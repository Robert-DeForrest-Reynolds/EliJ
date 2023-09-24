from sys import argv as Arguments, exit
from re import sub

from Log import Log

class Peach:
    def __init__(Self):
        Self.SourceContent:str = None

        Self.CommentFound = True
        Self.FunctionFound = True

        Self.Arguments = None
        Self.Flags = None
        Self.ArgumentCount = None

        Self.EntryFile = None

        Self.Comments = []
        Self.CommentInHand = None
        Self.CommentStartIndex = None
        Self.CommentEndIndex = None

        Self.RawFunctions = []

        Self.FlagsMap = {
            '-b': Self.Output_Breakdown,
            '-o': Self.Output_Intermediate_Language
        }

        Self.Parse_Arguments()

        if Self.EntryFile != None:
            Self.ExtractContents()

        if len(Self.SourceContent) > 1:
            Self.Find_Comments()

        if len(Self.SourceContent) > 1:
            Self.Find_Functions()

        Self.Execute_Flags()


    def Parse_Arguments(Self):
        Self.ArgumentCount = len(Arguments)
        if Self.ArgumentCount == 2: # No Flags
            Self.EntryFile = Arguments[1]
            Log(Context=Self.Parse_Arguments.__name__,
                ArgumentCount = Self.ArgumentCount,
                EntryFile = Self.EntryFile)
        elif Self.ArgumentCount > 2: # Flags Given
            Self.EntryFile = Arguments[1]
            Self.Flags = Arguments[2::]
            Self.Flags_Valid_Check()
            Log(Context=Self.Parse_Arguments.__name__,
                ArgumentCount = Self.ArgumentCount,
                Flags=Self.Flags,
                EntryFile = Self.EntryFile)
        else:
            print("Zero arguments given.")


    def Flags_Valid_Check(Self):
        try:
            for Flag in Self.Flags:
                Self.FlagsMap[Flag]()
        except KeyError:
            Log(Context=Self.Flags_Check.__name__,
                FlagError="You entered improper flags")


    def Execute_Flags(Self):
        if Self.Flags != None:
            for Flag in Self.Flags:
                Self.FlagsMap[Flag]()
            exit()


    def Find_Comments(Self):
        while Self.CommentFound:
            Self.CommentStartIndex = Self.Find_Symbol("#", "Find Start of Comment")
            if Self.CommentStartIndex != "Not Found":
                Self.CommentEndIndex = Self.Find_Symbol("#", "Find End of Comment", StartIndex=(Self.CommentStartIndex))
                if Self.CommentEndIndex != "Not Found":
                    Self.Comments.append(Self.SourceContent[Self.CommentStartIndex:Self.CommentEndIndex])
                    Self.SourceContent = Self.SourceContent.replace(Self.SourceContent[Self.CommentStartIndex-1:Self.CommentEndIndex+1], "")
            else:
                Self.CommentFound = False
            break
    

    def Find_Functions(Self):
        while Self.FunctionFound:
            Self.FunctionStartIndex = Self.Find_Keyword("func", "Find Start of Function")
            if Self.FunctionStartIndex != "Not Found":
                Self.FunctionEndIndex = Self.Find_Symbol("}", "Find End of Function", StartIndex=Self.FunctionStartIndex)
                if Self.FunctionEndIndex != "Not Found":
                    Self.RawFunctions.append(Self.SourceContent[Self.FunctionStartIndex:Self.FunctionEndIndex])
                    Self.SourceContent = Self.SourceContent.replace(Self.SourceContent[Self.FunctionStartIndex:Self.FunctionEndIndex], "")
            else:
                Self.FunctionFound = False
            break


    def Find_Symbol(Self, Symbol:str, Context:str, StartIndex:int=0):
        for Index, Character in enumerate(Self.SourceContent[StartIndex::]):
            if Character == Symbol:
                Log(Context=Context + " " + Self.Find_Symbol.__name__,
                    FoundIndex=Index)
                return Index + 1
        return "Not Found"


    def Find_Keyword(Self, Keyword:str, Context:str, StartIndex:int=0):
        Fillable = ""
        Counter = 0
        for Index, Character in enumerate(Self.SourceContent[StartIndex::]):
            if Counter >= 1: # Has the counter started? If so, continue to add the character in iteration, and counter += 1
                Fillable += Character
                Counter += 1
                
            if Character == Keyword[0]: # Is the character equal to f? If so, add character to fillable, and counter += 1
                Fillable += Character
                Counter += 1

            if Fillable == Keyword: # Is the fillable equal to the keyword 'func'? If so, Index += 2, log information, and return the Index
                Log(Context=Context + " " + Self.Find_Keyword.__name__,
                    FoundIndex=Index)
                return Index - len(Keyword) # Account for the length of keyword, we want this keyword in our parse

            if Counter >= 4: # Has counter reached 4, or somehow exceeded it? If so, reset.
                Fillable = ""
                Counter = 0

        return "Not Found"


    def ExtractContents(Self):
        Self.RawContent = open(Self.EntryFile).readlines()
        Self.SourceContent = "".join(Self.RawContent)
    

    def Output_Breakdown(Self):
        with open(f"{Self.EntryFile}.Breakdown.peach", 'w+') as BreakdownFile:
            BreakdownFile.write(str(Self.SourceContent))


    def Output_Intermediate_Language(Self):
        with open(f"{Self.EntryFile}.Source.peach", 'w+') as OutputFile:
            OutputFile.write(str(Self.SourceContent))
        with open(f"{Self.EntryFile}.Comments.peach", 'w+') as CommentsFile:
            CommentsFile.write(str(Self.Comments))
        with open(f"{Self.EntryFile}.RawFunctions.peach", 'w+') as OutputFile:
            OutputFile.write(str(Self.RawFunctions))
        # with open(f"{Self.EntryFile}.Finds.peach", 'w+') as OutputFile:
        #     OutputFile.write(str(Self.Finds))
        

    # Print out the functions in a readable way
    def Show_Functions(Self):
        print("\n".join(f"{Key}\n\t{Value}" for Key, Value in Self.Functions.items()))
