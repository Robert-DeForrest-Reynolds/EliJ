from Iwa import Compiler

from typing import List # type: ignore
from Error import ERROR
from Writers import Write_Instruction, Write_Prefab


def Cut_Tabspace(SourceFileData:List[str]) -> List[str]:
    for LineIndex, Line in enumerate(SourceFileData):
        for CharacterIndex, Character in enumerate(Line):
            if Character != " " and CharacterIndex == 0:
                break
            elif Character != " " and CharacterIndex >= 1:
                SourceFileData[LineIndex] = Line[CharacterIndex:]
                break
    return SourceFileData


def Check_For_Instructions(Iwa:Compiler, SourceFileData:List[str]) -> None:
    for Line in SourceFileData:
        for Keyword in Iwa.Variables.keys():
            if Line.startswith(Keyword):
                VariableSplit = [Element.strip() for Element in Line.split("=")]
                DataSplit = VariableSplit[0].split(" ")
                DataType = DataSplit[0]
                Name = DataSplit[1]
                Value = VariableSplit[1]
                Iwa.GlobalVariableMapping.update({Name: DataType})
                Variable = Iwa.Variables[DataType](Iwa.GlobalVariableMapping, Name, Value)
                Write_Instruction(Iwa, Variable)

        for Keyword in Iwa.Functions.keys():
            if Line.startswith(Keyword):
                FunctionSplit = Line.split("(")
                OpenParanIndex = Line.find("(")
                CloseParanIndex = len(Line) - Line[::-1].find(")")
                PotentialInstruction = FunctionSplit[0]
                Instruction = Iwa.Functions[PotentialInstruction](Iwa.GlobalVariableMapping, Line[OpenParanIndex+1:CloseParanIndex-1])
                Write_Instruction(Iwa, Instruction)


def Cut_Functions(Iwa:Compiler, SourceFileDataAsString:str) -> List[str]:
    FunctionStartIndex = None
    for Index, Character in enumerate(SourceFileDataAsString):
        if Index > 1:
            Cursor = "".join([SourceFileDataAsString[Index-2], SourceFileDataAsString[Index-1], Character])
            if Cursor == "Fnc":
                FunctionStartIndex = Index-2
        if FunctionStartIndex != None:
            if Character == "}":
                FunctionEndIndex = Index
                Function:str = SourceFileDataAsString[FunctionStartIndex:FunctionEndIndex+1]
                if Verify_Function(Function) == True:
                    SourceFileDataAsString = SourceFileDataAsString.replace(Function, "")
                    ParamStart = Find_Param_Start(Function)
                    FunctionName = Function[:ParamStart].split(" ")[1]
                    BodyStart = Find_BlockStart(Function)
                    FunctionBody = Function[BodyStart:]
                    Iwa.FunctionsMapping.update({FunctionName:FunctionBody})
                    return SourceFileDataAsString


def Find_Param_Start(Content:str):
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


def Cut_Comments(MutableCopyDataAsString:str) -> List[str]:
    CommentStart = None
    for CharacterIndex, Character in enumerate(MutableCopyDataAsString):
        if Character == "#" and CommentStart == None:
            CommentStart = CharacterIndex
        elif Character == "#" and CommentStart != None:
            CommentEnd = CharacterIndex
            if CommentStart == 0:
                MutableCopyDataAsString = MutableCopyDataAsString[CommentEnd+1:]
            else:
                # Comment = MutableCopyDataAsString[CommentStart:CommentEnd]
                FirstHalf = MutableCopyDataAsString[CommentStart:]
                SecondHalf = MutableCopyDataAsString[:CommentEnd]
                print("Commentless: ", FirstHalf)
    return MutableCopyDataAsString



def Parse_Source_File(Iwa:Compiler) -> str | List[str]:
    with open(Iwa.FilePath, 'r') as SourceFile:
        SourceFileLines:List[str] = SourceFile.readlines()

    Write_Prefab(Iwa)

    # Instructions = Function Calls, and Operators Usage
    # Steppage: Functions, Variables, Instructions
    # Functions get stripped from the SourceFileData first

    SourceFileDataAsString = "".join(SourceFileLines).replace("\n", "")
    SourceFileDataAsString = Cut_Functions(Iwa, SourceFileDataAsString)
    print(f"Source File Data String: {SourceFileDataAsString}")

    SourceFileData = [Line for Line in "".join(SourceFileLines).replace("\n", "").split(";") if Line != ""]

    MutableCopy = SourceFileData
    MutableCopy = Cut_Tabspace(SourceFileData)
    MutableCopy = "".join(SourceFileLines).replace("\n", "")
    MutableCopy = Cut_Comments(MutableCopy)

    Check_For_Instructions(Iwa, [Line for Line in MutableCopy.split(";") if Line != ""])

    if type(MutableCopy) is ERROR: return MutableCopy.Report
    
    return MutableCopy