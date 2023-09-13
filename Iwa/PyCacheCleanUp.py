from glob import glob
from os import remove, removedirs, getcwd

def PyCache_Clean_Up():
    try:
        print("\nCommencing PyCache Cleanup from Hope")
        Project_Path = getcwd()
        pyCacheFiles = glob(Project_Path + "\**\*.pyc", recursive = True)
        pyCacheFolders = glob(Project_Path + "\**\__pycache__", recursive = True)
        for File in pyCacheFiles:
            try:
                remove(File)
            except:
                print("Error removing .pyc files.")
        for Directory in pyCacheFolders:
            try:
                removedirs(Directory)
            except:
                print("Error removing _pycache__ directories.")
    except:
        "Some kind of error in PyCacheCleanup() function"