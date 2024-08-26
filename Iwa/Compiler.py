from typing import List, Dict # type: ignore

from Generators import Generate_Printf_Function, Generate_Integer_Variable
from Project import Project

class Compiler:
    def __init__(Self):
        Self.ProjectInstance = Project()
        Self.DirectoryPath = None
        Self.FilePath = None
        Self.EXEPath = None
        Self.GlobalVariableMapping = {}
        Self.FunctionsMapping:Dict[str,str] = {}

        Self.Functions:List[str] = {
            "Out": Generate_Printf_Function,
        }
        Self.Variables:List[str] = {
            "Int": Generate_Integer_Variable,
        }

        Self.StringPositions:Dict[str,List[int]] = {}


        Self.HelpMessage = """\
Iwa is the compiler for the Pineapple programming language, by Robert Lawrence DeForrest Reynolds.

I thank you for using this, and I hope you enjoy the language, and continue to use it.
"""