from sys import argv as Arguments, exit
from re import sub

from Log import Log

from CommentModule import Find_Comments
from FunctionModule import Find_Functions

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
        Self.RawFunctions = []
        Self.CommentInHand = None
        Self.CommentStartIndex = None
        Self.CommentEndIndex = None

        Self.FlagsMap = {
            '-b': Self.Output_Breakdown,
            '-o': Self.Output_Intermediate_Language
        }

        Self.Parse_Arguments()

        if Self.EntryFile != None:
            Self.ExtractContents()

        Find_Comments(Self)

        if len(Self.SourceContent) > 1:
            Find_Functions(Self)

        if Self.Flags != None:
            for Flag in Self.Flags:
                Self.FlagsMap[Flag]()

    def Parse_Arguments(Self):
        Self.ArgumentCount = len(Arguments)
        if Self.ArgumentCount == 2:
            Self.EntryFile = Arguments[1]
            Log(Context=Self.Parse_Arguments.__name__,
                ArguementCount = Self.ArgumentCount,
                EntryFile = Self.EntryFile)
        elif Self.ArgumentCount > 2:
            Self.EntryFile = Arguments[1]
            Self.Flags = Arguments[2::]
            Self.Flags_Check()
            Log(Context=Self.Parse_Arguments.__name__,
                ArguementCount = Self.ArgumentCount,
                Flags=Self.Flags,
                EntryFile = Self.EntryFile)
        else:
            print("Zero arguments given.")


    def Flags_Check(Self):
        try:
            for Flag in Self.Flags:
                Self.FlagsMap[Flag]()
        except KeyError:
            Log(Context=Self.Flags_Check.__name__,
                FlagError="You entered improper flags")
            exit()


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
