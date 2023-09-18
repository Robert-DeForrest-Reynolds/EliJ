def Log(Function_Name, **Data):
    print(f"Successful execution at {Function_Name}\n\t"+
            "\n\t".join([f"{(Name)}: {Datum}" for Name, Datum in Data.items()])+"\n"*3)