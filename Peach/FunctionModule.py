class FunctionModule:
    def __init__(Self):
        Self.Functions = {}
        Self.FunctionFound = True
        Self.FunctionInHand = None
        Self.FunctionStartIndex = None
        Self.FunctionEndIndex = None
        Self.FunctionParametersEndIndex = None
        Self.FunctionInHandDelcarativeName = None
        Self.FunctionBehavior = None

        while Self.FunctionFound:
            Self.Find_Function()
            if Self.FunctionFound == True:
                Self.Find_Function_End()
                Self.Get_Function_Delcarative_Name()
                Self.Find_Function_Parameters()
                Self.Get_Function_Behavior()
                Self.Save_Function()

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