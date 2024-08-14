# Type ignore comments are because VSCode kinda sucks.
from io import TextIOWrapper # type: ignore
from typing import List # type: ignore
from typing import Tuple # type: ignore
from typing import Dict # type:  ignore
from sys import argv as Arguments
from os import system
from os.path import exists # type:ignore
from Error import ERROR
from Generators import Generate_Printf_Function
from Helpers import Pretty_Wrap
from Writers import Write_Instruction, Write_Prefab
from Project import Project


global ProjectInstance
ProjectInstance = Project()

global FilePath
FilePath = None

ReservedKeywords:List[str] = {
    "Out": Generate_Printf_Function,
}

StringPositions:Dict[str,List[int]] = {}

def Cut_Tabspace(SourceFileLines:List[str]) -> str:
    LineIndex:int
    Line:str
    for LineIndex, Line in enumerate(SourceFileLines):
        CharacterIndex:int
        Character:str
        for CharacterIndex, Character in enumerate(Line):
            if Character != " " and CharacterIndex == 0:
                break
            elif Character != " " and CharacterIndex >= 1:
                SourceFileLines[LineIndex] = Line[CharacterIndex:]
                break
    return SourceFileLines


def Check_For_Instructions(SourceFileLines:List[str]):
    Line:str
    for Line in SourceFileLines:
        PotentialInstructionSplit = Line.split("(")
        OpenParanIndex = Line.find("(")
        CloseParanIndex = len(Line) - Line[::-1].find(")")
        if len(PotentialInstructionSplit) > 0:
            PotentialInstruction = PotentialInstructionSplit[0]
            if PotentialInstruction in ReservedKeywords.keys():
                Instruction = ReservedKeywords[PotentialInstruction](Line[OpenParanIndex+1:CloseParanIndex-1])
                Write_Instruction(ProjectInstance, Instruction)


def Parse_Source_File(SourceFilePath:str) -> str | List[str]:
    SourceFile:TextIOWrapper
    with open(SourceFilePath, 'r') as SourceFile:
        SourceFileLines:List[str] = SourceFile.readlines()

    Write_Prefab(ProjectInstance)

    MutableCopy = SourceFileLines
    MutableCopy = Cut_Tabspace(SourceFileLines)

    Check_For_Instructions(SourceFileLines)

    if type(MutableCopy) is ERROR: return MutableCopy.Report
    
    return MutableCopy


def Compile_Source_File():
    if ProjectInstance.Name is not None:
        pass
    else:
        system(f"clang untitled.c -o test")


def Parse_Arguments(Arguments:List[str]) -> None:
    global FilePath
    print(f"Parsing Arguments:\n{[f'{Argument}' for Argument in Arguments]}")
    if len(Arguments) == 3:
        if Arguments[1] in ["c", "compile"]:
            FilePath = Arguments[2]
            Build()
    elif len(Arguments) == 2:
        if Check_For_Config():
            print("Using project configuration.")
        else:
            print("There is no project found.")
            exit()


def Check_For_Config() -> bool:
    if exists(".pappleConfig"):
        return True
    else:
        return False


def Build():
    print("Compiling from given path.")
    print(f"Treating {FilePath} as main file.")
    print(f"Mutable Copy:\n{Parse_Source_File(FilePath)}\n")
    print(f"Compiling...")
    Compile_Source_File()
    print(f"Running...")
    system("test")


if __name__ == "__main__":
    WelcomeMessage:str = "~~~ Smile away, we're alive today. ~~~"
    Pretty_Wrap(WelcomeMessage)
    Parse_Arguments(Arguments)