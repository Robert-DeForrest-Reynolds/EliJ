from sys import argv
from re import search

def CommandParsing():

    print("-Command parsing stage-")

    if len(argv) == 1:
        
        print("No commands given, you can use `py Lily.py -h` to ask for help")
        return "No commands given"

    elif len(argv) == 2:
        
        print("Interpretation")
        return "Interpretation"

    elif len(argv) == 3:

        print("Interpretation with settings")
        return "Interpretation with settings"

    else:
        
        print("Error in CommandParsing()")
        return "Error in CommandParsing()"

CommandParsingReturn = CommandParsing()
print(CommandParsingReturn)

def PappleConfirmation():

    print("-Pineapple file confirmation stage-")

    if CommandParsingReturn != "Error in CommandParsing()" and CommandParsingReturn != "No commands given":

        if search("^.+\.(?:papple)", argv[1]):
            
            return "This is indeed a .papple file\n"

        else:

            print("Error in PappleConfirmation(), you are not using a proper .papple file, take a look at the files name, or how you typed it.")
            return "Error in PappleConfirmation()\n"

    elif CommandParsingReturn == "Error in CommandParsing()":

        return "Error in CommandParsing() detected by PappleConfirmation()"

    elif CommandParsingReturn == "No commands given":

        return "No commands given detected by PappleConfirmation()"

    else:

        print("PappleConfirmation Error: I don't know how you failed enough to get this far")
        return "PappleConfirmation Error: I don't know how you failed enough to get this far"

if CommandParsingReturn:
    PappleConfirmationReturn = PappleConfirmation()
else:
    print("Error in executing PappleConfirmation()")
print(PappleConfirmationReturn)

def FileReading():

    print("-File Reading Stage-")

    if CommandParsingReturn != "Error in CommandParsing()" and PappleConfirmationReturn != "Error in PappleConfirmation()":

        with open() as PappleFile:

            PappleFileData = PappleFile.read()
            print(PappleFileData)

    elif CommandParsingReturn == "Error in CommandParsing()":

        return "CommandParsing() did not return a non-error result"

    elif PappleConfirmationReturn == "Error in CommandParsing()":

        return "PappleConfirmation() did not return a non-error result"

    else:

        return "FileReading() Error: I don't know how you failed enough to get this far\n"

if __name__ == "__main__":
    print("Lily.py ran")