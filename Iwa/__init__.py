from typing import List, Dict # type: ignore
from os.path import exists # type: ignore
from os import remove # type: ignore
from subprocess import run # type: ignore

from Iwa.Writers import Write_Instruction, Write_Prefab

class Project:
    def __init__(Self, Name=None) -> None:
        Self.Name = Name

class ERROR:
    def __init__(Self, Report:str) -> None: Self.Report:str = Report

class Iwa:
    def __init__(Self, Arguments):
        Self.DEV = False
        Self.ProjectInstance = Project()
        Self.DirectoryPath = None
        Self.FilePath = None
        Self.EXEPath = None
        Self.GlobalVariableMapping = {}
        Self.FunctionsMapping:Dict[str,str] = {}
        
        Self.Arguments = Arguments
        Self.ArgumentCount = len(Arguments)

        Self.Functions:List[str] = {
            "Out": Self.Generate_Printf_Function,
        }
        Self.Variables:List[str] = {
            "Int": Self.Generate_Integer_Variable,
        }

        Self.StringPositions:Dict[str,List[int]] = {}

        Self.HelpMessage = """\
Iwa is the compiler for the Pineapple programming language, by Robert Lawrence DeForrest Reynolds.

I thank you for using this, and I hope you enjoy the language, and continue to use it.
"""

        Self.Parse_Arguments()


    def Cut_Tabspace(Self, SourceFileData:List[str]) -> List[str]:
        for LineIndex, Line in enumerate(SourceFileData):
            for CharacterIndex, Character in enumerate(Line):
                if Character != " " and CharacterIndex == 0:
                    break
                elif Character != " " and CharacterIndex >= 1:
                    SourceFileData[LineIndex] = Line[CharacterIndex:]
                    break
        return SourceFileData


    def Check_For_Instructions(Self, SourceFileData:List[str]) -> None:
        for Line in SourceFileData:
            for Keyword in Self.Variables.keys():
                if Line.startswith(Keyword):
                    VariableSplit = [Element.strip() for Element in Line.split("=")]
                    DataSplit = VariableSplit[0].split(" ")
                    DataType = DataSplit[0]
                    Name = DataSplit[1]
                    Value = VariableSplit[1]
                    Self.GlobalVariableMapping.update({Name: DataType})
                    Variable = Self.Variables[DataType](Self.GlobalVariableMapping, Name, Value)
                    Write_Instruction(Self, Variable)

            for Keyword in Self.Functions.keys():
                if Line.startswith(Keyword):
                    FunctionSplit = Line.split("(")
                    OpenParanIndex = Line.find("(")
                    CloseParanIndex = len(Line) - Line[::-1].find(")")
                    PotentialInstruction = FunctionSplit[0]
                    Instruction = Self.Functions[PotentialInstruction](Self.GlobalVariableMapping, Line[OpenParanIndex+1:CloseParanIndex-1])
                    Write_Instruction(Self, Instruction)


    def Cut_Functions(Self, SourceFileDataAsString:str) -> List[str]:
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
                    if Self.Verify_Function(Function) == True:
                        SourceFileDataAsString = SourceFileDataAsString.replace(Function, "")
                        ParamStart = Self.Find_Param_Start(Function)
                        FunctionName = Function[:ParamStart].split(" ")[1]
                        BodyStart = Self.Find_BlockStart(Function)
                        FunctionBody = Function[BodyStart:]
                        Self.FunctionsMapping.update({FunctionName:FunctionBody})
                        return SourceFileDataAsString


    def Find_Param_Start(Self, Content:str):
        for Index, Character in enumerate(Content):
            if Character == "(":
                return Index


    def Find_BlockStart(Self, Content:str):
        for Index, Character in enumerate(Content):
            if Character == "{":
                return Index


    def Verify_Function(Self, Function:str) -> bool:
        if Function.count("(") != Function.count(")"):
            print("Missing paranthesis")
            return False
        if Function.count("{") != Function.count("}"):
            print("Missing bracket")
            return False
        return True


    def Cut_Comments(Self, MutableCopyDataAsString:str) -> List[str]:
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


    def Parse_Source_File(Self) -> str | List[str]:
        with open(Self.FilePath, 'r') as SourceFile:
            SourceFileLines:List[str] = SourceFile.readlines()

        Write_Prefab(Self)

        # Instructions = Function Calls, and Operators Usage
        # Steppage: Functions, Variables, Instructions
        # Functions get stripped from the SourceFileData first

        SourceFileDataAsString = "".join(SourceFileLines).replace("\n", "")
        SourceFileDataAsString = Self.Cut_Functions(SourceFileDataAsString)

        if Self.DEV == True:
            print(f"Source File Data String: {SourceFileDataAsString}")

        SourceFileData = [Line for Line in "".join(SourceFileLines).replace("\n", "").split(";") if Line != ""]

        MutableCopy = SourceFileData
        MutableCopy = Self.Cut_Tabspace(SourceFileData)
        MutableCopy = "".join(SourceFileLines).replace("\n", "")
        MutableCopy = Self.Cut_Comments(MutableCopy)

        Self.Check_For_Instructions([Line for Line in MutableCopy.split(";") if Line != ""])

        if type(MutableCopy) is ERROR: return MutableCopy.Report
        
        return MutableCopy


    def Check_For_Config() -> bool:
        if exists(".pappleConfig"):
            return True
        else:
            return False


    def Compile_Source_File(Self) -> bool:
        if Self.ProjectInstance.Name != None:
            if exists(Self.EXEPath):
                remove(f"{Self.DirectoryPath}/{Self.ProjectInstance.Name}.exe")
            run(f"clang {Self.DirectoryPath}/{Self.ProjectInstance.Name}.c -o {Self.EXEPath}")
            if exists(f"{Self.EXEPath}"):
                return True
            else:
                return False
        else:
            if exists("test.exe"):
                remove("test.exe")
            run(f"clang untitled.c -o test")
            if exists("test.exe"):
                return True
            else:
                return False


    def Build(Self):
        if Self.ProjectInstance.Name == None:
            print(f"Treating {Self.FilePath} as main file.")
        else:
            print(f"Treating {Self.ProjectInstance.Name} as main file.")
        SourceFileContentsOutput = Self.Parse_Source_File()
        if Self.DEV == True:
            print(f"Source File Contents Output:\n{SourceFileContentsOutput}\n")
        print(f"Compiling...")
        if Self.Compile_Source_File() == True:
            print(f"Running...")
            if Self.EXEPath != None:
                run(Self.EXEPath)
            else:
                run("test")
        

    def Parse_Arguments(Self) -> None:
        if Self.Arguments[Self.ArgumentCount-1] == "dvt":
            Self.DEV = True
            print("Using Iwa in Developer Mode")
        print(f"Parsing Arguments:\n{[f'{Argument}' for Argument in Self.Arguments]}")
        if Self.ArgumentCount == 1:
            print(Self.HelpMessage)
        elif Self.Arguments[1] in ["c", "compile"]:
            if Self.ArgumentCount < 3:
                print("You didn't provide a path.")
                return
            if Self.Arguments[2].endswith(".papple"):
                PathSplit:List[str] = Self.Arguments[2].split("/")
                Self.ProjectInstance.Name = PathSplit[len(PathSplit)-1].replace(".papple", "")
                print(f"Building {Self.ProjectInstance.Name}")
                Self.DirectoryPath = Self.Arguments[2].replace(f"{Self.ProjectInstance.Name}.papple", "")
                Self.FilePath = Self.Arguments[2]
                Self.EXEPath = f"{Self.DirectoryPath}/{Self.ProjectInstance.Name}.exe"
                Self.Build()
            else:
                PathSplit:List[str] = Self.Arguments[2].split("/")
                Self.ProjectInstance.Name = PathSplit[len(PathSplit)-1]
                print(f"Building {Self.ProjectInstance.Name}")
                Self.DirectoryPath = Self.Arguments[2]
                Self.FilePath = Self.Arguments[2]+f"/{Self.ProjectInstance.Name}.papple"
                Self.EXEPath = f"{Self.DirectoryPath}/{Self.ProjectInstance.Name}.exe"
                Self.Build()


    def Generate_Printf_Function(Self, GlobalVariableMapping, Contents:str) -> str:
        if '"' in Contents:
            return f'printf({Contents});'
        elif GlobalVariableMapping[Contents] == "Int":
            return f'printf("%d", {Contents});'


    def Generate_Integer_Variable(Self, GlobalVariableMapping, Name:str, Value:str) -> str:
        return f"int {Name} = {Value};"