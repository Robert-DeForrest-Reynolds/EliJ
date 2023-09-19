from sys import argv as Arguments
from re import sub

from Log import Log

from CommentModule import CommentModule
from FindModule import FindModule
from FunctionModule import FunctionModule


class Peach:
    def __init__(Self):
        Self.SourceContent = None

        Self.Arguments = None
        Self.ArgumentCount = None
        Self.EntryFile = None

        Self.Parse_Arguments()
        Self.Extract_Contents()
        Self.Clear_Whitespace()


        """Turn SourceContent into a string, and then remove any whitespaces greater than 1."""
        Self.SourceContent = "".join(Self.SourceContent)
        Self.SourceContent = sub(" +", " ", Self.SourceContent)


        Self.Output_Intermediate_Language()

    
    def Output_Intermediate_Language(Self):
        with open(f"{Self.EntryFile}.Source.peach", 'w+') as OutputFile:
            OutputFile.write(str(Self.SourceContent))
        with open(f"{Self.EntryFile}.Finds.peach", 'w+') as OutputFile:
            OutputFile.write(str(Self.Finds))
        with open(f"{Self.EntryFile}.Functions.peach", 'w+') as OutputFile:
            OutputFile.write(str(Self.Functions))


    #Gets argument count given, and determines the given Entry File
    def Parse_Arguments(Self):
        Self.ArgumentCount = len(Arguments)
        if Self.ArgumentCount == 2:
            Self.EntryFile = Arguments[1]
            Self.Log(Function_Name=Self.Resolve_Find.__name__,
                             ArguementCount = Self.ArgumentCount,
                             EntryFile = Self.EntryFile)
        else:
            print("Zero arguments given.")

    #Open the entry file, and reads it's content as a list of lines
    def Extract_Contents(Self):
        Self.SourceContent = open(Self.EntryFile).readlines()
        

    #Clears any and all whitespace from the Database['Source Content']
    def Clear_Whitespace(Self):
        Self.SourceContent = [Line.strip("\n").strip(" ") for Line in Self.SourceContent if Line != "\n"]
        

    # Print out the functions in a readable way
    def Show_Functions(Self):
        print("\n".join(f"{Key}\n\t{Value}" for Key, Value in Self.Functions.items()))
