def Pretty_Wrap(Message:str):
    MessageLength:int = len(Message)
    Wrapper:str = "-"*MessageLength
    print(f"{Wrapper}\n{Message}\n{Wrapper}")