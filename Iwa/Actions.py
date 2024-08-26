from Iwa import Compiler

from os import system, remove
from os.path import exists # type:ignore
from typing import List # type: ignore

from Parser import Parse_Source_File

def Check_For_Config() -> bool:
    if exists(".pappleConfig"):
        return True
    else:
        return False


def Compile_Source_File(Iwa:Compiler) -> bool:
    if Iwa.ProjectInstance.Name != None:
        print("Woah, we got a project name")
        if exists(Iwa.EXEPath):
            remove(f"{Iwa.DirectoryPath}/{Iwa.ProjectInstance.Name}.exe")
        system(f"clang {Iwa.DirectoryPath}/{Iwa.ProjectInstance.Name}.c -o {Iwa.EXEPath}")
        if exists(f"{Iwa.EXEPath}"):
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


def Build(Iwa:Compiler):
    print("Compiling from given path.")
    if Iwa.ProjectInstance.Name == None:
        print(f"Treating {Iwa.FilePath} as main file.")
        print(f"Mutable Copy:\n{(Parse_Source_File(Iwa))}\n")
    else:
        print(f"Treating {Iwa.ProjectInstance.Name} as main file.")
        print(f"Mutable Copy:\n{(Parse_Source_File(Iwa))}\n")
    print(f"Compiling...")
    if Compile_Source_File() == True:
        print(f"Running...")
        if Iwa.EXEPath != None:
            system(Iwa.EXEPath)
        else:
            system("test")

def Zero_Argument(Iwa:Compiler, Arguments) -> None:
    print(Iwa.HelpMessage)


def Single_Flag_Argument(Iwa:Compiler, Arguments:List[str]) -> None:
    print(f"Parsing Arguments:\n{[f'{Argument}' for Argument in Arguments]}")
    if Check_For_Config():
        print("Using project configuration.")
    else:
        print("There is no project found.")
        exit()
    

def Project_Action(Iwa:Compiler, Arguments:List[str]) -> None:
    IwaCall:str = Arguments[0]
    Flag:str = Arguments[1]
    ProjectPath:str = Arguments[2]
    print(f"Parsing Arguments:\n{[f'{Argument}' for Argument in Arguments]}")
    if Arguments[1] in ["c", "compile"]:
        print(f"Building {Iwa.ProjectInstance.Name}")
        # If we give the file
        if Arguments[2].endswith(".papple"):
            print(f"Building {Iwa.ProjectInstance.Name}")
            PathSplit:List[str] = Arguments[2].split("/")
            Iwa.ProjectInstance.Name = PathSplit[len(PathSplit)-1]
            Iwa.DirectoryPath = PathSplit
            Iwa.FilePath = Arguments[2]
            Iwa.EXEPath = f"{Iwa.DirectoryPath}/{Iwa.ProjectInstance.Name}.exe"
            Build(Iwa)
        # If we give the directory, and/or Hope is calling Iwa
        else:
            print("Iwa is presuming that Hope is calling it.")
            PathSplit:List[str] = Arguments[2].split("/")
            Iwa.ProjectInstance.Name = PathSplit[len(PathSplit)-1]
            Iwa.DirectoryPath = Arguments[2]
            Iwa.FilePath = Arguments[2]+f"/{Iwa.ProjectInstance.Name}.papple"
            Iwa.EXEPath = f"{Iwa.DirectoryPath}/{Iwa.ProjectInstance.Name}.exe"
            print(Iwa.EXEPath)
            Build(Iwa)