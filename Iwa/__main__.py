from os import removedirs, remove, getcwd, system
from sys import argv
from glob import glob
from re import search

from Utilities_Declarations import *
from Exceptions import *
from Pineapple_Language import *
from C_Language import *

Argument_Count = len(argv)
Arguments = argv

Project_Path = None
Project_Name = Project_Path

C_Code = []

def CommandParsing():
    if Argument_Count >= 2:
        global Project_Path
        Project_Path = Arguments[1]
        print("Compilation")
        Compilation = True
        BuildCFile()
        # Compile()
        return Compilation
    else:
        return ZeroArgumentsGiven(Arguments, Argument_Count)

def FormString(Data):
    for Keyword in Keywords:
        if Keyword in Data:
            Data = Data.replace(Keyword, "")
    return Data

def BuildCFile():

    Papple_Files = glob(Project_Path + "\*.papple", recursive = True)

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
                    for Import in Imports:
                        print(Import)
                        print(IO_Import)
                        if str(Import).strip() == IO_Import:
                            print("Found import")
                            C_Code.append(C_IO_Import)

                if Line.startswith(Output_Function):
                    pass
    
    print(C_Code)

def Compile():
    system("msys64\mingw64\\bin\\gcc {}\\temp.c -o {}\\{}".format(Project_Path, Project_Path, Project_Name))

def CompileAndRun():
    system("msys64\mingw64\\bin\\gcc {}\\temp.c".format(Project_Path))
    system(Project_Path + "\Temp")
    

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

if __name__ == '__main__':
    CommandParsing()
    PyCacheCleanUp()