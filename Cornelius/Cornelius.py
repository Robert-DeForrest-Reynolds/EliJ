from random import randrange
from re import search

"""
>-Information-<

Need to import from target node
Needs to format to a vector of strings for C++ compiler to successfully compile to bytecode without interal reformatting

>-Abstraction Explanation-<

Node; a individual piece of data (integers, strings, words, sentences)
Portal; the to access point to an individual piece of data (Files, Memory Addresses)
Directory; a group of portals to be taken in (Folder, Array of Memory Addresses)

>-Object Explanation-<

Node - The "port" holding access to the data.
Twin - A hardcoded twin of a port and it's data in order to simulate origins
DataContainer - A locally stored twin of the data used, that holds meta-data about that data within the DataContainer object 
DataFrame - A collection of DataContainers organized into a managable database
"""

class Node:
    def __init__(self, Medium):
        self.Medium = Medium
        self.Individual_Node_Array = []
        self.BuildIndividualArray()

    def BuildIndividualArray(self):
        if search(r'(\..*)', self.Medium) and not search(r'(w{3})', self.Medium):
            with open(self.Medium, 'r') as File:
                for _ in File:
                    self.Individual_Node_Array.append(_)
        elif search(r'(w{3})', self.Medium):
            print("Found URL")
            print(self.Medium)
        else:
            for _ in self.Medium:
                self.Individual_Node_Array.append(_)
        return self.Individual_Node_Array

class DataContainer:

    def __init__(self, Data):
        self.Data = Data
        self.ID = ""
        self.Type = ""
        self.GenerateID()
        self.FindDataType()

    def GenerateID(self):
        for _ in range(25):
            self.ID += str(randrange(0, 9))
        return self.ID
    
    def FindDataType(self):
        if type(self.Data) == str:
            self.Type = "String"
        elif type(self.Data) == int:
            self.Type = "Integer"    
        return self.Type

class DataFrame:
    def __init__(self, Node_Group):
        self.Node_Group = []
        self.ConstructFrame()

    def ConstructFrame():
        pass

if __name__ == '__main__':
    pass