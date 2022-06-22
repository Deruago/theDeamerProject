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

# FGL (This is required for some tooling)
install_deamer_extra = False

confirm_with_enter = True

build_dir = "build"

install_location_include = None
install_location_lib = None
install_location_bin = None
install_location_include_argument = ""
install_location_lib_argument = ""
install_location_bin_argument = ""
install_prefix_argument = ""

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

def setup_install_locations():
    global install_location_include
    global install_location_lib
    global install_location_bin
    global install_location_include_argument
    global install_location_lib_argument
    global install_location_bin_argument
    global install_prefix_argument
    
    install_is_relative = False
    if install_location_include is not None:
        install_location_include_argument = f'-DCMAKE_INSTALL_INCLUDEDIR="{install_location_include}"'
        install_is_relative = True
        
    if install_location_lib is not None:
        install_location_lib_argument = f'-DCMAKE_INSTALL_LIBDIR="{install_location_lib}"'
        install_is_relative = True
        
    if install_location_bin is not None:
        install_location_bin_argument = f'-DCMAKE_INSTALL_BINDIR="{install_location_bin}"'
        install_is_relative = True
    
    if install_is_relative:
        install_prefix_argument = '-DCMAKE_INSTALL_PREFIX="../../install/"'

# Installs a Deamer Package
# If location is true it will check in the Deamer-lang github repository
# Otherwise it will look at the repositories of @Deruago
def install_extra_deamer_package(name: str, install: bool, test_argument: str = None, extra_args: str = "", location: bool = True):
    global install_location_lib_argument
    global install_location_bin_argument
    global install_prefix_argument
    setup_install_locations()
    
    # Test argument specifies the option to enable/disable testing
    if test_argument is not None:
        test_argument = f"-D{test_argument}=OFF"
    else:
        test_argument = ""
    
    if install:
        print(f"Retrieving Deamer Package: {name}")
        
        if os.path.isdir(f"{build_dir}/DeamerPackage/{name}"):
            os.system(f"cd {build_dir}/DeamerPackage/{name} && git pull")
        else:
            if location:
                os.system(f"git clone https://github.com/deamer-lang/{name}/ {build_dir}/DeamerPackage/{name}")
            else:
                os.system(f"git clone https://github.com/Deruago/{name}/ {build_dir}/DeamerPackage/{name}")
        
        print(f"Done Retrieving Deamer Package: {name}")
    
        print(f"Installing {name}")
        
        make_directory(f"{build_dir}/DeamerPackage/{name}/build")
        os.system(f'cd {build_dir}/DeamerPackage/{name}/build && cmake ../ -DINSTALL_GTEST=OFF {install_location_lib_argument} {install_location_bin_argument} {install_prefix_argument} {test_argument} {extra_args} && cmake --build . --target install')
        
        print(f"Done installing {name}")
        
# Installs a project
def install_project(name: str, install: bool, test_argument: str = None, extra_args: str = ""):
    global install_location_lib_argument
    global install_location_bin_argument
    global install_prefix_argument
    setup_install_locations()
    
    # Test argument specifies the option to enable/disable testing
    if test_argument is not None:
        test_argument = f"-D{test_argument}=OFF"
    else:
        test_argument = ""
    
    
    if install and subdirectory_exists(name):
        print(f"Installing {name}")
        
        make_directory(f"{build_dir}/{name}")
        os.system(f'cd {build_dir}/{name} && cmake ../../{name} -DINSTALL_GTEST=OFF {install_location_lib_argument} {install_location_bin_argument} {install_prefix_argument} {test_argument} {extra_args} && cmake --build . --target install')
        
        print(f"Done installing {name}")

# Installs a language project
def install_language_project(name: str, language_folder: str, install: bool, test_argument: str, extra_args: str = ""):
    global install_location_include_argument
    global install_location_lib_argument
    global install_location_bin_argument
    global install_prefix_argument
    setup_install_locations()
    
    # Test argument specifies the option to enable/disable testing
    if test_argument is not None:
        test_argument = f"-D{test_argument}=OFF"
    else:
        test_argument = ""
        
    if install and subdirectory_exists(name):
        print(f"Installing {name}")
        
        make_directory(f"{build_dir}/{name}")
        os.system(f'cd {build_dir}/{name} && cmake ../../{name}/{language_folder} -DINSTALL_GTEST=OFF {install_location_include_argument} {install_location_lib_argument} {install_location_bin_argument} {install_prefix_argument} {test_argument} {test_argument} {extra_args} && cmake --build . --target install')
        
        print(f"Done installing {name}")
 

def install_subprojects():
    global install_deamer_core
    global install_deamer_external
    global install_deamer_optional
    global install_deamer_extra
    
    print(subfolders)
    
    # Deamer External and Deamer Algorithm are dependency-less, and are used by
    # most subprojects. Thus should be installed first
    install_project("DeamerExternal", install_deamer_external, "DEAMER_EXTERNAL_BUILD_TESTS")
    install_project("DeamerAlgorithm", install_deamer_external, "DEAMER_ALGORITHM_BUILD_TESTS")
    
    # Dregx Depends on DeamerExternal
    # Deamer uses Dregx for DFA Construction and Regex Fuzzing
    install_language_project("DREGX", "dregx", install_deamer_external, None, "-Ddregx_ENABLE_COMPILER_GENERATOR=OFF")
    
    # Required
    install_project("Deamer", install_deamer_core, "DEAMER_BUILD_TESTS")
    install_language_project("DLDL", "DLDL", install_deamer_core, "DLDL_BUILD_TESTS")
    
    # Optional
    install_project("DST", install_deamer_extra)
    
    install_extra_deamer_package("FGL", install_deamer_optional, "TESTS", location=False)

def handle_arguments():
    global install_deamer_core
    global install_deamer_external
    global install_deamer_optional
    global install_deamer_extra
    
    global confirm_with_enter
    global install_location_include
    global install_location_lib
    global install_location_bin
    
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
            
        if argument == "-extra":
            print("Installing everything available.")
            install_deamer_core = True
            install_deamer_external = True
            install_deamer_optional = True
            install_deamer_extra = True
        
        if argument == "-external-only":
            print("Installing only external required depencencies.")
            install_deamer_core = False
            install_deamer_external = True
            install_deamer_optional = False
            
        if argument == "-optional":
            print("Also installing the optional parts")
            install_deamer_optional = True
        
        if argument == "-local-install":
            install_location_include = "include/"
            install_location_lib = "lib/"
            install_location_bin = "bin/"
            
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
