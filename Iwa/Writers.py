from __future__ import annotations
from typing import TYPE_CHECKING # type: ignore

if TYPE_CHECKING:
    from Iwa import Compiler

from typing import List #type: ignore

C_PREFAB = "#include <stdio.h>\nint main() {\n}"


def Write_Prefab(Iwa:Compiler):
    print("Writing Prefab...")
    if Iwa.ProjectInstance.Name != None:
        print(f"Using project name: {Iwa.ProjectInstance.Name}\n")
        with open(f"{Iwa.DirectoryPath}/{Iwa.ProjectInstance.Name}.c", 'w+') as CFile:
            CFile.write(C_PREFAB)
    else:
        print("WARNING: No project name given. Defaulting to title: 'untitled.c'.\n")
        with open("untitled.c", 'w+') as CFile:
            CFile.write(C_PREFAB)


def Write_Instruction(Iwa:Compiler, Instruction:str) -> None:
    if Iwa.ProjectInstance.Name != None:
        with open(f"{Iwa.DirectoryPath}/{Iwa.ProjectInstance.Name}.c", 'r') as CFile:
            CurrentLines:List[str] = CFile.readlines()
        with open(f"{Iwa.DirectoryPath}/{Iwa.ProjectInstance.Name}.c", 'w') as CFile:
            EndLineIndex:int = len(CurrentLines)-1
            CurrentLines.insert(EndLineIndex, Instruction)
            CFile.write("".join(CurrentLines))
    else:
        with open("untitled.c", 'r') as CFile:
            CurrentLines:List[str] = CFile.readlines()
        with open("untitled.c", 'w') as CFile:
            EndLineIndex:int = len(CurrentLines)-1
            CurrentLines.insert(EndLineIndex, Instruction+"\n")
            CFile.write("".join(CurrentLines))
