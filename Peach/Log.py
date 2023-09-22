def Log(Context, **Data):
    print(f"Execution at {Context}\n\t"+
            "\n\t".join([f"{(Name)}: {Datum}" for Name, Datum in Data.items()])+"\n"*3)