
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

#include "Structures.h"
#include "Globals.h"
#include "Interpreter.h"
#include "PointerChecks.h"

#include "Contains.h"
#include "Count.h"
#include "Dictionary.h"
#include "Expressions.h"
#include "Find.h"
#include "FindBetween.h"
#include "FindFromEnd.h"
#include "Hash.h"
#include "Input.h"
#include "LeftTrimIndex.h"
#include "Output.h"
#include "ReadFile.h"
#include "ReadFileLines.h"
#include "Remove.h"
#include "Replace.h"
#include "Reverse.h"
#include "Split.h"
#include "Trim.h"

void Setup_Internal_Types(void);
void Setup_Valid_Operators(void);
void Setup_Globals(void);
void Check_Windows_Style_Path(void);
void Verify_Valid_Papple_File(char* PotentialFileName, int ArgumentLength, int WorkingDirectoryLength);
void Parse_User_Arguments(int ArgumentsCount, char* Arguments[]);
void Setup_Working_Directory(void);


void Setup_Internal_Types(){
    Type* StringType = (Type*) malloc(sizeof(Type));
    Type* IntType = (Type*) malloc(sizeof(Type));
    Type* FloatType = (Type*) malloc(sizeof(Type));
    Type* OutputType = (Type*) malloc(sizeof(Type));
    *StringType = STRING;
    *IntType = INT;
    *FloatType = FLOAT;
    *OutputType = OUTPUT;

    InternalTypeMap = Create_Dictionary(50);
    
    Insert(InternalTypeMap, strdup("String"), STRING, StringType, TYPE);
    Insert(InternalTypeMap, strdup("Int"), STRING, IntType, TYPE);
    Insert(InternalTypeMap, strdup("Float"), STRING, FloatType, TYPE);
    
    #if DEBUG
    puts("\nVerifying Internal Types");
    for (int Index = 0; Index < InternalTypeMap->Size; Index++){
        if (InternalTypeMap->Table[Index] != NULL){
            Pair* KeyValue = InternalTypeMap->Table[Index];
            Type ValueType = *(Type*) KeyValue->Value;
            printf("Type Syntax: %s\nRepresentation: %s\n", (char*) KeyValue->Key, TypesAsStrings[ValueType]);
        }
    }
    #endif
}


void Setup_Valid_Operators(){
    ValidOperators = Create_Dictionary(50);
    
    Insert(InternalTypeMap, strdup("+"), STRING, (void*) true, BOOL);
    Insert(InternalTypeMap, strdup("-"), STRING, (void*) true, BOOL);
    Insert(InternalTypeMap, strdup("*"), STRING, (void*) true, BOOL);
    Insert(InternalTypeMap, strdup("/"), STRING, (void*) true, BOOL);
    
    #if DEBUG
    puts("\nVerifying Internal Types");
    for (int Index = 0; Index < InternalTypeMap->Size; Index++){
        if (InternalTypeMap->Table[Index] != NULL){
            Pair* KeyValue = InternalTypeMap->Table[Index];
            Type ValueType = *(Type*) KeyValue->Value;
            printf("Type Syntax: %s\nRepresentation: %s\n", (char*) KeyValue->Key, TypesAsStrings[ValueType]);
        }
    }
    #endif
}


