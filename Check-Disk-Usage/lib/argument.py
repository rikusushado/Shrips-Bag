from lib.include import *
    
class argument:
    def translateToOptions(args):
        args.pop(0)
        keys = data.get("arg").get("key")
        
        length = keys.len() - 3
        options[0:length] = [""]
        
        for arg in args:
            for key in keys:
                if key in arg:
                    start = key.len()
                    value = arg[start:-1]
                    
                    match key:
                        case "--install":
                            return(task.install())
                        
                        case "--reinstall":
                            return(task.reinstall())
                            
                        case "--update":
                            return(task.reinstall())
                        
                        case "-c=":
                            options[0] = value
                            
                        case "-n=":
                            options[1] = value
                            
                        case "-t=":
                            options[2] = value
                            
                        case "-u=":
                            options[3] = value
                            
                        case _:
                            error_internal = colored("Internal error:", "red")
                            cprint("%s", error_internal, "argument handler does not know {key}.")
                            print("This error is application fault!")
                            exit(-1)
        
        return(options)
    