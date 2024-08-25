# Type ignore comments are because VSCode kinda sucks.
from typing import List # type: ignore
from typing import Dict # type:  ignore
from sys import argv as Arguments
from os import system, remove
from os.path import exists # type:ignore
from Generators import Generate_Printf_Function, Generate_Integer_Variable
from Project import Project

# Import EliJ Utility Files
from os.path import dirname, realpath
from sys import path
path.append(dirname(dirname(realpath(__file__))))
from Helpers import Pretty_Wrap

from Parser import Parse_Source_File


global ProjectInstance
ProjectInstance = Project()

global FilePath
FilePath = None

GlobalVariableMapping = {}

FunctionsMapping:Dict[str,str] = {}

Functions:List[str] = {
    "Out": Generate_Printf_Function,
}

Variables:List[str] = {
    "Int": Generate_Integer_Variable,
}

StringPositions:Dict[str,List[int]] = {}

HelpMessage = """\
Iwa is the compiler for the Pineapple programming language, by Robert Lawrence DeForrest Reynolds.

I thank you for using this, and I hope you enjoy the language, and continue to use it.
"""


def Parse_Arguments(Arguments:List[str]) -> None:
    global FilePath
    if len(Arguments) == 3:
        print(f"Parsing Arguments:\n{[f'{Argument}' for Argument in Arguments]}")
        if Arguments[1] in ["c", "compile"]:
            if Arguments[2].endswith(".papple"):
                FilePath = Arguments[2]
                print(f"Building {FilePath}")
                Build()
            else:
                print("Iwa is presuming that Hope is calling it.")
                FilePath = Arguments[2]+".papple"
                ProjectInstance.Name = Arguments[2]
                print(f"Building {ProjectInstance.Name}")
                Build()
    elif len(Arguments) == 2:
        print(f"Parsing Arguments:\n{[f'{Argument}' for Argument in Arguments]}")
        if Check_For_Config():
            print("Using project configuration.")
        else:
            print("There is no project found.")
            exit()
    elif len(Arguments) == 1:
        print(HelpMessage)


def Compile_Source_File() -> bool:
    if ProjectInstance.Name != None:
        print("Woah, we got a project name")
        if exists(f"{ProjectInstance.Name}.exe"):
            remove(f"{ProjectInstance.Name}.exe")
        system(f"clang {ProjectInstance.Name}.c -o {ProjectInstance.Name}.exe")
        if exists(f"{ProjectInstance.Name}.exe"):
            return True
        else:
            return False
    else:
        if exists("test.exe"):
            remove("test.exe")
        system(f"clang untitled.c -o test")
        if exists("test.exe"):
            return True
        else:
            return False


def Check_For_Config() -> bool:
    if exists(".pappleConfig"):
        return True
    else:
        return False


def Build():
    print("Compiling from given path.")
    if ProjectInstance.Name == None:
        print(f"Treating {FilePath} as main file.")
        print(f"Mutable Copy:\n{(Parse_Source_File(FilePath))}\n")
    else:
        print(f"Treating {ProjectInstance.Name} as main file.")
        print(f"Mutable Copy:\n{(Parse_Source_File(FilePath))}\n")
    print(f"Compiling...")
    if Compile_Source_File() == True:
        print(f"Running...")
        if ProjectInstance.Name != None:
            system(ProjectInstance.Name)
        else:
            system("test")


if __name__ == "__main__":
    Pretty_Wrap("~~~ Smile away, we're alive today. ~~~")
    Parse_Arguments(Arguments)