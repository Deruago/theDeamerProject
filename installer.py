import os
import sys
import subprocess


subfolders = [ f.path for f in os.scandir("./") if f.is_dir() ]

# installation groups
# Deamer, DeamerExternal, DeamerAlgorithm, DLDL
install_deamer_core = True

# DST
install_deamer_optional = False

build_dir = "build"

def install_header():
    print("This will automatically install the several subprojects.")
    input("Press enter to continue this process.")


def make_directory(name: str):
    try:
        os.mkdir(name)
    except FileExistsError:
        pass
        

def subdirectory_exists(name: str):
    return f"./{name}" in subfolders


def install_project(name: str, install: bool):
    if install and subdirectory_exists(name):
        print(f"Installing {name}")
        
        make_directory(f"{build_dir}/{name}")
        os.system(f'cd {build_dir}/{name} && cmake ../../{name} -DINSTALL_GTEST=off && cmake --build . --target install')
        
        print(f"Done installing {name}")
 

def install_subprojects():
    print(subfolders)
    
    # Deamer External and Deamer Algorithm are dependency-less, and are used by
    # most subprojects. Thus should be installed first
    install_project("DeamerExternal", install_deamer_core)
    install_project("DeamerAlgorithm", install_deamer_core)
    
    # Required
    install_project("Deamer", install_deamer_core)
    install_project("DLDL", install_deamer_core)
    
    # Optional
    install_project("DST", install_deamer_optional)

def handle_arguments():
    global install_deamer_core
    global install_deamer_optional

    if len(sys.argv) <= 1:
        return
    
    for argument in sys.argv:
        if argument == "-complete":
            print("Installing everything available.")
            install_deamer_core = True
            install_deamer_optional = True
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
