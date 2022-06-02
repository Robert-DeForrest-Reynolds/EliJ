with open("Iwa_Utilities\C_Language.txt", 'r') as File:
    C_Lanuage = File.readlines()
    Include = C_Lanuage[0].strip()
    Define = C_Lanuage[1].strip()
    C_IO_Import = C_Lanuage[2].strip()