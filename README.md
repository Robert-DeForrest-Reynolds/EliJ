Pineapple is the name of the language. Iwa is the name of the interpreter I built for it.
Most of this currently is thought vomit. If you wish to provide any input, create a pull request, or reach out to me on Discord, user: `robertdeforrest`

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

### Currently Implemented
 - String Variable Declarations
 - Integer Variable Declarations
 - `Out(String Contents)`
 - `In()`
 - `In(String Prompt)` - Overloaded with string to display to console before user input
 - `Find_Between(String Content, String LeftQuery, String RightQuery)` - Find substring between two strings

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

Program crashes can be determined by the user through reassigning their constant value.
Constant values will only be change using the `Mutate()` function.

Dynamic typing is not supported, and will never be supported, nor any of it's lower-types like duck typing, sub-typing, or nominal typing comparison.
All typing is declared, casted, and compared explicitly. You can specify a kind of "translation unit" that allows for casting to other specifed types.

There will be built-in functions to assist with type casting primitive types to one another when compatible.

I see no reason why there *needs* to be:
 - semi-colons when there are already newline characters, and we can search forward in specified contexts
 - code block wrapping when code blocks are almost always organized with newlines, and tabs for readability anyways

All functions can return 3 types, the type statically stated, an Error that you can use to better present errors within your program, and a void pointer, or "None" in Pineapple.

Parameter evaluation is just easier, and better done with a wrapping of characters, in Pineapple, and most languages that is parentheses wrap "()".

Memory is automatically allocated, but is only deallocated automatically within a local scope.

Within the global scope, the user is responsible for deallocation using the built-in Free() function.

Anything that is not nothing, is something, and there's no initialization without identity. In other words, a variable requires a declarative name, and a type at minimum, or you have nothing. Every named, and typed variable in Pineapple is therefore fundamentally described as an object.

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