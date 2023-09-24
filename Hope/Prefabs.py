DefaultProjectSettings = """# Hope Project Manager Settings

Project_Type={}
Iwa_Path={}
Project_Path={}
"""

DefaultGitIgnore = """".Hope_Settings"
".Common"
"""

Console_Application_Project_Type_Prefab = """# This is the prefab code for a Console project #
Out("I'm Alive.")"""

DevTest_Application_Project_Type_Prefab = """# This is the prefab code for a DevTest project #
func Addition(int X, int y){
    return X + Y;
}

Out(Addition(5, 5))
"""