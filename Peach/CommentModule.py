class CommentModule:
    def __init__(Self):
        Self.Comments = []
        Self.CommentFound = True
        Self.CommentInHand = None
        Self.CommentStartIndex = None
        Self.CommentEndIndex = None


        while Self.CommentFound:
            Self.Find_Comment()
            if Self.CommentFound:
                Self.Find_Comment_End()

    def Find_Comment():
        pass

    def Find_Comment_End():
        pass