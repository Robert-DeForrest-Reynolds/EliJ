I need to write something here for test too, but I'm smart

Pineapple is the name of the language. Iwa is the name of the compiler I built for it.
Iwa utilizes C++, and Clang

All values in Pineapple are immutable by default. Mutability is impossible in Pineapple.

A Pineapple program is broken down in to parts, they are implemented into each program by default, and can be toggled off:
- Stack-Memory for incredible efficiency
- Garbage Collection on References
- Runtime Instruction Execution, optionally


Pineapple is fundamentally made up of 4 things: Declarations, Calls, Loops, Conditionals.

Pineapple gets translated into an intermediate language using Python that is easier to work with when generating C code. This can then be easily made compatible with any compiler. As well, Pineapple will be easy to update, as

### Guiding Principles & Opinions:
- Research & Development is the key skill a software developer requires. Good luck.
- Clean, and organized code is better than short, and abbreviated code. Autocomplete exists for a reason.
- Modularity over inheritance. It isn't too hard to make modularity messy, but it's very easy to make inheritance hell. Complexity is achieved through individual identity in multitudes.
- Programming languages allow us to talk to computers, but more importantly, it allows them to talk to us, and tell us what they are doing. When someone else comes along and reads your code, it best damn well tell them what the computer is doing. Don't hide things, make jokes at the expense of humor, not the program, and never, ever, for the love of all that is mighty, forget your documentation.
- Technology is a conceptualization to help us. Don't deny it's implementation to make your life easier. Technology will inevitably push us farther and farther as the human capacity for experience craves more than what it had yesterday. We can still keep our humanity while implementing technology for it's great benefits, with positive intents. TLDR; VR good, TikTok bad.
- Remember this if nothing else. A calculator is an artificial intelligence. Intelligence has levels. If you implement something intelligent, as long as the input is constrained, and if there is a loop, it is maintained, nothing *should* go wrong. We need not be scared of incredibly intelligent things with constrained inputs, and maintained loops. We need be scared of even the dumbest of intelligent things that do not have constrained inputs, nor maintained loops. They are completely unpredictable, completely unteachable, and absolutely uncontrollable.
- A compiled, released program should never require another program to run. It should be absolute, and complete. This is not to say that two programs interacting with one another is bad, but more specifically, this tends leads to one-sided interactions between two programs which has proved to be very bad.
- The idea "everything in programming is an object" is a good thing. The backend of a language being structured as so, allows the programmer to develop a program that is naturally modular. An integer is a object, just as much as a cat is.

# Double Notation
Pineapple has something I called "double notation". The two notations that you can use are "conventional", "didactic".
Iwa will only allow the first convention detected, at which the full convention needs to be used. If conventional notation is the first detected, conventional notation will be required throughout the whole project, likewise didactic notation.

All documentation for Pineapple is done using conventional notation. The documentation for the particulars of didactic notation is provided here, as well as documentation using didactic notation: [(WIP)](WIP)

### Comments:

```
// Single-Line Comment

/*
Multi-Line Comment
*/

(Use for "codified notation" within code)
# Single-Line Comment

###
Multi-Line Comment
###
```

### Variable Declaration:

Type Name = Value

```
decimal Pi = 3.14
```

### Function Declaration

Name (Parameters) {Functionality}

```
Addition ( Integer X, Integer Y )
{
	return X + Y
}
```

### Conditionals

Value Equative Operator Value

4 or 8 Space Indentation Statement

Value Equative Operator Value

4 or 8 Space Indentation Statement


```
if Wheat in Bread_Ingredients
		Return Baked = True
```

```
if Food == Expired{
		Return "Throw in trash"
}else{
		Return "Edible"
}
```

```
if Fruit is "Apple"
		Return "Yummy"
or Fruit is "Orange"
		Return "Meh"
or Fruit is "Cherry"
		Return "Meh"
else Fruit is "Grapefruit"
		Return "Gross"
```

### Code Examples

```
integer UserInput1;
integer UserInput2;

Out(User_Input_1, User_Input_2);
```

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

