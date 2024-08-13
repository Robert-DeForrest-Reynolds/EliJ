# Type ignore comments are because VSCode kinda sucks.
from io import TextIOWrapper # type: ignore
from typing import List # type: ignore
from typing import Tuple # type: ignore
from typing import Dict # type:  ignore
from sys import argv as Arguments
from os import system

class ERROR:
    def __init__(Self, Report:str) -> None: Self.Report:str = Report


global ProjectName
ProjectName = None
global FilePath
FilePath = None


C_PREFAB = "#include <stdio.h>\nint main() {\n}"


def Generate_Printf_Function(Contents:str) -> str:
    return f'printf({Contents});'


ReservedKeywords:List[str] = {
    "Out": Generate_Printf_Function,
}


StringPositions:Dict[str,List[int]] = {}


def Write_Prefab():
    print("Writing Prefab...")
    if ProjectName is not None:
        print(f"Using project name: {ProjectName}\n")
        with open(f"{ProjectName}.c", 'w+') as CFile:pass
    else:
        print("WARNING: No project name given.\n")
        with open("untitled.c", 'w+') as CFile:
            CFile.write(C_PREFAB)


def Generate_Instruction(Parameters, Instruction) -> None:
    if ProjectName is not None:
        with open(f"{ProjectName}.c", 'r') as CFile:
            CurrentLines:List[str] = CFile.readlines()
        with open(f"{ProjectName}.c", 'w') as CFile:
            EndLineIndex:int = len(CurrentLines)-2
            CurrentLines.insert(EndLineIndex, ReservedKeywords[Instruction](Parameters))
            CFile.write("".join(CurrentLines))
    else:
        with open("untitled.c", 'r') as CFile:
            CurrentLines:List[str] = CFile.readlines()
        with open("untitled.c", 'w') as CFile:
            EndLineIndex:int = len(CurrentLines)-1
            CurrentLines.insert(EndLineIndex, ReservedKeywords[Instruction](Parameters))
            CFile.write("".join(CurrentLines))


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
                Generate_Instruction(Line[OpenParanIndex+1:CloseParanIndex-1], PotentialInstruction)


def Parse_Source_File(SourceFilePath:str) -> str | List[str]:
    SourceFile:TextIOWrapper
    with open(SourceFilePath, 'r') as SourceFile:
        SourceFileLines:List[str] = SourceFile.readlines()

    Write_Prefab()

    MutableCopy = SourceFileLines
    MutableCopy = Cut_Tabspace(SourceFileLines)

    Check_For_Instructions(SourceFileLines)

    if type(MutableCopy) is ERROR: return MutableCopy.Report
    
    return MutableCopy


def Compile_Source_File():
    if ProjectName is not None:
        pass
    else:
        system(f"clang untitled.c -o test")


def Parse_Arguments(Arguments:List[str]) -> None:
    global ProjectName
    global FilePath
    print(f"Parsing Arguments:\n{[f'{Argument}' for Argument in Arguments]}")
    if len(Arguments) == 2:
        FilePath = Arguments[1]
        print("")
        print(f"Mutable Copy:\n{Parse_Source_File(FilePath)}\n")
        print(f"Compiling...")
        Compile_Source_File()
        print(f"Running...")
        system("test")
    elif len(Arguments) == 3:
        ProjectName = Arguments[2]


def Pretty_Wrap(Message:str):
    MessageLength:int = len(Message)
    Wrapper:str = "-"*MessageLength
    print(f"{Wrapper}\n{Message}\n{Wrapper}")


if __name__ == "__main__":
    WelcomeMessage:str = "~~~ Smile away, we're alive today. ~~~"
    Pretty_Wrap(WelcomeMessage)
    Parse_Arguments(Arguments)