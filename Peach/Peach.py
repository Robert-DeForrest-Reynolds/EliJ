from sys import argv as Arguments
from re import sub

"""
Peach breaks down Pineapple source code into data that is easier for a computer to interpret and understand.

Pineapple is fundamentally made up of 4 things: Declarations, Calls, Loops, Conditionals.

Steps:
    - Find All Imports & Resolve
    - Find All Functions & Save to Dictionary
    - Parse Through Statements & Save to Dependant Dictionaries:
        - Declarations
        - Calls
        - Loops
        - Conditionals

"""

class Peach:
    def __init__(Self):
        Self.SourceContent = None
        Self.Imports = []
        Self.Functions = {}

        Self.Arguments = None
        Self.ArgumentCount = None
        Self.EntryFile = None

        Self.ImportFound = True
        Self.ImportStartIndex = None
        Self.ImportEndIndex = None

        Self.FunctionFound = True
        Self.FunctionInHand = None
        Self.FunctionStartIndex = None
        Self.FunctionEndIndex = None
        Self.FunctionParametersEndIndex = None
        Self.FunctionInHandDelcarativeName = None
        Self.FunctionBehavior = None
        
        
        Self.Parse_Arguments()
        Self.Extract_Contents()
        Self.Clear_Whitespace()


        Self.SourceContent = "".join(Self.SourceContent)
        Self.SourceContent = sub(" +", " ", Self.SourceContent)

        """

        The entry file will be every project's starting point. If you've used C/C++, think of the main function, but instead it's a file.
        Every file that is imported is it's own namespace scope.
        Any other file within source code is referred to as a "Module".
        Any and all functions within files, are as well their own namespace scope.
        Functions cannot, and should not see global variables, functions only see passed parameters.

        A Pineapple project is made up of:
            - An Entry File
            - Modules
            - A Configuration File

        When you use Hope to make a Pineapple project, these files are automatically generated.

        Anything left after search is complete is then referred to as EntryFileStatments

        Types's are objects/classes. Type functions (otherwise known as methods) followed the exception to the above specified rule. Type functions belong to the
        respective struture's namespace.

        Order of operations:
            - EntryFile Search
                - Comment Search
                - Import Search
                    - Errors:
                        - Syntax Errors:
                            - 
                - Resolve Import(s)
                    - Errors:
                        - Cannot find import
                        - Import has error
                - Function Search
                    - Comment Inner Search
                    - Find Search
                    - Resolve Find(s)
                    - Type Search
                - Type Search
                - EntryFileStatments
                - Return Intermediate Language Files of Each Search

        Each search procedure is kept to it's own module that is then used and called to when Peach is used.
        Each modules __init__() should return it's respective information

        Comments are kept and used for generating documentation, this is an optional feature
        Functions are turned into a dictionary {DelcarativeName:[FunctionParameters,
                                                                 FunctionBehavior]}
        """

        # while Self.CommentFound:
        #     Self.Find_Comment()
        #     if Self.CommentFound:
        #         Self.Find_Comment_End()

        while Self.FunctionFound:
            Self.Find_Function()
            if Self.FunctionFound == True:
                Self.Find_Function_End()
                Self.Get_Function_Delcarative_Name()
                Self.Find_Function_Parameters()
                Self.Get_Function_Behavior()
                Self.Save_Function()

        while Self.ImportFound:
            Self.Find_Import()
            if Self.ImportFound == True:
                Self.Find_Import_End()
                Self.Resolve_Import()


        Self.Output_Intermediate_Language()

    
    def Output_Intermediate_Language(Self):
        with open(f"{Self.EntryFile}.Source.peach", 'w+') as OutputFile:
            OutputFile.write(str(Self.SourceContent))
        with open(f"{Self.EntryFile}.Imports.peach", 'w+') as OutputFile:
            OutputFile.write(str(Self.Imports))
        with open(f"{Self.EntryFile}.Functions.peach", 'w+') as OutputFile:
            OutputFile.write(str(Self.Functions))

    def Output_Data(Self, Function_Name, **Data):
        print(f"Successful execution at {Function_Name}\n\t"+
              "\n\t".join([f"{(Name)}: {Datum}" for Name, Datum in Data.items()])+"\n"*3)

    # Find Imports
    def Find_Import(Self):
        Fillable = ""
        Counter = 0
        for Index, Character in enumerate(Self.SourceContent):
            if Counter >= 1:
                Fillable += Character
            if Counter >= 4:
                Fillable = ""
                Counter = 0
            if Character == "F":
                Fillable += Character
                Counter += 1
            if Fillable == "From":
                Self.ImportStartIndex = Index + 2
                Self.Output_Data(Function_Name=Self.Find_Import.__name__,
                                 ImportStartIndex = Self.ImportStartIndex)
                return True
        Self.ImportFound = False
        return False
    

    def Find_Import_End(Self):
        for Index, Character in enumerate(Self.SourceContent[Self.ImportStartIndex::]):
            if Character == ";":
                Self.ImportEndIndex = Index + Self.ImportStartIndex
                Self.Output_Data(Function_Name=Self.Find_Import_End.__name__,
                                 ImportEndIndex = Self.ImportEndIndex)
                break

    
    def Resolve_Import(Self):
        Self.ImportInHandData = Self.SourceContent[Self.ImportStartIndex:Self.ImportEndIndex].split(" import ")
        Self.Imports.append(Self.ImportInHandData)
        Self.SourceContent = Self.SourceContent.replace("From " + Self.SourceContent[Self.ImportStartIndex:Self.ImportEndIndex]+";", "~")
        if Self.ImportInHandData[1] == "*":
            ImportContent = open(Self.ImportInHandData[0]+".papple").readlines()
            ImportContent = [Line.strip("\n").strip(" ") for Line in ImportContent if Line != "\n"]
            ImportContent = "".join(ImportContent)
            ImportContent = sub(" +", " ", ImportContent)
            Self.SourceContent = Self.SourceContent.replace("~", ImportContent)
        else:
            Self.Resolve_Namespace_Import()
        Self.Output_Data(Function_Name=Self.Resolve_Import.__name__,
                         ImportData = Self.ImportInHandData,
                         SourceContentAfterReplace = Self.SourceContent)


    def Resolve_Namespace_Import(Self):
        pass


    #Gets argument count given, and determines the given Entry File
    def Parse_Arguments(Self):
        Self.ArgumentCount = len(Arguments)
        if Self.ArgumentCount == 2:
            Self.EntryFile = Arguments[1]
            Self.Output_Data(Function_Name=Self.Resolve_Import.__name__,
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


    #Finds the first function in the source content
    def Find_Function(Self):
        for Index, Character in enumerate(Self.SourceContent):
            if Character == ">":
                Self.FunctionStartIndex = Index + 1
                Self.Output_Data(Function_Name=Self.Find_Function.__name__,
                                 functionStartIndex = Self.FunctionStartIndex)
                Self.FunctionFound = True
                return True
        Self.FunctionFound = False
        return False


    def Find_Function_End(Self):
        for Index, Character in enumerate(Self.SourceContent[Self.FunctionStartIndex::]):
            if Character == "}":
                Self.FunctionEndIndex = Index + Self.FunctionStartIndex
                Self.FunctionInHand = Self.SourceContent[Self.FunctionStartIndex:Self.FunctionEndIndex]
                print("Successfully read function using Find_Function_End()\n"+
                      "Output:\n"+
                      f"\tFunction In Hand: {Self.FunctionInHand}"+'\n'*2+
                      f"\tFunction End Index: {Self.FunctionEndIndex}"+'\n'*3)
                break


    #Finds the start of the parameters
    def Find_Function_Parameters(Self):
        Counter = 0
        for Index, Character in enumerate(Self.FunctionInHand):
            if Character == "(":
                if Counter >= 1:
                    print(f"Found second '(' at {Index}"+'\n'*2)
                    break
                Counter += 1
                Self.FunctionParametersStartIndex = Index + 1
                print("Successfully found function using Find_Function_Parameters()\n"+
                    "Output:\n"+
                    f"\tFunction Parameter Start Index: {Self.FunctionParametersStartIndex}"+'\n'*3)
                break
        for Index, Character in enumerate(Self.FunctionInHand[Self.FunctionParametersStartIndex::]):
            if Character == ")":
                Self.FunctionParametersEndIndex = Index + Self.FunctionParametersStartIndex
                Self.FunctionInHandParameters = Self.FunctionInHand[Self.FunctionParametersStartIndex:Self.FunctionParametersEndIndex]
                Self.FunctionInHandParameters = Self.FunctionInHandParameters.split(", ")
                Self.FunctionParametersEndIndex = Index + Self.FunctionParametersStartIndex
                print("Successfully found end of function using Find_Function_Parameters()\n"+
                      "Output:\n"+
                      f"\tParameters found: {Self.FunctionInHandParameters}\n"+
                      f"\tFunction Parameter End Index: {Self.FunctionParametersEndIndex}"+'\n'*3)
                break


    # Get function in-hand name
    def Get_Function_Delcarative_Name(Self):
        Name = ""
        for Character in Self.FunctionInHand:
            if Character == "(":
                Self.FunctionInHandDelcarativeName = Name
                print("Successfully found function name Get_Function_Declarative_Name()\n"+
                      "Output:\n"+
                      f"\tFunction Delcarative Name: {Self.FunctionInHandDelcarativeName}"+'\n'*3)
                break
            else:
                Name += Character


    # Index slice to find the functions behavior
    def Get_Function_Behavior(Self):
        BehaviorEndIndex = Self.FunctionEndIndex-3
        Self.FunctionBehavior = Self.FunctionInHand[Self.FunctionParametersEndIndex+2:BehaviorEndIndex]
        print("Successfully found function name Get_Function_Behavior()\n"+
              "Output:\n"+
              f"\tFunction Behavior: {Self.FunctionBehavior}"+'\n'*3)


    # Trasfer functions from SourceContent to Functions
    def Save_Function(Self):
        FunctionData = [Self.FunctionInHandParameters,
                        Self.FunctionBehavior]
        Self.Functions.update({Self.FunctionInHandDelcarativeName:FunctionData})
        Self.SourceContent = Self.SourceContent.replace(">"+Self.FunctionInHand+"}", "")
        print("Successfully saved function using Save_Function()\n"+
            "Output:\n"+
            f"\tSource Content after replace: {Self.SourceContent}\n"
            f"\tFunctions: {Self.Functions}"+'\n'*3)
        

    # Print out the functions in a readable way
    def Show_Functions(Self):
        print("\n".join(f"{Key}\n\t{Value}" for Key, Value in Self.Functions.items()))