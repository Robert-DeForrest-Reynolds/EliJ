class FindModule:
    def __init__(Self):
        Self.Finds = []
        Self.FindFound = True
        Self.FindInHand = None
        Self.FindStartIndex = None
        Self.FindEndIndex = None

        while Self.FindFound:
            Self.Find_Find()
            if Self.FindFound == True:
                Self.Find_Find_End()
                Self.Resolve_Find()

    # Find Finds
    def Find_Find(Self):
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
                Self.FindStartIndex = Index + 2
                Self.Output_Data(Function_Name=Self.Find_Find.__name__,
                                 FindStartIndex = Self.FindStartIndex)
                return True
        Self.FindFound = False
        return False
    

    def Find_Find_End(Self):
        for Index, Character in enumerate(Self.SourceContent[Self.FindStartIndex::]):
            if Character == ";":
                Self.FindEndIndex = Index + Self.FindStartIndex
                Self.Output_Data(Function_Name=Self.Find_Find_End.__name__,
                                 FindEndIndex = Self.FindEndIndex)
                break

    
    def Resolve_Find(Self):
        Self.FindInHandData = Self.SourceContent[Self.FindStartIndex:Self.FindEndIndex].split(" Find ")
        Self.Finds.append(Self.FindInHandData)
        Self.SourceContent = Self.SourceContent.replace("From " + Self.SourceContent[Self.FindStartIndex:Self.FindEndIndex]+";", "~")
        if Self.FindInHandData[1] == "*":
            FindContent = open(Self.FindInHandData[0]+".papple").readlines()
            FindContent = [Line.strip("\n").strip(" ") for Line in FindContent if Line != "\n"]
            FindContent = "".join(FindContent)
            FindContent = sub(" +", " ", FindContent)
            Self.SourceContent = Self.SourceContent.replace("~", FindContent)
        else:
            Self.Resolve_Namespace_Find()
        Self.Output_Data(Function_Name=Self.Resolve_Find.__name__,
                         FindData = Self.FindInHandData,
                         SourceContentAfterReplace = Self.SourceContent)


    def Resolve_Namespace_Find(Self):
        pass