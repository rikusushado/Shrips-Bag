from lib.includes import *

with open('data.json', 'r') as file:
    data = json.load(file)


def runningAsRoot() -> bool:
    return os.getuid() == 0
                          

