from os import path, removedirs, remove, getcwd
from sys import argv, dont_write_bytecode
from re import search
from glob import glob

from Iwa_Utilities.Utilities_Declarations import *
from Iwa_old import User_Arguments

Argument_Count = len(argv)
Arguments = argv

def CommandParsing():
    if Argument_Count == 1:
        print()