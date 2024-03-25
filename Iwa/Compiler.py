from sys import argv

ArgumentCount = len(argv)
Arguments = argv

ProjectPath = None
ProjectName = ProjectPath

def Command_Parsing():
    if ArgumentCount >= 2:
        global Project_Path
        ProjectPath = Arguments[1]
        print("Compilation")
        Compilation = True
        # Compile()
        return Compilation
    else:
        return "Zero Arguements Given"