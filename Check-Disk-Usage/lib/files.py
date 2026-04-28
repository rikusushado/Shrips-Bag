class files:
    def readJSON(path):
        with open(path, 'r') as file:
            data = json.load(file)

    def buildPaths(tree, current_path=""):
        paths = []
        
        if isinstance(tree, str):
            return [os.path.join(current_path, tree.lstrip("/"))]

        if len(tree) == 2 and isinstance(tree[0], str) and isinstance(tree[1], list):
            prefix = tree[0]
            content = tree[1]
            new_base = os.path.join(current_path, prefix.lstrip("/"))
            for item in content:
                paths.extend(build_paths(item, new_base))
        
        else:
            for item in tree:
                paths.extend(build_paths(item, current_path))
                
        return paths
                        

    def prepareEnvironment(paths):
        for path in paths:
            if not os.path.exists(path):
                if runningAsRoot():
                    if "/var/lang" in path:
                        assistant.run("flang")
                else:
                    error_permission = colored("Permission error:", "yellow")
                    cprint(error_string, "Required files or folders not found!")
                    print("Please run as root if you want to download them with the asistant!")