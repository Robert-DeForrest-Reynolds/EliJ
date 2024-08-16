from typing import List #type: ignore

C_PREFAB = "#include <stdio.h>\nint main() {\n}"


def Write_Prefab(ProjectInstance):
    print("Writing Prefab...")
    if ProjectInstance.Name != None:
        print(f"Using project name: {ProjectInstance.Name}\n")
        with open(f"{ProjectInstance.Name}.c", 'w+') as CFile:
            CFile.write(C_PREFAB)
    else:
        print("WARNING: No project name given. Defaulting to title: 'untitled.c'.\n")
        with open("untitled.c", 'w+') as CFile:
            CFile.write(C_PREFAB)


def Write_Instruction(ProjectInstance, Instruction) -> None:
    if ProjectInstance.Name != None:
        with open(f"{ProjectInstance.Name}.c", 'r') as CFile:
            CurrentLines:List[str] = CFile.readlines()
        with open(f"{ProjectInstance.Name}.c", 'w') as CFile:
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
