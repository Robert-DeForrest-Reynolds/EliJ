def Generate_Printf_Function(GlobalVariableMapping, Contents:str) -> str:
    if '"' in Contents:
        return f'printf({Contents});'
    elif GlobalVariableMapping[Contents] == "Int":
        return f'printf("%d", {Contents});'


def Generate_Integer_Variable(GlobalVariableMapping, Name:str, Value:str) -> str:
    return f"int {Name} = {Value};"