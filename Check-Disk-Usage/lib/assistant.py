class assistant:  
    def __init__(self):
        super().__init__()
        self.run(select)
              
    def run(self, select):
        match select:
            case "flang":
                self.lang()
                
            case "fchat":
                self.chat()
            
            case "ftarget":
                self.target()
                
            case _:
                error_internal = colored("Internal error:", "red")
                cprint(error_internal, "assistant called with non valid option.")
                print("This error is application fault!")
                exit(-1)
                
    def lang(self):
        print("Please, select an option:")
        print("Exit (0)")
        i = 1
        for language in languages.items():
            print("%s%d","{language} ({i})")
            i += 1
            
        length = languages.items.len()
        if select == 0:
            return 0
        
        elif select in range(length + 1)[1:-1]:
            return(languages[select])
        
        else:
            print("%d","Option {select} not in the list!")