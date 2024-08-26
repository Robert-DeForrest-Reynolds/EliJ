# Type ignore comments are because VSCode kinda sucks.
from typing import List # type: ignore
from typing import Dict # type:  ignore
from sys import argv as Arguments

# Import EliJ Utility Files
from os.path import dirname, realpath
from sys import path
path.append(dirname(dirname(realpath(__file__))))
from Helpers import Pretty_Wrap
from Actions import Zero_Argument, Single_Flag_Argument, Project_Action
from Compiler import Compiler

Iwa = Compiler()


ActionMapping:Dict[int,str] = {
    1:Zero_Argument,
    2:Single_Flag_Argument,
    3:Project_Action,
}


if __name__ == "__main__":
    Pretty_Wrap("~~~ Smile away, we're alive today. ~~~")
    ActionMapping[len(Arguments)](Iwa, Arguments)