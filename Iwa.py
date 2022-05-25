from ast import Import
from os import removedirs, remove, getcwd, listdir
from sys import argv
from glob import glob
from re import search

from Iwa_Utilities.Utilities_Declarations import *
from Iwa_Utilities.Exceptions import *

Argument_Count = len(argv)
Arguments = argv
Project_Name = Arguments[1]



Four_Spaces = "    "
Eight_Spaces = "        "

Import_Statement = "Import"

Open_Block = "("
Close_Block = ")"

String_Wrapper = "\""

Output_Function = "Output"

Keywords = (
    Four_Spaces,
    Eight_Spaces,
    Open_Block,
    Close_Block,
    String_Wrapper,
    Import_Statement,
    Output_Function
)

def CommandParsing():
    if Argument_Count >= 2:
        print("Compilation")
        Compilation = True
        return Compilation
    else:
        return ZeroArgumentsGiven(Arguments, Argument_Count)

def FormString(Data):
    Formed_String = Data
    for Keyword in Keywords:
        if Keyword in Data:
            Data = Data.replace(Keyword, "")
    return Data

def Compile():

    Papple_Files = glob(Project_Name + "\*.papple", recursive = True)

    File_Count = 0
    Line_Count = 0

    for File in Papple_Files:
        File_Count += 1
        with open(File, 'r') as Papple_File:
            Papple_File_Lines = Papple_File.readlines()
            for Line in Papple_File_Lines:
                Line_Count += 1
                if Line.startswith(Import_Statement):
                    Imports = []
                    Next_Line_Index = (Papple_File_Lines.index(Line)+1)
                    Next_Line = Papple_File_Lines[Next_Line_Index]
                    while Next_Line.startswith(Four_Spaces) or Next_Line.startswith(Eight_Spaces):
                        Imports.append(Next_Line.replace("    ", ""))
                        Next_Line_Index += 1
                        Next_Line = Papple_File_Lines[Next_Line_Index]
                if Line.startswith(Output_Function):
                    print(FormString(Line))

def PyCacheCleanUp():
    print("\nCommencing PyCache Cleanup from Iwa")
    Project_Path = getcwd()
    pyCacheFiles = glob(Project_Path + "\**\*.pyc", recursive = True)
    pyCacheFolders = glob(Project_Path + "\**\__pycache__", recursive = True)
    for File in pyCacheFiles:
        try:
            remove(File)
        except:
            print("Error removing .pyc files.")
    for Directory in pyCacheFolders:
        try:
            removedirs(Directory)
        except:
            print("Error removing _pycache__ directories.")

PyCacheCleanUp()