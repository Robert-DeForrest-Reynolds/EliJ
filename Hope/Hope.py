# Placeholder file for Hope build system

from sys import argv
from os import mkdir

# Command Lists
New_Project_Com_List = [
    "New",
    "new",
    "n"
]

# Debugging
print("Arguments:" + str(argv) + '\n')

# Project Generation Function
def Create():

    Project_Name = str(argv[2])

    print("Project Name:" + Project_Name)
    mkdir(argv[2])

    with open(Project_Name + "\\" + '.gitignore', 'w+') as IGNORE_FILE:
        IGNORE_FILE.write(".Hope_Settings" + '\n' + ".Common")

    with open(Project_Name + "\\" + '.Hope_Settings', 'w+') as SETTINGS_FILE:
        SETTINGS_FILE.write("""# Hope Project Manager Settings

Iwa_Path=
Project_Type=
""")

# Analyze given commands
def CommandParsing():
    Command_Given = str(argv[1])

    if Command_Given in New_Project_Com_List:
        try:
            Create()
        except FileExistsError:
            print("Project with that name already exists, so Hope failed to create the project.")

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
    CommandParsing()