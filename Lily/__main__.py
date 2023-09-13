# You have to have the Peach parser directory in the Toran source directory

if __name__ == '__main__':
    from sys import path
    path.append("Peach")
    from Peach import Peach
    Peach()