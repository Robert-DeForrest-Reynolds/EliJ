Peach breaks down Pineapple source code into data that is easier for a computer to interpret and understand.
Pineapple is fundamentally made up of 4 things: Declarations, Calls, Loops, Conditionals.

Steps:
- Find all comments
- Find all Finds & Resolve
- Find all Functions & Save to Dictionary
- Parse Through Statements & Save to Dependent Dictionaries:
- Declarations
- Calls
- Loops
- Conditionals

The entry file will be every project's starting point. If you've used C/C++, think of the main function, but instead it's a file.

Every file that is found using `Find` is it's own namespace scope.

Any other file within source code is referred to as a "Module".

Any and all functions within files, are as well their own namespace scope.

Functions cannot, and should not see global variables, functions only see passed parameters.

  

A Pineapple project is made up of:
- An Entry File
- Modules
- A Configuration File

  

When you use Hope to make a Pineapple project, these files are automatically generated.

  

Anything left after search is complete is then referred to as EntryFileStatments

  

Types are objects/classes. Type functions (otherwise known as methods) followed the exception to the above specified rule. Type functions belong to the respective structure's namespace.

  

Order of operations:

    - EntryFile Search
        - Comment Search
        - Find Search
            - Errors:
                - Syntax Errors:
                    - It seems <Statement> missing semi-colon at <Character-Position>;
        - Resolve Find(s)
            - Errors:
                - Cannot find Find
                - Find has error
        - Function Search
            - Comment Inner Search
            - Find Search
            - Resolve Find(s)
                - Errors:
                    - Cannot find Find
                    - Find has error
            - Type Search
                - Errors:
                    - Delcarative-Name matches Delcarative-Name outside of this function scope,
                        please specify if this value is global, or private.
                    - The value you gave is not the same type as the value you used to declared.
                        This is the type you used to declare the variable:
                        This is the type of the value you tried to assign to the variable:
        - Type Search
            - Errors:
                - The value you gave is not the same type as the value you used to declared.
                    This is the type you used to declare the variable:
                    This is the type of the value you tried to assign to the variable:
        - EntryFileStatments
        - Return Intermediate Language Files of Each Search

  

Each search procedure is kept to it's own module that is then used and called to when Peach is used.

Each modules __init__() should return it's respective information

  

Comments are kept and used for generating documentation, this is an optional feature

Functions are turned into a dictionary {DelcarativeName:[FunctionParameters,

                                                            FunctionBehavior]}