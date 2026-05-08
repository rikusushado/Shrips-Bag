from glob.py.rukian_utils import *

valid_arguments = globalArgs()
valid_arguments = getJSONData("data/args.json", "update-wp")

arguments = validateArguments(valid_arguments, sys.argv)

cmd_data = getJSONData("data/build.json", "update-wp", False, "command")

def build(array, mode = "debug"):            
    command = commands.get(mode)

    subprocess.run(command)
    
build(cmd_data, arguments[0])