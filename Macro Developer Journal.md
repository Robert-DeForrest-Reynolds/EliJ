This is the definition of "brain vomit".

In order to install Pineapple, all you need to do is clone the folder from it's GitHub repository: https://github.com/Robert-DeForrest-Reynolds/Pineapple. All of Pineapple is written in pure Python, and uses the standard library, therefore there is no building needed. Make sure you are using Python 3.9+.

If you wish, you can package the Iwa.py script, or Lily.py script with your project, but this is not suggested for a multitude of reasons. If you do, please credit the compiler somewhere reasonably.

If Python is the default application that opens .py files on your system, you can simply invoke Iwa from the command line by it's name
You can set an environment variable path to the file containing Iwa, to invoke the compiler from anywhere easily.

**Examples**

Plain Compilation
```
Iwa File.papple
```

Compilation with target
```
Iwa File.papple File
```

Compilation with settings
```
Iwa File.papple -IncludeRuntime
```