from glob.py.rukian_utils import *

valid_arguments = globalArgs()
valid_arguments = getJSONData("data/args.json", "disk-usage")

arguments = validateArguments(valid_arguments, sys.argv)

cmd_data = getJSONData("data/build.json", "disk-usage", False, "command")

def build(array):            
    command = cmd_data 

    subprocess.run(command)
    
build(cmd_data, arguments[0])
