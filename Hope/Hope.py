"""Standard Library Imports"""
from sys import argv
from os import mkdir, remove, removedirs
import glob

"""Prefab Imports"""
from Prefabs import Information

# Project Type Generation Strings


# Debugging Information

def Spit_Debug_Info():
    print("""--Debug Info--
Arguments:{}
""".format(str(argv)))

# Help Print
def Help_Print():
    print(Information.Help_Information)

# Project Generation Function
def Create():

    Project_Type, Project_Name = str(argv[2]),str(argv[3])
    print("Project Name: " + Project_Name)

    mkdir(argv[3])

    with open(Project_Name + "\\" + '{}_Main.papple'.format(Project_Name), 'w+') as GENERATED_PAPPLE_FILE:
        GENERATED_PAPPLE_FILE.write(Information.Console_Application_Project_Type)

    with open(Project_Name + "\\" + '.gitignore', 'w+') as IGNORE_FILE:
        IGNORE_FILE.write(".Hope_Settings" + '\n' + ".Common")

    with open(Project_Name + "\\" + '.Hope_Settings', 'w+') as SETTINGS_FILE:
        SETTINGS_FILE.write("""# Hope Project Manager Settings

Project_Type={}
Iwa_Path={}
""".format(Project_Type, Project_Name))

# Analyze given commands
def CommandParsing():

    Action_Command_Given = str(argv[1])

    if Action_Command_Given in Information.New_Project_Com_List:
        try:
            Create()
        except FileExistsError:
            print("Project with that name already exists, so Hope failed to create the project.")
    elif Action_Command_Given in Information.Help_Com_List:
        Help_Print()

# Project Prototype
def Prototype():
    pass

# Project Build
def Build():
    pass

# Project build and run
def Run():
    pass

# Project build for release
def ReleaseBuild():
    pass

# Project Clean
def Clean():
    pass

# Clean Up Those Gross Files. I No Likey.
# Also, this is the only function you are not allowed to remove if you take this source code.
# If you do, I will beat you with a baguette.
def PyCacheCleanUp():
    pyCacheFiles = glob.glob("*\**\*.pyc", recursive = True)
    pyCacheFolders = glob.glob("*\**\__pycache__", recursive = True)
    for file in pyCacheFiles:
        try:
            remove(file)
        except:
            print("""\n\nError removing .pyc files.
Ignore this if you do not know what it means, but do please report it.
The files are harmless, this function is only to avoid clutter.
""")
    for dir in pyCacheFolders:
        try:
            removedirs(dir)
        except:
            print("""\n\nError removing _pycache__ directories.
Ignore this if you do not know what it means, but do please report it.
The files are harmless, this function is only for convience.
""")

if __name__ == '__main__':
    Spit_Debug_Info()
    CommandParsing()
    PyCacheCleanUp()