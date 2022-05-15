from os import path, removedirs, remove, getcwd
from sys import argv, dont_write_bytecode
from re import search
from glob import glob

# Predefined constants for utility
NEWLINE = "\n"

User_Arguments = argv


# We need to analyze the given command
def CommandParsing():

    # Stage Identification
    print(NEWLINE + "-Command parsing stage-")

    # If no commands are given
    if len(User_Arguments) == 1:
        
        print("No commands given, you can use `py Lily.py -h` to ask for help")
        return "No commands given"

    # If we're doing plain compilation
    elif len(User_Arguments) == 2:
        
        print("Compilation")
        return "Compilation"

    # If we're doing compilation with settings
    elif len(User_Arguments) >= 3:

        print("Interpretation with settings")
        return "Interpretation with settings"

    # If there was some kind of error in parsing the command
    else:
        
        print("Error in CommandParsing()")
        return "Error in CommandParsing()"

# Command Parsing Data Store
CommandParsingReturn = CommandParsing()
print(CommandParsingReturn)

# We need to confirm that a .papple file is being targeted
def PappleConfirmation():

    # Stage Identification
    print(NEWLINE + "-Pineapple file confirmation stage-")

    # If CommandParsing() return a non-error result,
    # then go through confirming that we're targeting
    # a .papple file
    if CommandParsingReturn != "Error in CommandParsing()" and CommandParsingReturn != "No commands given":

        # We're using regular expression to search through the given string
        if search("^.+\.(?:papple)", User_Arguments[1]):
            
            return "This is indeed a .papple file"

        # If we fail to confirm that you are targeting a .papple file, 
        # return error
        else:

            print("Error in PappleConfirmation(), you are not using a proper .papple file, take a look at the files name, or how you typed it.")
            return "Error in PappleConfirmation()"

    # This is here to keep track of out-of-bounds errors
    else:

        print("PappleConfirmation Error: I don't know how you failed enough to get this far")
        return "PappleConfirmation Error: I don't know how you failed enough to get this far"

# As long as we didn't have a `None` value return by CommandParsing(), execute PappleConfirmation()
if CommandParsingReturn:
    PappleConfirmationReturn = PappleConfirmation()

# If for some reason we were not able to execute PappleConfirmation(), raise error
else:
    print("Error in executing PappleConfirmation()")

# Print out the PappleConfirmation() return for user | make optional later, and turn into a pretty print
print(PappleConfirmationReturn)

# We need to read the file, and extract data from it
def FileReading():

    # Stage Identification
    print(NEWLINE + "-File Reading Stage-")

    # If CommandParsing() and PappleConfirmation() return a non-error result, move on
    if CommandParsingReturn != "Error in CommandParsing()" and PappleConfirmationReturn != "Error in PappleConfirmation()":
        
        # If the file or path-to-file exists, we will move on
        if path.exists(argv[1]):

            # Open file for reading
            with open(argv[1]) as PappleFile:
                
                # Extract the content, and print it | we'll pretty print this later, and make it optional
                PappleFileData = PappleFile.read()
                print(NEWLINE + "-Printing out source code-")
                print(PappleFileData)
                print("-End of Source Code-" + NEWLINE)
            
                return "Reading File"
        
        # If the file or path-to-file doesn't exist, we return an error
        else:

            return "File selected for compilation doesn't seem to exist"

    # If there was some kind of error in CommandParsing() not caught earlier, we make sure to pop it here
    elif CommandParsingReturn == "Error in CommandParsing()":

        return "CommandParsing() did not return a non-error result"

    # If there was some kind of error in PineappleConfirmation() not caught earlier, we make sure to pop it here
    elif PappleConfirmationReturn == "Error in PappleConfirmation()":

        return "PappleConfirmation() did not return a non-error result"

    # This is here to keep track of out-of-bounds errors
    else:

        return "FileReading() Error: I don't know how you failed enough to get this far"

# As long as we didn't have a `None` value return by CommandParsing() and PappleConfirmation(), execute PappleConfirmation()
if PappleConfirmationReturn:

    FileReadingReturn = FileReading()

# If for some reason we were not able to execute FileReading(), raise error
else:

    print("Error in executing PappleConfirmation()")

print(FileReadingReturn)

def PyCacheCleanUp():
    print("\n\nCommencing PyCache Cleanup")
    Project_Path = getcwd()
    pyCacheFiles = glob(Project_Path + "\**\*.pyc", recursive = True)
    pyCacheFolders = glob(Project_Path + "\**\__pycache__", recursive = True)
    for file in pyCacheFiles:
        try:
            print(file)
            remove(file)
        except:
            print("Error removing .pyc files.")
    for dir in pyCacheFolders:
        try:
            print(dir)
            removedirs(dir)
        except:
            print("Error removing _pycache__ directories.")
PyCacheCleanUp()