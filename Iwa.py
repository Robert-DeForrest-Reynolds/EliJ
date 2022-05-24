from os import removedirs, remove, getcwd, listdir
from sys import argv
from re import search
from glob import glob

from Iwa_Utilities.Utilities_Declarations import *
from Iwa_Utilities.Exceptions import *

Argument_Count = len(argv)
Arguments = argv
Project_Name = Arguments[1]

def CommandParsing():
    if Argument_Count >= 2:
        print("Compilation")
        Compilation = True
        return Compilation
    else:
        return ZeroArgumentsGiven(Arguments, Argument_Count)
    
def Parsing():
    Papple_Files = glob(Project_Name + "\*.papple", recursive = True)

    for File in Papple_Files:
        print("Found: ", File, "and Reading it")
        with open(File, 'r') as Papple_File:
            for Line in Papple_File:
                print(Line)

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

Parsing()

PyCacheCleanUp()