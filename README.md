Pineapple is the name of the language. Iwa is the name of the interpreter I built for it.

Let's keep this simple, what're the hopes and goals?
 - Fast to write, fast to develop
 - Easy to interpret, therefore, theoretically easy to embed
 - Manual memory management that feels nicer
 - A high-level language with low-level capabilities
 - Strong standard library
 - Efficient enough

I think there is a middle ground between concrete compilation to machine code, and broad-scoped interpretation of code that allows for a simplistic experience in language development, and computer science research.

The Pineapple is fundamentally made up of 2 things: Declarations, and operations.
Declarations structure and add data to the accessible scopes.
Operations like conditionals make decision on how to access, and what do with that data, as well as, functions which exist to reuse code, and organize complex functionality.
If it's not a declaration, it's an operation. If it's not an operation, we've reached the end of the program.
Files are read top-down.
The only control flow hidden that begs an understanding of the backend is scope, but it is simple. Anything declared outside of the local scope of a variable, function, or an object is global. You cannot expose data within a local scope to the global scope, but the global scope is always exposed to any local scope, and local scope cannot overwrite, or shadow in name.
### **Standard Library Implementations**
- Strings
- Math Functions & Constants
- Lists
- Dictionaries
- Linked Lists
- Output
- Input
- File Operations
- Date & Time
- Networking
- Error Handling
- Multi-Threading
- Asynchronous Control Flow
- Database Interaction
- Randomness
- Graphical Interfacing
- Ranges
### Advanced Functionality
Priority on these functionalities is much lower then the standard library
- Events
- Triggers
- Random
- Ranges
- Audio Programming
- Regular Expressions
- Embedded Runtime within the Executable, Garbage Collection
- Databases
- Embedded Documentation
- Accessing System Calls, and other low-level functions
- Stacks
- XML
- JSON
- CSV
- Color
- Data Visualization
### **External Tools & Subjects**
- Learning & Tutorials
- Workflow
- Integrated Code Editor
- Integrated Development Environment
- Reference Manual
- Documentation
- Debugging
- Build System
- Package Manager
- Package Development
- Plug-ins
- Version Control System
- Unit Testing
- Interpretation
- Virtual Environment
- Graphics Rendering Engine
- Extensibility of a Compiled Program

---

Developer = Pineapple Language Developer
User = Pineapple Language User
Consumer = User of Pineapple Language Application

Each line is considered a statement.
A statement holds declarations, expressions, and calls.
Certain statements like conditionals will index forward to combine multi-line statements.

When searching through a statement, we'll find the first Space character, and will identify the keyword found.
All keywords, are hashed into a hash table (the Global dictionary)
That keyword will be used to key into the Global dictionary. If a value is found, the internal instruction will be used.
Variables names, function names, and object names are hashed into the Global dictionary

If the hash does not exist in the map, the interpreter will crash, and report it.

Dynamic typing is not supported, and will never be supported.

I see no reason why there *needs* to be:
 - semi-colons when there are already newline characters, and we can search forward in specified contexts
 - code block wrapping when code blocks are almost always organized with newlines, and tabs for readability anyways

All functions can return 3 types, the type statically state, an Error, and a NULL value, or "None" in Pineapple

Parameter evaluation is just easier, and better done with a wrapping of characters, in Pineapple, and most languages that is parentheses wrap "()".

Memory is automatically allocated, but is only deallocated automatically within a local scope.

Within the global scope, the user is responsible for deallocation using the built-in Free() function.

Everything is something. Pineapple strays from delving too far into the canonical OOP approach. An Object in Pineapple is treated as a structure of data.

```
\ Comments in Pineapple \
\ 
Multi-line
comment in
Pineapple
\ 

\ Variable Declarations \
Int Number = 5
Str String = "Hello"
Float Wallet = 0.30
Bool Alive = True
Dict PhoneNumbers = {}
List Names = []
Number = 0

\ Conditional Statements \
If Number < 10
    Out("Number is less than 10")
Or Number == 10
    Out("Number is equal to 10")
Else
    Out("Number is more than 10")

\ Loop Statement \
While Number < 15
    Number += 1

List Fruits = [
    "Apple",
    "Orange",
    "Strawberry",
]

For Fruit in Fruits
    Out(Fruit)

\ Function Declaration: Read_File \
Fnc Read_File(String FilePath) -> Rtn
    File SomeFile = Open(FilePath)
    Str Contents = SomeFile.Read_Lines()
    Out(Contents)

Fnc Sum(Int X, Int Y) -> Int
    Rtn X + Y

Sum(Int 5, Int 5)

Obj Person:
    Str Name
    Int Age
    \ Example of constructor implementation \
    \ There are no internal constructors or methods for objects \
    Fnc New(_Name, _Age)
        Str Name = _Name
        Int Age = _Age

\ Object Instantiation \
Person Sally;

\ Object Property Call \
Sally.Name = "Sally"
Sally.Age = 25

Free(Sally) \ Automatically frees all properties within local scope of any object \
```
