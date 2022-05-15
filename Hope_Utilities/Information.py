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

Console_Application_Project_Type = """Import
    IO

Output("I'm Alive.")
"""

DefaultProjectSettings = """# Hope Project Manager Settings

Project_Type={}
Iwa_Path={}
"""

DefaultGitIgnore = """".Hope_Settings"
".Common"
"""