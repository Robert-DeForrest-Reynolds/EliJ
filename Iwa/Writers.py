from typing import List #type: ignore

C_PREFAB = "#include <stdio.h>\nint main() {\n}"


def Write_Prefab(Iwa):
    print("Writing Prefab...")
    if Iwa.ProjectInstance.Name != None:
        with open(f"{Iwa.DirectoryPath}/{Iwa.ProjectInstance.Name}.c", 'w+') as CFile:
            CFile.write(C_PREFAB)
    else:
        print("WARNING: No project name given. Defaulting to title: 'untitled.c'.\n")
        with open("untitled.c", 'w+') as CFile:
            CFile.write(C_PREFAB)


def Write_Instruction(Iwa, Instruction:str) -> None:
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
