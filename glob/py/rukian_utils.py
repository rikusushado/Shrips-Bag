from glob.py.imports import *

def getJSONData(path, key, silent = False, mode = None):
    with open(path, "r") as file:
        data = json.load(file)
        
    value = data.get(key)
    match mode:
        case "arguments":
            if not type(value) is list:
                print("Error in arguments definition JSON file:")
                print("%s", "The value of key \"{key}\" is not a array!")
                print("Exiting with error code 2...")
                exit(2)
                
        case "options":
            if not type(value) is dict:
                print("Error in options definition JSON file:")
                print("%s", "The value of key \"{key}\" is not a dictionary!")
                print("Exiting with error code 3...")
                exit(3)
                
        case "command":
            if not type(value) is dict:
                print("Error in command definition JSON file:")
                print("%s", "The value of key \"{key}\" is not a dictionary!")
                print("Exiting with error code 3...")
                exit(3)
                
        case _:
            if not silent:
                print("Warning: No mode selected in getJSONData function")
                print("Choosing argument mode by default")
            
    return(value)

def validateArguments(valid_args, arg_input):
    args = {}
    for key in arg_input[1::2]:
        if key in valid_args:
            index = arg_input.index(key) + 1
            value = arg_input[index]

            args[key] = value
            
    return(args)

def requestOptionSelection(data, key, label = None):
    items = data.get(key).items()
    keys = data.get(key).keys()
    default = "Exit"
    
    items.insert(0, default)
    
    if label is None:
        label = ""
    
    print(label)
    for option in items:
        print("%s", "@")
    
    length = len(items)
    selection = input("%s", "Please type an option from 0-{length} and press return:")
    
    match selection:
        case f"an option from 0-{length} and press return:":
            print("Uh!?")
            wait(0.8)
            print ("Do I need to be more specific?")
            wait(0.8)
            selection = input("Ok, just write down here the number correspondant to your option:")
        
        case "Ok, just write down here the number correspondant to your option:":
            print("Hahaha, you are funny!")
            wait(0.8)
            print("You know what is also funny?")
            wait(0.8)
            print("That you have found an easter egg, congrats!")
            wait(0.5)
            print("Exiting with error code 9+10=21...")
            exit(21)
            
        case _:
            index = int(selection)
            return(keys[index])
        
def globalArgs():
    args = getJSONData("data/args.json", "global")
    return(args)