# Pineapple Eco-System Notes

---

### **Environment**

- Preprocessing
    
- Scope
    
- Reference Frames
    
    Reference Frame are in essence controlled namespacing in Pineapple.
    
    Data can have different types, and values.
    
    Entities can have different classifications, and behavior.
    
    Then there are keywords, like Access Modifiers, Type Declarations, Operators, Delineators, Comments, or Separators, which are all separate and are not referred to in the Pineapple ecosystem as either data or entities, but there own completely separate kinds of functionality.
    

---

### **Utilities**

- Comments
- Comment References
- Log Handling
- Exception Handling

---

### **Declaration**

- Variables
    
    Variables will be immutable by default, unless the keyword `Mutable` is used when declaring a variable. Variables can not, and must not be made mutable afterward it's declaration, no exceptions.
    
    You can create a variable without giving it a value. In Pineapple we call this declaring a variable or declaration. When you give it a value you, we say that variable has been initialized.
    
    You can pass declared variables into functions for use.
    
    The compiler will see if you have used the variable, if you used the variable declaration as a passable argument, it will sense if you have initialized that function anywhere, if you haven’t, and it’s only been declared, your program won’t compile.
    

---

### **Functionality**

- Operators
    
- Booleans
    
- Conditionals
    
    Conditionals in any supported text editor or IDE will use divider line to make separations between if else conditionals for easier reading.
    
- Functions
    
    You will be able to give a function multiple names, this has multiple quality of life benefits, however, is not required in anywhere to be used.
    
    - Syntax Drafts
        
        ```python
        # Complex function with absolute wording
        <Access Modifier> <Return Type Declaration> (Function Name; Reference Names)
        [Passable Parameters]
        {
        Funtional Code
        }
        
        Private Integer (Do_Something; Reference_Name)
        [Passable_Parameter1, Passable_Parameter2]
        {
        	Variable_1 = Passable_Parameter_1
        	Variable_2 = Passable_Parameter_2
        }
        ```
        
        ```python
        #Complex function without absolute wording
        
        <Access Modifier> <Return Type Declaration> (Function Name; Reference Names)
        [Passable Parameters]
        {
        Funtional Code
        }
        
        Priv Int (Do_Something, Reference_Name)
        [Passable_Parameter1, Passable_Parameter2]
        {
        	Variable_1 = Passable_Parameter_1
        	Variable_2 = Passable_Parameter_2
        }
        ```
        
- Input/Output
    
- Memory Management, Access Modifiers, Register Access, Ownership, Borrowing, Trading, Loaning, and Priveleges
    
- Command Line Arguments
    
- File Management
    

---

### **Advanced Functionality that will Implemented after Bootstrapping Iwa**

- Events
- Triggers
- Random
- Ranges
- Iterators
- Audio Programming
- Lambda Functions
- Module System

---

## Advanced Pineapple Language Features

- _**These are features that will be supported later on**_

---

- Regular Expressions
- File Management
- Embedded Runtime within the Executable, Garbage Collection
- Asynchronous Behavior
- Databases
- Embedded Documentation
- Agents
- Parameter Overloading
- Instrinsic Functions
- Accessing System Calls, and other low-level functions
- Stacks
- Time
- HTTP
- Tk
- XML
- JSON
- CSV
- Color
- Data Visualization
- Predefined Variables (move to advanced feature list, for later implementation)
- Predefined Constants (move to advanced feature list, for later implementation)
- Objects (move to advanced feature list, for later implementation)
    I’m going to use functions to implement classes & objects. Classes are going to be more like ‘classifications’. Instead of representing objects, they will represent the object type. Meaning that there will be an implementation of custom object typing.
- Classifications (move to advanced feature list, for later implementation)
- Procedures (move to advanced feature list, for later implementation)
- Control Flow (move to advanced feature list, for later implementation)
- Dynamic Data Types (move to advanced feature list, for later implementation)
    Type casting, the ability not to cast a type, and run through the compiler safely
- Custom Data Types (move to advanced feature list, for later implementation)

---



# Program
