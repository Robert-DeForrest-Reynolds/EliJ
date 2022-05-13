"""Standard Library Imports"""
import os
import sys
import glob

print(sys.path)
Project_Path = sys.path.append(os.path.join(os.path.dirname(__file__), '..'))
print(sys.path)

"""Imports"""
import Information

# Project Type Generation Strings


# Debugging Information

def Spit_Debug_Info():
    print("""--Debug Info--
Arguments:{}
""".format(str(sys.argv)))

# Help Print
def Help_Print():
    print(Information.Help_Information)

# Project Generation Function
def Create():

    Project_Type, Project_Name = str(argv[2]),str(argv[3])
    print("Project Name: " + Project_Name)

    sys.mkdir(sys.argv[3])

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

    Action_Command_Given = str(sys.argv[1])

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

if __name__ == '__main__':
    Spit_Debug_Info()
    CommandParsing()
    PyCacheCleanUp()