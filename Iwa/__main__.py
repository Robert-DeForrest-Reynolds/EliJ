# Type ignore comments are because VSCode kinda sucks.
from io import TextIOWrapper # type: ignore
from typing import List # type: ignore
from typing import Dict # type:  ignore
from sys import argv as Arguments
from os import system, remove
from os.path import exists # type:ignore
from Error import ERROR
from Generators import Generate_Printf_Function, Generate_Integer_Variable
from Helpers import Pretty_Wrap
from Writers import Write_Instruction, Write_Prefab
from Project import Project


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

def Cut_Tabspace(SourceFileData:List[str]) -> str:
    for LineIndex, Line in enumerate(SourceFileData):
        for CharacterIndex, Character in enumerate(Line):
            if Character != " " and CharacterIndex == 0:
                break
            elif Character != " " and CharacterIndex >= 1:
                SourceFileData[LineIndex] = Line[CharacterIndex:]
                break
    return SourceFileData


def Check_For_Instructions(SourceFileData:List[str]) -> None:
    for Line in SourceFileData:
        for Keyword in Variables.keys():
            if Line.startswith(Keyword):
                VariableSplit = [Element.strip() for Element in Line.split("=")]
                DataSplit = VariableSplit[0].split(" ")
                DataType = DataSplit[0]
                Name = DataSplit[1]
                Value = VariableSplit[1]
                GlobalVariableMapping.update({Name: DataType})
                Variable = Variables[DataType](GlobalVariableMapping, Name, Value)
                Write_Instruction(ProjectInstance, Variable)

        for Keyword in Functions.keys():
            if Line.startswith(Keyword):
                FunctionSplit = Line.split("(")
                OpenParanIndex = Line.find("(")
                CloseParanIndex = len(Line) - Line[::-1].find(")")
                PotentialInstruction = FunctionSplit[0]
                Instruction = Functions[PotentialInstruction](GlobalVariableMapping, Line[OpenParanIndex+1:CloseParanIndex-1])
                Write_Instruction(ProjectInstance, Instruction)


def Cut_Functions(SourceFileDataAsString:str) -> List[str]:
    FunctionStartIndex = None
    for Index, Character in enumerate(SourceFileDataAsString):
        if Index > 2:
            Cursor = "".join([SourceFileDataAsString[Index-3], SourceFileDataAsString[Index-2], SourceFileDataAsString[Index-1], Character])
            if Cursor == "Func":
                FunctionStartIndex = Index-3
        if FunctionStartIndex != None:
            if Character == "}":
                FunctionEndIndex = Index
                Function:str = SourceFileDataAsString[FunctionStartIndex:FunctionEndIndex+1]
                if Verify_Function(Function) == True:
                    SourceFileDataAsString = SourceFileDataAsString.replace(Function, "")
                    ParamStart = Find_ParamStart(Function)
                    FunctionName = Function[:ParamStart].split(" ")[1]
                    BodyStart = Find_BlockStart(Function)
                    FunctionBody = Function[BodyStart:]
                    FunctionsMapping.update({FunctionName:FunctionBody})
                    return SourceFileDataAsString


def Find_ParamStart(Content:str):
    for Index, Character in enumerate(Content):
        if Character == "(":
            return Index


def Find_BlockStart(Content:str):
    for Index, Character in enumerate(Content):
        if Character == "{":
            return Index


def Verify_Function(Function:str) -> bool:
    if Function.count("(") != Function.count(")"):
        print("Missing paranthesis")
        return False
    if Function.count("{") != Function.count("}"):
        print("Missing bracket")
        return False
    return True


def Parse_Source_File(SourceFilePath:str) -> str | List[str]:
    with open(SourceFilePath, 'r') as SourceFile:
        SourceFileLines:List[str] = SourceFile.readlines()

    Write_Prefab(ProjectInstance)

    # Instructions = Function Calls, and Operators Usage
    # Steppage: Functions, Variables, Instructions
    # Functions get stripped from the SourceFileData first

    SourceFileDataAsString = "".join(SourceFileLines).replace("\n", "")
    SourceFileDataAsString = Cut_Functions(SourceFileDataAsString)
    SourceFileData = [Line for Line in "".join(SourceFileLines).replace("\n", "").split(";") if Line != ""]

    print(f"Source File Data String: {SourceFileDataAsString}")

    MutableCopy = SourceFileData
    MutableCopy = Cut_Tabspace(SourceFileData)

    Check_For_Instructions(SourceFileData)

    if type(MutableCopy) is ERROR: return MutableCopy.Report
    
    return MutableCopy


def Compile_Source_File() -> bool:
    if ProjectInstance.Name is not None:
        pass
    else:
        if exists("test.exe"):
            remove("test.exe")
        system(f"clang untitled.c -o test")
        if exists("test.exe"):
            return True
        else:
            return False


def Parse_Arguments(Arguments:List[str]) -> None:
    global FilePath
    print(f"Parsing Arguments:\n{[f'{Argument}' for Argument in Arguments]}")
    if len(Arguments) == 3:
        if Arguments[1] in ["c", "compile"]:
            FilePath = Arguments[2]
            print(f"Building {FilePath}")
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
    print(f"Mutable Copy:\n{(Parse_Source_File(FilePath))}\n")
    print(f"Compiling...")
    if Compile_Source_File() == True:
        print(f"Running...")
        system("test")


if __name__ == "__main__":
    Pretty_Wrap("~~~ Smile away, we're alive today. ~~~")
    Parse_Arguments(Arguments)