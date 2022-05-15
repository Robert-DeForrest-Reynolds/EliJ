"""Standard Library Imports"""
from argparse import Action
from os import mkdir, remove, removedirs, getcwd
from sys import argv
from glob import glob

from Hope_Utilities.Information import *

Argument_Amount = len(argv)
User_Arguments = argv
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

# Debugging
def Spit_Debug_Info():
    print("""--Debug Info--
Arguments:{}
""".format(str(User_Arguments)))

# Help Print
def Help_Print():
    print(Help_Information)

# Project Generation Function
def Create():

    Project_Type = Parameter_1
    print("Project Name: " + Project_Name)

    mkdir(Project_Name)

    with open(Project_Name + "\\" + '{}.papple'.format(Project_Name), 'w+') as GENERATED_PAPPLE_FILE:
        GENERATED_PAPPLE_FILE.write(Console_Application_Project_Type)

    with open(Project_Name + "\\" + '.gitignore', 'w+') as IGNORE_FILE:
        IGNORE_FILE.write(DefaultGitIgnore)

    with open(Project_Name + "\\" + '.Hope_Settings', 'w+') as SETTINGS_FILE:
        SETTINGS_FILE.write(DefaultProjectSettings.format(Project_Type, Project_Name))

# Analyze given commands
def CommandParsing():

    if Action_Type in New_Project_Com_List:
        try:
            Create()
        except FileExistsError:
            print("Project with that name already exists, so Hope failed to create the project.")
    elif Action_Type in Help_Com_List:
        Help_Print()
    elif Action_Type == "Debug":
        Spit_Debug_Info

def PyCacheCleanUp():
    print("\n\nCommencing PyCache Cleanup")
    Project_Path = getcwd()
    pyCacheFiles = glob(Project_Path + "\**\*.pyc", recursive = True)
    pyCacheFolders = glob(Project_Path + "\**\__pycache__", recursive = True)
    for file in pyCacheFiles:
        try:
            print(file)
            remove(file)
        except:
            print("Error removing .pyc files.")
    for dir in pyCacheFolders:
        try:
            print(dir)
            removedirs(dir)
        except:
            print("Error removing _pycache__ directories.")

if __name__ == '__main__':
    CommandParsing()
    PyCacheCleanUp()