import os
import sys
import shutil
import subprocess

# This Python Script utilizes the Python standard library to offer
# A Cross Platform OS support for console commands.
#
# Deamer CC construct the argument input for this python script
# And Python executes the correct arguments.
#
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public License
# as published by the Free Software Foundation; either version 3
# of the License, or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software Foundation,
# Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
#
# For more information go to:
# https://github.com/Deruago/theDeamerProject
#
# If you find some crucial issue or bug please report it. By following the above link.
#

dangerous_script = False
our_os = ""
target_os = ""
python_console_version = "1.0.0"
user_name = ""
debug_mode = False

def execute_setting(arg_os: str, arg_header: str, arg_content: str):
	global dangerous_script
	global our_os
	global target_os
	global user_name
	global debug_mode

	if arg_header == "DANGEROUS":
		# Dangerous script should not continue if some error occures
		if arg_content == "TRUE":
			dangerous_script = True
		else:
			dangerous_script = False
	if arg_header == "OUR_OS":
		# Specifies the OS the python script is executed on
		# Required when target specific commands are executed
		our_os = arg_content
	if arg_header == "THEIR_OR":
		# Specifies the OS the python script should target
		# Required when target specific commands are executed
		our_os = arg_content
	if arg_header == "USER_NAME":
		# Specifies the name of the user or application which initiated this script
		user_name = arg_content
	if arg_header == "DEBUG_MODE":
		# Enable or Disable Debug Mode
		if arg_content == "TRUE":
			debug_mode = True
		else:
			debug_mode = False

def execute_windows_arguments(arg_os: str, arg_header: str, arg_content: str):
	global dangerous_script
	global our_os
	global target_os
	global user_name
	global python_console_version
	global debug_mode

	if our_os == "linux":
		# No conversion possible
		pass
	if our_os == "windows":
		# Standard windows cmd call
		os.system(f'{arg_content}')
		pass
	if our_os == "mac":
		# No conversion possible
		pass
	pass

def execute_linux_argument(arg_os: str, arg_header: str, arg_content: str):
	global dangerous_script
	global our_os
	global target_os
	global user_name
	global python_console_version
	global debug_mode

	if our_os == "linux":
		# Standard linux console call
		os.system(f'({arg_content})')
		pass
	if our_os == "windows":
		# Try to use WSL
		os.system(f"bash -c '({arg_content})'")
		pass
	if our_os == "mac":
		# No conversion possible
		pass
	pass

def execute_mac_argument(arg_os: str, arg_header: str, arg_content: str):
	global dangerous_script
	global our_os
	global target_os
	global user_name
	global python_console_version
	global debug_mode

	if our_os == "linux":
		# No conversion possible
		pass
	if our_os == "windows":
		# No conversion possible
		pass
	if our_os == "mac":
		# Standard mac console call
		os.system(f'({arg_content})')
		pass
	pass

def find_executable(lhsPath: str, file: str):
	for root, dirs, files in os.walk(lhsPath):
		if file in files:
			return os.path.join(root, file)
	raise Exception('Could not find file, this script is maybe dangerous')

def execute_python_argument(arg_os: str, arg_header: str, arg_content: str):
	global dangerous_script
	global our_os
	global target_os
	global user_name
	global python_console_version
	global debug_mode

	if debug_mode:
		print(f'{arg_os} --- {arg_header} --- {arg_content}')
	if arg_header == "MOVEFILE":
		# This will move the file to the given path
		_, lhs_path, __, rhs_path, ___ = arg_content.split('"')
		shutil.move(lhs_path, rhs_path)
		return
	if arg_header == "CD":
		# This will change the directory to the given path
		_, lhs_path, __ = arg_content.split('"')
		os.chdir(lhs_path)
		return
	if arg_header == "REMFILE":
		# This will remove the file at the given path
		_, lhs_path, __ = arg_content.split('"')
		os.remove(lhs_path)
		return
	if arg_header == "REMDIR":
		# This will remove the directory at the given path
		_, lhs_path, __ = arg_content.split('"')
		shutil.rmtree(lhs_path)
		return
	if arg_header == "CREATEDIR":
		# This will create the directory at the given path
		_, lhs_path, __ = arg_content.split('"')
		os.mkdir(lhs_path)
		return
	if arg_header == "FINDANDEXEC":
		# This will find and executable and execute it
		# This command will only run executables without other args.
		_, lhs_path, __ = arg_content.split('"')
		executable = find_executable('./', lhs_path)
		subprocess.check_call([executable])
		return
	if arg_header == "COPYFILE":
		# This will copy the file to the given path
		_, lhs_path, __, rhs_path, ___ = arg_content.split('"')
		shutil.copy(lhs_path, rhs_path)
		return
	if arg_header == "COMMAND":
		# It is assumed the command is cross platform executable
		_, lhs_path, __= arg_content.split('"')
		os.system(lhs_path)
		return
	if arg_header == "ECHO":
		# This will echo the given argument
		_, lhs_path, __= arg_content.split('"')
		print(lhs_path)
		return
	if arg_header == "VERSION":
		# This will print the python script version
		print(python_console_version)
		return
	print(f"Unknown Argument Header: {arg_header}")

def execute_argument(arg: str):
	global dangerous_script
	global our_os
	global target_os
	global user_name
	global python_console_version
	global debug_mode

	# argument_os is the first word
	#  - Defines the target OS.
	#  - This variable is also used to specify if some setting must be initialized
	# argument_header is the second word
	#  - Defines what type of command is executed.
	# argument_content the arguments for the command
	argument_os, argument_header, argument_content = arg.split(" ", 2)
	
	# Setup 1 setting
	if argument_os == "SETTING":
		execute_setting(argument_os, argument_header, argument_content)
		return
	if argument_os == "windows":
		execute_windows_argument(argument_os, argument_header, argument_content)
		return
	if argument_os == "linux":
		execute_linux_argument(argument_os, argument_header, argument_content)
		return
	if argument_os == "mac":
		execute_mac_argument(argument_os, argument_header, argument_content)
		return
	
	try:
		execute_python_argument(argument_os, argument_header, argument_content)
	except:
		# print(f"Command throwed exception. This python script might become dangerous")
		if dangerous_script:
			print("As the script is dangerous this script will not continue further!")
			sys.exit()
		return

def main():
	global debug_mode
	if debug_mode:
		print('Entered Python Console!')

	first = True
	for argument in sys.argv:
		if first:
			first = False
			continue

		execute_argument(argument)

if __name__ == "__main__":
	main()
