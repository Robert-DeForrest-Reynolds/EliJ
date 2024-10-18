# You have to have the Peach parser directory in the Toran source directory

if __name__ == '__main__':
    from sys import path

    # Parse the Entry File, and obtain the contents in Intermediate Files
    path.append("Peach")
    from Peach import Peach
    Peach()