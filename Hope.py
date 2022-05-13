"""Standard Library Imports"""
from os import mkdir
from sys import argv

# Help Information
Help_Information = """
Welcome to the Hope Build System for Pineapple

Most of Hope's commands fall within this model:
Syntax Key: Hope <action> <context> <naming>

Help Information
----------------
Aliases: Help, help, H, h
`Hope Help`
Note: You can attach a context to help like so: `Hope Help New`

Create New Project
------------------
Aliases: New, new, Create, create, N, n, C, c
'Hope New <Project-Type> <project-name>'
"""

# Action Command Lists
New_Project_Com_List = [
    "New",
    "new",
    "Create",
    "create",
    "N",
    "n",
    "C",
    "c"
]

Help_Com_List = [
    "Help",
    "help",
    "H",
    "h"
]

# The prefabricated texts that is written into the .papple(s) file when creating a project dependant on type
Console_Application_Project_Type = """Import Prefabs
Import System

User_Input = Input()

Print("Sanity Check")

If (User_Input in Prefabs.EXIT_COMMANDS)
{
    System.Exit()
}
"""

User_Arguments = argv

# Debugging Information

def Spit_Debug_Info():
    print("""--Debug Info--
Arguments:{}
""".format(str(User_Arguments)))

# Help Print
def Help_Print():
    print(Help_Information)

# Project Generation Function
def Create():

    Project_Type, Project_Name = str(User_Arguments[2]),str(User_Arguments[3])
    print("Project Name: " + Project_Name)

    mkdir(User_Arguments[3])

    with open(Project_Name + "\\" + '{}_Main.papple'.format(Project_Name), 'w+') as GENERATED_PAPPLE_FILE:
        GENERATED_PAPPLE_FILE.write(Console_Application_Project_Type)

    with open(Project_Name + "\\" + '.gitignore', 'w+') as IGNORE_FILE:
        IGNORE_FILE.write(".Hope_Settings" + '\n' + ".Common")

    with open(Project_Name + "\\" + '.Hope_Settings', 'w+') as SETTINGS_FILE:
        SETTINGS_FILE.write("""# Hope Project Manager Settings

Project_Type={}
Iwa_Path={}
""".format(Project_Type, Project_Name))

# Analyze given commands
def CommandParsing():

    Action_Command_Given = str(User_Arguments[1])

    if Action_Command_Given in New_Project_Com_List:
        try:
            Create()
        except FileExistsError:
            print("Project with that name already exists, so Hope failed to create the project.")
    elif Action_Command_Given in Help_Com_List:
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