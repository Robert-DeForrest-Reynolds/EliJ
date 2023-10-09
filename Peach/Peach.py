from sys import argv as Arguments, exit
from os import remove
from re import sub

from Log import Log

class Peach:
    def __init__(Self):
        Self.RawContent:str = None
        Self.SourceContent:str = None

        Self.CommentFound = True
        Self.FunctionFound = True
        Self.ImportFound = True
        Self.ObjectFound = True

        Self.Arguments = None
        Self.Flags = None
        Self.ArgumentCount = None

        Self.EntryFile = None

        Self.Comments = []
        Self.RawFunctions = []
        Self.Imports = []
        Self.Objects = []

        Self.FlagsMap = {
            '-b': Self.Output_Breakdown,
            '-o': Self.Output_Intermediate_Language
        }

        Self.Parse_Arguments()

        if Self.EntryFile != None:
            Self.ExtractContents()

        Self.Delimiters = [" ", ":", "<-"]


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


    def Find_Imports(Self):
        while Self.ImportFound:
            Self.ImportStartIndex = Self.Find_Keyword("from", "Find Start of Import")
            if Self.ImportStartIndex != "Not Found":
                Self.ImportEndIndex = Self.Find_Symbol(";", "Find End of Import", StartIndex=Self.ImportStartIndex)
                if Self.ImportEndIndex != "Not Found":
                    Self.Imports.append(Self.SourceContent[Self.ImportStartIndex:Self.ImportEndIndex])
                    Self.SourceContent = Self.SourceContent.replace(Self.SourceContent[Self.ImportStartIndex:Self.ImportEndIndex], "")
            else:
                Self.ImportFound = False


    def Find_Objects(Self):
        while Self.ObjectFound:
            Self.ObjectStartIndex = Self.Find_Keyword("obj", "Find Start of Object")
            if Self.ObjectStartIndex != "Not Found":
                Self.ObjectEndIndex = Self.Find_Newline("|", "Find End of Object", StartIndex=Self.ObjectStartIndex)
                if Self.ObjectEndIndex != "Not Found":
                    Self.Objects.append(Self.SourceContent[Self.ObjectStartIndex:Self.ObjectEndIndex])
                    Self.SourceContent = Self.SourceContent.replace(Self.SourceContent[Self.ObjectStartIndex:Self.ObjectEndIndex], "")
            else:
                Self.ObjectFound = False


    def Find_Newline(Self, Context:str, StartIndex:int=0):
        for Index, Character in enumerate(Self.SourceContent[StartIndex::]):
            if Character == "\n":
                Log(Context=Context + " " + Self.Find_Symbol.__name__,
                    FoundIndex=Index)
                return Index + 1 + StartIndex
        return "Not Found"


    def Find_Symbol(Self, Symbol:str, Context:str, StartIndex:int=0):
        for Index, Token in enumerate(Self.SourceContent[StartIndex::]):
            print(Token)
            if Token == Symbol:
                Log(Context=Context + " " + Self.Find_Symbol.__name__,
                    FoundIndex=Index)
                return Index + 1 + StartIndex
        return "Not Found"


    def Find_Keyword(Self, Keyword:str, Context:str, StartIndex:int=0):
        for Index, Token in enumerate(Self.SourceContent[StartIndex::]):
            if Token == Keyword:
                Log(Context=Context + " " + Self.Find_Keyword.__name__,
                FoundIndex=Index)

        return "Not Found"

    def ExtractContents(Self):
        with open(Self.EntryFile) as SourceFile:
            Self.SourceContent = SourceFile.readlines()
    

    def Output_Breakdown(Self):
        with open(f"{Self.EntryFile}.Breakdown.peach", 'w+') as BreakdownFile:
            BreakdownFile.write(str(Self.SourceContent))


    def Output_Intermediate_Language(Self):
        try:
            remove(f"{Self.EntryFile}.Source.peach")
            remove(f"{Self.EntryFile}.Comments.peach")
            remove(f"{Self.EntryFile}.RawFunctions.peach")
            remove(f"{Self.EntryFile}.Imports.peach")
        except:
            print("Failure to remove a previous Intermediate File for some reason.")

        with open(f"{Self.EntryFile}.Source.peach", 'w+') as OutputFile:
            OutputFile.write(str(Self.SourceContent).strip("\n"))
        with open(f"{Self.EntryFile}.Comments.peach", 'w+') as CommentsFile:
            CommentsFile.write(str(Self.Comments))
        with open(f"{Self.EntryFile}.RawFunctions.peach", 'w+') as OutputFile:
            OutputFile.write(str(Self.RawFunctions))
        with open(f"{Self.EntryFile}.Imports.peach", 'w+') as OutputFile:
            OutputFile.write(str(Self.Imports))
        with open(f"{Self.EntryFile}.Objects.peach", 'w+') as OutputFile:
            OutputFile.write(str(Self.Objects))

    # Print out the functions in a readable way
    def Show_Functions(Self):
        print("\n".join(f"{Key}\n\t{Value}" for Key, Value in Self.Functions.items()))
