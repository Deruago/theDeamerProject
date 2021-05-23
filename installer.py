import os
import subprocess


subfolders = [ f.path for f in os.scandir("./") if f.is_dir() ]

# installation groups
# Deamer, DeamerExternal, DLDL
install_deamer_core = True

# DST
install_deamer_optional = False


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
        make_directory(f"build/{name}")
        os.system(f'cd build/{name} && cmake ../../{name} && cmake --build . --target install')
 

def install_subprojects():
    print(subfolders)
    make_directory("build")
    
    install_project("Deamer", install_deamer_core)
    install_project("DeamerExternal", install_deamer_core)
    install_project("DLDL", install_deamer_core)
    install_project("DST", install_deamer_optional)


if __name__ == "__main__":
    install_header()
    install_subprojects()
