"""Standard Library Imports"""
from os import mkdir, system
from sys import argv

from Information import *
from CommandLists import *
from DefaultData import *
from Debug import *

ArgumentAmount = len(argv)
Arguments = argv
HopeCall = argv[0]

if ArgumentAmount >= 2:
    ActionType = argv[1]

if ArgumentAmount >= 3:
    ProjectName = argv[2]

if ArgumentAmount >= 4:
    Parameter_1 = argv[3]

if ArgumentAmount >= 5:
    Parameter_2 = argv[4]

if ArgumentAmount >= 6:
    Parameter_3 = argv[5]

def Help_Print():
    print(Help_Information)

def Create():
    ProjectType = Parameter_1
    print("Project Name: " + ProjectName)

    mkdir(ProjectName)

    with open(ProjectName + "\\" + '{}.papple'.format(ProjectName), 'w+') as GENERATED_PAPPLE_FILE:
        try:
            GENERATED_PAPPLE_FILE.write(Console_Application_Project_Type)
        except:
            print("Error generating papple file template")
        GENERATED_PAPPLE_FILE.close()

    with open(ProjectName + "\\" + '.gitignore', 'w+') as IGNORE_FILE:
        try:
            IGNORE_FILE.write(DefaultGitIgnore)
        except:
            print("Error generating ignore file")
    IGNORE_FILE.close()

    with open(ProjectName + "\\" + '.Hope_Settings', 'w+') as SETTINGSFILE:
        try:
            SETTINGSFILE.write(DefaultProjectSettings.format(ProjectType, ProjectName, ProjectName))
        except:
            print("Error generating Hope settings file")
    SETTINGSFILE.close()

def Build():
    ProjectPath = ProjectName
    try:
        print("Building", ProjectName)
        system("Iwa {}".format(ProjectPath))
        with open(ProjectName + "\.Hope_Settings", 'r') as SETTINGSFILE:
            for Line in SETTINGSFILE:
                if "ProjectPath=" in Line:
                    ProjectPath = Line.replace("ProjectPath=", "")
    except:
        print("Build Error")
        

def Run():
    ProjectPath = ProjectName
    if ArgumentAmount > 3:
        Flags = " ".join(Arguments[3::])
        print(Flags)
        print("Running", ProjectName)
        system(f"Lily {ProjectPath} {Flags}")
    else:
        print("Running", ProjectName)
        system(f"Lily {ProjectPath}")


def CommandParsing():
    try:
        if ActionType in NewProjectCommandList and ArgumentAmount >= 4:
            try:
                Create()
                return "Project Creation Successful"
            except FileExistsError:
                print("Project with that name already exists, so Hope failed to create the project.")
                return "Project Creation Failure, Project With Name Already Exists"
        elif ActionType in BuildCommandList:
            try:
                Build()
            except:
                print("Failure building project for some reason")
        elif ActionType in RunCommandList:
            try:
                Run()
            except:
                print("Failure building project for some reason")
        elif ActionType in HelpCommandList:
            Help_Print()
            return "Help Print"
        elif ActionType == "Debug":
            Spit_Debug_Info(Arguments)
            return "Debug mode"
        else:
            print("Error when parsing arguments")
            return "Parsing Error"
    except:
        "Some kind of error in CommandParsing() function"

if __name__ == '__main__':
    CommandParsing()