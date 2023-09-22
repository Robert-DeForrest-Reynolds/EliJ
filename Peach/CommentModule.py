from Log import Log


def Find_Comments(Peach):
    while Peach.CommentFound:
        Peach.CommentStartIndex = Find_Comment_Start(Peach)
        if Peach.CommentStartIndex != "Not Found":
            Peach.CommentEndIndex = Find_Comment_End(Peach)
            if Peach.CommentEndIndex != "Not Found":
                Peach.Comments.append(Peach.SourceContent[Peach.CommentStartIndex:Peach.CommentEndIndex])
                Peach.SourceContent = Peach.SourceContent.replace(Peach.SourceContent[Peach.CommentStartIndex:Peach.CommentEndIndex], "")
        else:
            Peach.CommentFound = False


def Find_Comment_Start(Peach):
    for Index, Character in enumerate(Peach.SourceContent):
        if Character == "#":
            Log(Context=Find_Comment_Start.__name__,
                FoundIndex=Index)
            return Index
    return "Not Found"


def Find_Comment_End(Peach):
    SearchIndex = Peach.CommentStartIndex + 1
    Content = Peach.SourceContent[SearchIndex::]
    for Index, Character in enumerate(Content):
        if Character == "#":
            Log(Context=Find_Comment_End.__name__,
                FoundIndex=Index)
            return Index + Peach.CommentStartIndex + 2
    return "Not Found"