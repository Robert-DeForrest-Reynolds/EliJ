from os import mkdir, system, path
from sys import argv

from Information import Help_Information
from Prefabs import DefaultProjectSettings, DefaultGitIgnore, Console_Application_Project_Type_Prefab, DevTest_Application_Project_Type_Prefab

# Import EliJ Utility Files
from os.path import dirname, realpath
from sys import path
path.append(dirname(dirname(realpath(__file__))))
from Helpers import Pretty_Wrap

class Hope:
    def __init__(Self):
        Pretty_Wrap("~~~ Always Have Hope ~~~")
        Self.Arguments = [Argument.lower() for Argument in argv]
        Self.ArgumentAmount = len(argv)

        Self.CommandMapping = {
            "create": Self.Create,
            "c": Self.Create,
            "new": Self.Create,
            "n": Self.Create,
            "build": Self.Build,
            "b": Self.Build,
            "run": Self.Run,
            "r": Self.Run,
            "help": Self.Help_Print,
            "h": Self.Help_Print,
        }

        if Self.ArgumentAmount >= 2:
            try:
                Command = Self.Arguments[1]
                Self.CommandMapping[Command]()
            except KeyError:
                print("Whatever you gave is not a command.")

    def Help_Print(Self):
        print(Help_Information)

    def Create(Self):
        ProjectPrefabMapping = {
            "console": Console_Application_Project_Type_Prefab,
            "test": DevTest_Application_Project_Type_Prefab
        }

        if Self.ArgumentAmount == 4:
            ProjectType = Self.Arguments[2]
            ProjectName = Self.Arguments[3]

        mkdir(ProjectName)

        with open(path.join(ProjectName, f'{ProjectName}.papple'), 'w+') as GENERATED_PAPPLE_FILE:
            try:
                GENERATED_PAPPLE_FILE.write(ProjectPrefabMapping[ProjectType])
            except:
                print("Error generating papple file template")
            GENERATED_PAPPLE_FILE.close()

        with open(path.join(ProjectName, '.gitignore'), 'w+') as IGNORE_FILE:
            try:
                IGNORE_FILE.write(DefaultGitIgnore)
            except:
                print("Error generating ignore file")
        IGNORE_FILE.close()

        with open(path.join(ProjectName, '.Hope_Settings'), 'w+') as SETTINGSFILE:
            try:
                SETTINGSFILE.write(DefaultProjectSettings.format(ProjectType, ProjectName, ProjectName))
            except:
                print("Error generating Hope settings file")
        SETTINGSFILE.close()

    def Build(Self):
        if Self.ArgumentAmount == 3:
            ProjectName = Self.Arguments[2]
            print("Building", ProjectName)
            system(f"iwa c {ProjectName}\{ProjectName}")
            with open(ProjectName + "\.Hope_Settings", 'r') as SETTINGSFILE:
                for Line in SETTINGSFILE:
                    if "ProjectPath=" in Line:
                        ProjectPath = Line.replace("ProjectPath=", "")
            

    def Run(Self):
        print("Always have hope.")
        if Self.ArgumentAmount == 3:
            ProjectName = Self.Arguments[2]
            print("Running", ProjectName)
            system(f"Lily {path.join(ProjectName, ProjectName)}.papple")
        elif Self.ArgumentAmount >= 3:
            ProjectName = Self.Arguments[2]
            Flags = " ".join(Self.Arguments[3::])
            print(Flags)
            print("Running", ProjectName)
            system(f"Lily {path.join(ProjectName, ProjectName)}.papple {Flags}")
        else:
            print("What?")
