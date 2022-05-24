class ZeroArgumentsGiven(Exception):
    """Exception raised when zero arguments are given when calling Iwa"""
    def __init__(self, Arguments, Argument_Count):
        self.Arguments = Arguments
        self.Argument_Count = Argument_Count
        super().__init__("""
Argument Amount: {}
Arguments Presented: {}
        """.format(Arguments, Argument_Count))

class NotPappleFile(Exception):
    """Exception raised when file taken in for parsing is not a papple file"""
    def __init__(self, File):
        self.File = File

        super().__init__()