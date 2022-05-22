from os import path, removedirs, remove, getcwd
from sys import argv, dont_write_bytecode
from re import search
from glob import glob

from Iwa_Utilities.Utilities_Declarations import *

User_Arguments = argv

def CommandParsing():

    print(NEWLINE + "-Command parsing stage-")
    if len(User_Arguments) == 1: 
        print("No commands given, you can use `Iwa -h` to ask for help")
        return "No commands given"
    elif len(User_Arguments) == 2:
        print("Compilation")
        return "Compilation"
    elif len(User_Arguments) >= 3:
        print("Interpretation with settings")
        return "Interpretation with settings"
    else:
        print("Error in CommandParsing()")
        return "Error in CommandParsing()"

CommandParsingReturn = CommandParsing()
print(CommandParsingReturn)

def PappleConfirmation():
    print(NEWLINE + "-Pineapple file confirmation stage-")
    if CommandParsingReturn != "Error in CommandParsing()" and CommandParsingReturn != "No commands given":
        if search("^.+\.(?:papple)", User_Arguments[1]):
            return "This is indeed a .papple file"
        else:
            print("Error in PappleConfirmation(), you are not using a proper .papple file, take a look at the files name, or how you typed it.")
            return "Error in PappleConfirmation()"
    else:
        print("PappleConfirmation Error: I don't know how you failed enough to get this far")
        return "PappleConfirmation Error: I don't know how you failed enough to get this far"

if CommandParsingReturn:
    PappleConfirmationReturn = PappleConfirmation()

else:
    print("Error in executing PappleConfirmation()")

print(PappleConfirmationReturn)

def FileReading():

    print(NEWLINE + "-File Reading Stage-")

    if CommandParsingReturn != "Error in CommandParsing()" and PappleConfirmationReturn != "Error in PappleConfirmation()":
        
        if path.exists(argv[1]):

            with open(argv[1]) as PappleFile:
                
                PappleFileData = PappleFile.read()
                print(NEWLINE + "-Printing out source code-", NEWLINE)
                print(PappleFileData)
                print("-End of Source Code-", NEWLINE)
            
                return "Reading File"
        
        else:

            return "File selected for compilation doesn't seem to exist"

    elif CommandParsingReturn == "Error in CommandParsing()":

        return "CommandParsing() did not return a non-error result"

    elif PappleConfirmationReturn == "Error in PappleConfirmation()":

        return "PappleConfirmation() did not return a non-error result"

    else:

        return "FileReading() Error: I don't know how you failed enough to get this far"

if PappleConfirmationReturn:

    FileReadingReturn = FileReading()

else:

    print("Error in executing PappleConfirmation()")

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
    PyCacheCleanUp()