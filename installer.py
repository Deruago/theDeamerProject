import os
import sys
import subprocess


subfolders = [ f.path for f in os.scandir("./") if f.is_dir() ]

# installation groups
# Deamer, DLDL
install_deamer_core = True

# DeamerExternal, DeamerAlgorithm
install_deamer_external = True

# DST
install_deamer_optional = False

confirm_with_enter = True

build_dir = "build"

def install_header():
    global confirm_with_enter
    
    print("This will automatically install the several subprojects.")
    
    if confirm_with_enter:
        input("Press enter to continue this process.")


def make_directory(name: str):
    try:
        os.mkdir(name)
    except FileExistsError:
        pass
        

def subdirectory_exists(name: str):
    return f"./{name}" in subfolders


def install_project(name: str, install: bool, test_argument: str, extra_args: str = ""):
    # Test argument specifies the option to enable/disable testing
    if test_argument is not None:
        test_argument = f"-D{test_argument}=OFF"
    else:
        test_argument = ""
        
    if install and subdirectory_exists(name):
        print(f"Installing {name}")
        
        make_directory(f"{build_dir}/{name}")
        os.system(f'cd {build_dir}/{name} && cmake ../../{name} -DINSTALL_GTEST=OFF {test_argument} {extra_args} && cmake --build . --target install')
        
        print(f"Done installing {name}")
 

def install_subprojects():
    global install_deamer_core
    global install_deamer_external
    global install_deamer_optional
    
    print(subfolders)
    
    # Deamer External and Deamer Algorithm are dependency-less, and are used by
    # most subprojects. Thus should be installed first
    install_project("DeamerExternal", install_deamer_external, "DEAMER_EXTERNAL_BUILD_TESTS")
    install_project("DeamerAlgorithm", install_deamer_external, "DEAMER_ALGORITHM_BUILD_TESTS")
    
    # Dregx Depends on DeamerExternal
    # Deamer uses Dregx for DFA Construction and Regex Fuzzing
    install_project("DREGX", install_deamer_external, None, "-Ddregx_ENABLE_COMPILER_GENERATOR=OFF")
    
    # Required
    install_project("Deamer", install_deamer_core, "DEAMER_BUILD_TESTS")
    install_project("DLDL", install_deamer_core, "DLDL_BUILD_TESTS")
    
    # Optional
    install_project("DST", install_deamer_optional, "TESTS")

def handle_arguments():
    global install_deamer_core
    global install_deamer_external
    global install_deamer_optional
    global confirm_with_enter

    if len(sys.argv) <= 1:
        return
    
    for argument in sys.argv:
        if argument == "-no-confirm-with-enter":
            confirm_with_enter = False
    
        if argument == "-complete":
            print("Installing everything available.")
            install_deamer_core = True
            install_deamer_external = True
            install_deamer_optional = True
        
        if argument == "-external-only":
            print("Installing only external required depencencies.")
            install_deamer_core = False
            install_deamer_external = True
            install_deamer_optional = False
            
        if argument == "-optional":
            print("Also installing the optional parts")
            install_deamer_optional = True
            
def handle_build_directory():
    global build_dir
    
    # If the python script sees a different OS
    # It will create a different build directory for that OS
    # May not work for all different OSes
    if os.name == 'nt':
        build_dir = "build_windows"
        make_directory("build_windows")
    elif os.name == 'posix':
        build_dir = "build_linux"
        make_directory("build_linux")
    else:
        build_dir = "build"
        make_directory("build")

if __name__ == "__main__":
    handle_build_directory()
    handle_arguments()
    install_header()
    install_subprojects()
