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