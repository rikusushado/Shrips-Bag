from glob.py.rukian_utils import *

valid_arguments = globalArgs()
valid_arguments = getJSONData("data/args.json", "all")

arguments = validateArguments(valid_arguments, sys.argv)

cmd_data = getJSONData("data/build.json", "all", False, "command")

def build(array):
    script_dir = cmd_data.get("script-dir")
    for script in cmd_data.get("script-names"):
        command = f"../../{script_dir}/{script}"
        subprocess.run(["python3", command])
    
build(cmd_data, arguments[0])
