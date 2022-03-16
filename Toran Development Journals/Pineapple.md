##### Standard Pineapple Language
*This is the list of things I think I should get done to be able to consider the language "existing", and ready to be worked on more*

**Environment**
 - Development Environment
 - Program Structure

**Utilities**
 - Comments
    * ~ Single line comment
    * ~~~ This is a multi-line comment ~~~
 - Comment References
    * | This is a comment reference  |
 - Log Handling
    * Log()
        > Prints data to the console dependant on passed parameters, and given context
 - Exception Handling
    * Try {} Catch {}

**Barebones Functionality**
 - Modulation
    * Import {<Module_Name>}
 - Variables
    * Variable_Name = 3.14
 - Operators
    * 2 + 2 * (8 * 8)
 - Strings
    * Variable_Name = "I'm a string"
 - Booleans
    * Boolean_Variable = True
 - If (Else) Statements
    * If <Conditional-Operation>{<Behavior>}
    * If <Conditional-Operation>{<Behavior>} Else{<Behavior>}
 - Switch Statements
    * Switch {}
 - Functions
    * FunctionName (<Passed-Parameters>)[<Passable-Parameters>]{<Behavior>}
 - Memory Management, Access Modifiers, Register Access

**Standard Library Functionality**
 - Input/Output
    * Print()
        > Prints data to console
    * PrintLine()
        > Prints data to console and adds a new-line
 - Triggers
    * Wait(){}
        > Waits for Return from a function dependant on match specification. If match returns true, the function will execute described behavior, if match returns false the function will pass, to be read again the next REPL-cycle. An If statement that works kind of like a Lambda function, but it's a lambda conditional, that specifically waits for function returns
 - Random
 - Ranges
 - Iterators
 - Command Line Arguments
 - Audio Programming

##### Advanced Pineapple Language Features
**These are features that will be supported later on**

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
 - Predefined Variables
 - Predefined Constants
 - Objects/Classifications
 - Dynamic Data Types
 - Custom Data Types
 - Procedures
 - Control Flow
 - Lambda Functions

##### Supported Source-to-Source Compilation
 - Web Assembly
 - DOM
 - HTML
 - CSS
 - JavaScript