void Setup_Globals(){
    Globals = Create_Dictionary(50);
    VariableDeclaration* VarDecl = malloc(sizeof(VariableDeclaration));
    VariableDeclaration_Pointer_Check(VarDecl, "Variable Declaration Pointer Allocation Fail");
    VarDecl->Function = Variable_Declaration;
    VarDecl->FunctionName = "Variable_Declaration";

    OutputFunction* OutputFunc = malloc(sizeof(OutputFunction));
    Output_Pointer_Check(OutputFunc, "Output Pointer Allocation Fail");
    OutputFunc->Function = Output;
    OutputFunc->FunctionName = "Output";

    InputFunction* InputFunc = malloc(sizeof(InputFunction));
    Input_Pointer_Check(InputFunc, "Input Pointer Allocation Fail");
    InputFunc->Function = Input;
    InputFunc->FunctionName = "Input";

    FindBetweenFunction* FindBetweenFunc = malloc(sizeof(FindBetweenFunction));
    FindBetween_Pointer_Check(FindBetweenFunc, "Find_Between Pointer Allocation Fail");
    FindBetweenFunc->Function = Find_Between;
    FindBetweenFunc->FunctionName = "Find_Between";
    FindBetweenFunc->FuncType = FIND_BETWEEN;

    // Variable Types
    Insert(Globals, strdup("String"), STRING, VarDecl, DECLARATION);
    Insert(Globals, strdup("Int"), STRING, VarDecl, DECLARATION);
    Insert(Globals, strdup("Float"), STRING, VarDecl, DECLARATION);
    Insert(Globals, strdup("List"), STRING, VarDecl, DECLARATION);

    // Built-In Functions
    Insert(Globals, strdup("Out"), STRING, OutputFunc, OUTPUT);
    Insert(Globals, strdup("In"), STRING, InputFunc, INPUT);
    Insert(Globals, strdup("Find_Between"), STRING, FindBetweenFunc, STRING_RTN);
    
    #if DEBUG
    puts("\nVerifying Built-Ins within Globals");
    for (int Index = 0; Index < Globals->Size; Index++){
        if (Globals->Table[Index] != NULL){
            Pair* KeyValue = Globals->Table[Index];
            switch (KeyValue->ValueType){
                case DECLARATION:{
                    VariableDeclaration* VarDeclCheck = (VariableDeclaration*) KeyValue->Value;
                    VariableDeclaration_Pointer_Check(VarDecl, "Variable Declaration Pointer Allocation Fail");
                    printf("Key: %s\nValue: %s\n", (char*) KeyValue->Key, VarDeclCheck->FunctionName);
                    break;
                }
                case OUTPUT:{
                    OutputFunction* OutputFuncCheck = (OutputFunction*) KeyValue->Value;
                    Output_Pointer_Check(OutputFuncCheck, "Output Function Instruction Allocation Fail");
                    printf("Key: %s\nValue: %s\n", (char*) KeyValue->Key, OutputFuncCheck->FunctionName);
                    break;
                }
                case INPUT:{
                    InputFunction* InputFuncCheck = (InputFunction*) KeyValue->Value;
                    Input_Pointer_Check(InputFuncCheck, "Input Function Instruction Allocation Fail");
                    printf("Key: %s\nValue: %s\n", (char*) KeyValue->Key, InputFuncCheck->FunctionName);
                    break;
                }
                default:
                    break;
            }
        }
    }
    #endif
}

void Check_Windows_Style_Path(){
    if (FileName != NULL) {
        if (Contains(FileName, "\\")) {
            FileName = Replace(FileName, "\\", "/");
            FinalWorkingDirectory = Replace(WorkingDirectory, "\\", "/");
            int FinalFileNameLength = strlen(FinalWorkingDirectory) + strlen(FileName) + 2;
            char* FinalFileName = malloc(FinalFileNameLength + 1 * sizeof(char));
            String_Pointer_Check(FinalFileName, "Final File Name Allocation Fail");
            strcpy(FinalFileName, FinalWorkingDirectory);
            strcat(FinalFileName, FileName);
            free(FileName);
            FileName = malloc((FinalFileNameLength + 1) * sizeof(char));
            FileName[FinalFileNameLength] = '\0';
            strcpy(FileName, FinalFileName);
            free(FinalFileName);
        }
    }
}


void Verify_Valid_Papple_File(char* PotentialFileName, int ArgumentLength, int WorkingDirectoryLength){
    if (Contains(PotentialFileName, ".")){
        int FileNameLength = WorkingDirectoryLength + ArgumentLength;
        FileName = (char *) malloc((FileNameLength + 1) * sizeof(char));
        String_Pointer_Check(FileName, "File Name Pointer Allocation Fail");
        FileName[FileNameLength] = '\0';
        strcpy(FileName, PotentialFileName);
    }
    else {
        printf("You provided an invalid filename: %s\n", PotentialFileName);
        exit(EXIT_FAILURE);
    }
}


void Parse_User_Arguments(int ArgumentsCount, char* Arguments[]){
    if (ArgumentsCount == 1){
        printf("You provided no arguments.");
        exit(EXIT_FAILURE);
    }

    if (ArgumentsCount > 3){
        printf("You provided too many arguments, someting went wrong. Detected %d arguments.\n", ArgumentsCount);
        exit(EXIT_FAILURE);
    }

    for (int ArgumentIndex = 1; ArgumentIndex < ArgumentsCount; ArgumentIndex++) {
        size_t ArgumentLength = strlen(Arguments[ArgumentIndex]) + 3;
        ArgumentBuffer = malloc((ArgumentLength + 1) * sizeof(char));
        ArgumentBuffer[ArgumentLength] = '\0';
        String_Pointer_Check(ArgumentBuffer, "ArgumentBuffer Allocation Fail");
        strcpy(ArgumentBuffer, Arguments[ArgumentIndex]);
        if (ArgumentIndex == 1){
            Verify_Valid_Papple_File(ArgumentBuffer, ArgumentLength,  WorkingDirectoryLength);
        }
        free(ArgumentBuffer);
    }
}


void Setup_Working_Directory(){
    if (getcwd(WorkingDirectory, sizeof(WorkingDirectory)) == NULL) {
        perror("Failed to obtain current working directory.");
        exit(EXIT_FAILURE);
    }
    WorkingDirectoryLength = strlen(WorkingDirectory);
}