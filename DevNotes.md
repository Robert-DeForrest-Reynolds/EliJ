# EliJ/Iwa Developer Documentation

## Table of Contents
1. [Overview](#overview)
2. [Core Components](#core-components)
3. [Data Structures](#data-structures)
4. [Type System](#type-system)
5. [Memory Management](#memory-management)
6. [Built-in Functions](#built-in-functions)
7. [String Operations](#string-operations)
8. [Expression Handling](#expression-handling)
9. [File Operations](#file-operations)
10. [Error Handling](#error-handling)

## Overview
EliJ/Iwa is an interpreter implementation written in C, featuring a robust type system, built-in functions, and comprehensive string manipulation capabilities. The project emphasizes memory safety and modular design.

## Core Components

### Dictionary System
The dictionary implementation serves as the foundation for variable storage and symbol tables.

```c
Dictionary* Create_Dictionary(int Size);
void Insert(Dictionary* Dict, void* Key, Type KeyType, void* Value, Type ValueType);
Any* Lookup(Dictionary* Dict, void* Key);
```

- **Create_Dictionary**: Initializes a new dictionary with specified size
- **Insert**: Adds key-value pairs with type information
- **Lookup**: Retrieves values by key

### Interpreter Core
The interpreter processes instructions and manages execution flow.

```c
Any* Evaluate_Instruction(char* Instruction, int LineNumber);
Any* Execute_Statement(char* Instruction, char* KeywordBuffer, Any* InstructionKeyword, 
                      int InstructionLength, int CharacterIndex, int LineNumber);
```

## Data Structures

### Pair Structure
```c
typedef struct Pair {
    void* Key;
    Type KeyType;
    void* Value;
    Type ValueType;
    struct Pair* Next;
} Pair;
```

### Dictionary Structure
```c
typedef struct Dictionary {
    Pair** Table;
    int Filled;
    int Size;
    int InnerDepth;
} Dictionary;
```

### Any Structure
```c
typedef struct Any {
    void* Value;
    Type ValueType;
    FunctionType FuncType;
} Any;
```

## Type System
The type system supports multiple data types:
- STRING
- INT
- FLOAT
- DICTIONARY
- FUNCTION
- DECLARATION
- BOOL
- MULTILINE

## Memory Management

### Pointer Checking
```c
void String_Pointer_Check(char* Pointer, const char* PointerName);
void CharList_Pointer_Check(char** Pointer, const char* PointerName);
void StringList_Pointer_Check(StringList* Pointer, const char* PointerName);
```

### Memory Allocation Safety
All memory allocations are checked and verified:
```c
char* Buffer = malloc(Size * sizeof(char));
String_Pointer_Check(Buffer, "Buffer allocation failed");
```

## Built-in Functions

### Output Function
```c
void Output(Any* Pointer);
```
Handles output for different types:
- String output
- Integer output
- Float output
- Function reference output

### Input Function
```c
char* Input(char* Prompt);
```
Handles user input with optional prompt.

## String Operations

### Find Operations
```c
int Find(char* String, char* Query);
char* Find_Between(char* String, char* LeftQuery, char* RightQuery);
int Find_From_End(char* String, char* Query);
```

### String Manipulation
```c
char* Replace(char* String, char* Match, char* Replacement);
char* Remove(char* String, char* RemoveCharacter);
char* Reverse(char* String);
StringList* Split(char* String, char SplitCharacter);
```

## Expression Handling

### Arithmetic Operations
```c
long Solve_Addition(long OperandOne, long OperandTwo);
long Solve_Multiplication(long OperandOne, long OperandTwo);
char* Resolve_Expression(char* Expression, int ExpressionLength, bool Recursive);
```

Supports:
- Addition
- Subtraction
- Multiplication
- Division
- Nested parentheses
- Operator precedence

## File Operations

### File Reading
```c
char* Read_File(char* FileName);
StringList* Read_File_Lines(char* FileName, int LineBufferSize);
```

### Path Handling
```c
void Check_Windows_Style_Path(void);
void Setup_Working_Directory(void);
```

## Error Handling

### Error Message Creation
```c
char* Create_Error_Message(char* Statement, char* SpecificError, 
                          int ErrorIndex, int ErrorMarkerLength);
```

Example error output:
```
Error: Variable does not exist.
String Name = FirstName + LastName
              ^^^^^^^^^
```

## Usage Examples

### Variable Declaration
```c
String Name = "John"
Int Age = 25
Float Height = 1.75
```

### Function Calls
```c
Out("Hello World")
UserInput = In("Enter your name: ")
SubString = Find_Between(Text, "<", ">")
```

### Expressions
```c
Int Result = (5 + 3) * 2
String FullName = FirstName + " " + LastName
```

## Setup and Configuration

### Global Setup
```c
void Setup_Globals(void);
void Setup_Internal_Types(void);
void Setup_Valid_Operators(void);
```

### Initialization Process
1. Setup global variables
2. Initialize type system
3. Register built-in functions
4. Setup working directory
5. Parse command line arguments
6. Begin interpretation

## Best Practices

### Memory Management
- Always check allocated memory
- Free memory when no longer needed
- Use provided pointer checking functions

### Error Handling
- Check return values
- Provide meaningful error messages
- Handle edge cases appropriately

### Type Safety
- Always specify correct types
- Verify type compatibility
- Use type checking functions

## Contributing
When contributing to the project:
1. Follow existing code style
2. Add appropriate error checking
3. Document new functions
4. Verify memory management
5. Test edge cases
