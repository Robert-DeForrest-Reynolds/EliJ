"""Standard Library Imports"""
from os import mkdir, remove, removedirs, getcwd, system
from sys import argv
from glob import glob

from Information import *
from Command_Lists import *
from Settings_File_Default_Data import *
from Debug import *
from Utilities_Declarations import *

Argument_Amount = len(argv)
Arguments = argv
Hope_Call = argv[0]

if Argument_Amount >= 2:
    Action_Type = argv[1]

if Argument_Amount >= 3:
    Project_Name = argv[2]

if Argument_Amount >= 4:
    Parameter_1 = argv[3]

if Argument_Amount >= 5:
    Parameter_2 = argv[4]

if Argument_Amount >= 6:
    Parameter_3 = argv[5]

def Help_Print():
    print(Help_Information)

def Create():

    Project_Type = Parameter_1
    print("Project Name: " + Project_Name)

    mkdir(Project_Name)

    with open(Project_Name + "\\" + '{}.papple'.format(Project_Name), 'w+') as GENERATED_PAPPLE_FILE:
        try:
            GENERATED_PAPPLE_FILE.write(Console_Application_Project_Type)
        except:
            print("Error generating papple file template")
        GENERATED_PAPPLE_FILE.close()

    with open(Project_Name + "\\" + '.gitignore', 'w+') as IGNORE_FILE:
        try:
            IGNORE_FILE.write(DefaultGitIgnore)
        except:
            print("Error generating ignore file")
    IGNORE_FILE.close()

    with open(Project_Name + "\\" + '.Hope_Settings', 'w+') as SETTINGS_FILE:
        try:
            SETTINGS_FILE.write(DefaultProjectSettings.format(Project_Type, Project_Name, Project_Name))
        except:
            print("Error generating Hope settings file")
    SETTINGS_FILE.close()

def Build():
    Project_Path = Project_Name
    try:
        print("Building", Project_Name)
        system("Iwa {}".format(Project_Path))
        with open(Project_Name + "\.Hope_Settings", 'r') as SETTINGS_FILE:
            for Line in SETTINGS_FILE:
                if "Project_Path=" in Line:
                    Project_Path = Line.replace("Project_Path=", "")
    except:
        print("Build Error")


def CommandParsing():
    try:
        if Action_Type in New_Project_Command_List and Argument_Amount >= 4:
            try:
                Create()
                return "Project Creation Successful"
            except FileExistsError:
                print("Project with that name already exists, so Hope failed to create the project.")
                return "Project Creation Failure, Project With Name Already Exists"
        elif Action_Type in Build_Command_List:
            try:
                Build()
            except:
                print("Failure building project for some reason")
        elif Action_Type in Help_Command_List:
            Help_Print()
            return "Help Print"
        elif Action_Type == "Debug":
            Spit_Debug_Info(Arguments)
            return "Debug mode"
        else:
            print("Error when parsing arguments")
            return "Parsing Error"
    except:
        "Some kind of error in CommandParsing() function"

def PyCacheCleanUp():
    try:
        print(NEWLINE, "Commencing PyCache Cleanup from Hope")
        Project_Path = getcwd()
        pyCacheFiles = glob(Project_Path + "\**\*.pyc", recursive = True)
        pyCacheFolders = glob(Project_Path + "\**\__pycache__", recursive = True)
        for File in pyCacheFiles:
            try:
                remove(File)
            except:
                print("Error removing .pyc files.")
        for Directory in pyCacheFolders:
            try:
                removedirs(Directory)
            except:
                print("Error removing _pycache__ directories.")
    except:
        "Some kind of error in PyCacheCleanup() function"

if __name__ == '__main__':
    CommandParsing()
    PyCacheCleanUp()