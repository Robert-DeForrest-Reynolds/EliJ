#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "ReadFile.h"
#include "ReadFileLines.h"
#include "Contains.h"
#include "PointerChecks.h"
#include "Replace.h"
#include "Structures.h"
#include "Enums.h"
#include "Dictionary.h"
#include "Output.h"
#include "Input.h"
#include "Find.h"
#include "FindBetween.h"

Dictionary* Globals;
char* ArgumentBuffer;
char* FileName;
char WorkingDirectory[1024 * 1024]; // 1MB
int WorkingDirectoryLength;
char* FinalWorkingDirectory;
StringList* Instructions;

void Variable_Declaration(char* VariableName, char* VariableValue, Type VariableValueType);
int Skip_Whitespace(char* Line);
char** Find_Declaration_Values(Type VariableType, char* UnparsedValues, char* Instruction, int LineNumber);
Any* Execute_Statement(char* Instruction, char* KeywordBuffer, Any* InstructionKeyword, int InstructionLength, int CharacterIndex, int LineNumber);
Any* Evaluate_Instruction(char* Instruction, int LineNumber);
void Setup_Internal_Types(void);
void Setup_Globals(void);
void Run_Interpreter(void);
void Check_Windows_Style_Path(void);
void Verify_Valid_Papple_File(char* PotentialFileName, int ArgumentLength, int WorkingDirectoryLength);
void Parse_User_Arguments(int ArgumentsCount, char* Arguments[]);

void Variable_Declaration(char* VariableName, char* VariableValue, Type VariableValueType){
    #if DEBUG
    printf("Inserting Variable Declaration: %s = %s\n\n", VariableName, VariableValue);
    #endif
    Insert(Globals, strdup(VariableName), STRING, strdup(VariableValue), VariableValueType);
}

int Skip_Whitespace(char* Line){
    for (int Index = 0; Index < strlen(Line); Index++){
        if (Line[Index] != ' '){
            return Index;
        }
    }
    return -1;
}


char** Find_Declaration_Values(Type VariableType, char* UnparsedValues, char* Instruction, int LineNumber){
    char** Values = malloc(2 * sizeof(char*));
    CharList_Pointer_Check(Values, "Declaration Values Allocation Fail");
    bool NoSeparation = false;

    int SearchIndex = Skip_Whitespace(UnparsedValues);

    for (int CharacterIndex = SearchIndex; CharacterIndex < strlen(UnparsedValues+SearchIndex); CharacterIndex++){
        if (UnparsedValues[CharacterIndex] == ' ' | UnparsedValues[CharacterIndex] == '='){
            int NameLength = (CharacterIndex - SearchIndex);
            Values[0] = malloc((NameLength + 1) * sizeof(char));
            String_Pointer_Check(Values[0], "Variable Name Allocation Fail");
            Values[0][NameLength] = '\0';
            strncpy(Values[0], UnparsedValues+SearchIndex, NameLength);
            if (UnparsedValues[CharacterIndex] == '='){
                SearchIndex = Skip_Whitespace(UnparsedValues+CharacterIndex) + CharacterIndex;
            } else {
                SearchIndex = Skip_Whitespace(UnparsedValues+CharacterIndex) + CharacterIndex;
                if (UnparsedValues[SearchIndex] != '='){
                    printf("Missing a = sign at line: %d, index: %d\n", LineNumber, SearchIndex);
                    exit(EXIT_FAILURE);
                }
                SearchIndex += 1;
                SearchIndex = Skip_Whitespace(UnparsedValues+SearchIndex) + SearchIndex;
            }
            break;
        }
    }

    // Get variable value
    int ValueLength = strlen(UnparsedValues+SearchIndex);
    Values[1] = malloc((ValueLength + 1) * sizeof(char));
    String_Pointer_Check(Values[1], "Variable Value Allocation Fail");
    Values[1][ValueLength] = '\0';
    strncpy(Values[1], UnparsedValues+SearchIndex, ValueLength);

    // If variable value is a function call
    int PotentialFunctionEnd = Find(Values[1], "(");
    if (PotentialFunctionEnd != -1){
        char* PotentialKeyword = malloc(((PotentialFunctionEnd) + 1) * sizeof(char));
        PotentialKeyword[PotentialFunctionEnd] = '\0';
        strncpy(PotentialKeyword, Values[1], PotentialFunctionEnd);
        Any* PotentialFunction = Lookup(Globals, PotentialKeyword);
        if (PotentialFunction != NULL && PotentialFunction->ValueType == INPUT){
            Any* InstructionReturn = Evaluate_Instruction(Values[1], LineNumber);
            if (InstructionReturn != NULL){
                free(Values[1]);
                switch (InstructionReturn->ValueType){
                    case STRING:{
                        Values[1] = (char*) InstructionReturn->Value;
                        break;
                    }
                    default:
                        puts("Unknown ValueType when searching for instruction return type\n");
                        break;
                }
            }
        }
    }
    
    return Values;
}


Any* Execute_Statement(char* Instruction, char* KeywordBuffer, Any* InstructionKeyword, int InstructionLength, int ValuesStartIndex, int LineNumber){
    #if DEBUG
    printf("Executing Statement: %s\n\n", Instruction);
    #endif
    if (InstructionKeyword != NULL){
        switch (InstructionKeyword->ValueType){
            case DECLARATION:{
                VariableDeclaration* VarDecl = (VariableDeclaration*) InstructionKeyword->Value;
                VariableDeclaration_Pointer_Check(VarDecl, "Variable Declaration Pointer Allocation Fail");
                char* ValueBuffer = malloc((InstructionLength - ValuesStartIndex + 1) * sizeof(char));
                String_Pointer_Check(ValueBuffer, "Value Buffer Allocation Fail");
                ValueBuffer[InstructionLength - ValuesStartIndex] = '\0';
                strncpy(ValueBuffer, Instruction + ValuesStartIndex, InstructionLength - ValuesStartIndex);
                Any* ValueType = Lookup(InternalTypeMap, KeywordBuffer);
                if (ValueType == NULL){
                    puts("You magical fuck, how did you break this? That internal type doesn't exist.");
                    exit(EXIT_FAILURE);
                }
                if (ValueType->ValueType == TYPE){
                    Type DeclType = *(Type*) ValueType->Value;
                    char** Values = Find_Declaration_Values(DeclType, ValueBuffer, Instruction, LineNumber);
                    VarDecl->Function(Values[0], Values[1], DeclType);
                }
                free(ValueBuffer);
                break;
            }
            case OUTPUT:{
                OutputFunction* Func = (OutputFunction*) InstructionKeyword->Value;
                Output_Pointer_Check(Func, "Output Function Instruction Allocation Fail");
                char* ValueBuffer = malloc((InstructionLength - ValuesStartIndex + 1) * sizeof(char));
                char* Parameter;
                ValueBuffer[InstructionLength - ValuesStartIndex] = '\0';
                strncpy(ValueBuffer, Instruction + ValuesStartIndex, InstructionLength - ValuesStartIndex);
                int ValueBufferLength = strlen(ValueBuffer);
                if (ValueBuffer[0] == '(' && ValueBuffer[ValueBufferLength - 1] == ')'){
                    Parameter = malloc(((ValueBufferLength - 2) + 1) * sizeof(char));
                    String_Pointer_Check(Parameter, "Parameter Allocation Fail");
                    Parameter[ValueBufferLength-2] = '\0';
                    strncpy(Parameter, ValueBuffer+1, ValueBufferLength-2);
                } else {
                    printf("You are missing a paranthesis at your function call");
                    exit(EXIT_FAILURE);
                }

                if (Parameter[0] == '"' && Parameter[strlen(ValueBuffer) - 1] == '"'){
                    Any* Content = (Any*) malloc(sizeof(Any));
                    int ParameterLength = strlen(Parameter);
                    char* StrippedString = malloc(((ParameterLength - 2) + 1) * sizeof(char));
                    String_Pointer_Check(StrippedString, "Stripped String Allocation Fail");
                    StrippedString[ParameterLength-2] = '\0';
                    strncpy(StrippedString, Parameter+1, ParameterLength-2);
                    Content->Value = Parameter;
                    Content->ValueType = STRING;
                    Func->Function(Content);
                    free(StrippedString);
                } else {
                    Any* ParameterValue = Lookup(Globals, Parameter);
                    if (ParameterValue == NULL){
                        printf("%s does not exist\n", Parameter);
                        exit(EXIT_FAILURE);
                    }
                    else {
                        if (ParameterValue->ValueType == STRING){
                            int ParameterValueLength = strlen((char*) ParameterValue->Value);
                            int StrippedStringLength = ParameterValueLength - 2;
                            char* StrippedString = malloc((StrippedStringLength + 1) * sizeof(char));
                            String_Pointer_Check(StrippedString, "Stripped String Allocation Fail");
                            StrippedString[StrippedStringLength] = '\0';
                            strncpy(StrippedString, (char*) ParameterValue->Value+1, ParameterValueLength-2);
                            ParameterValue->Value = StrippedString;
                            Func->Function(ParameterValue);
                            free(StrippedString);

                        }
                        else if (ParameterValue->ValueType == INT) {
                            Func->Function(ParameterValue);
                        }
                    }
                }
                free(ValueBuffer);
                free(Parameter);
                break;
            }
            case INPUT:{
                InputFunction* Func = (InputFunction*) InstructionKeyword->Value;
                Input_Pointer_Check(Func, "Input Function Instruction Allocation Fail");
                Any* ReturnValue = (Any*) malloc(sizeof(Any));
                char* ValueBuffer = malloc((InstructionLength - ValuesStartIndex + 1) * sizeof(char));
                ValueBuffer[InstructionLength - ValuesStartIndex] = '\0';
                strncpy(ValueBuffer, Instruction + ValuesStartIndex, InstructionLength - ValuesStartIndex);
                char* Parameters = Find_Between(ValueBuffer, "(", ")");
                int ParametersLength = strlen(Parameters);
                if (Parameters[0] == '\"' && Parameters[ParametersLength-1] == '\"'){
                    char* String = Find_Between(Parameters, "\"", "\"");
                    char* UserInput = Func->Function(String);
                    ReturnValue->Value = UserInput;
                    ReturnValue->ValueType = STRING;
                    free(String);
                }
                free(ValueBuffer);
                free(Parameters);
                return ReturnValue;
            }
            default:
                puts("Unknown ValueType when searching for instruction type\n");
                break;
        }
    }
    return NULL;
}


Any* Evaluate_Instruction(char* Instruction, int LineNumber){
    #if DEBUG
    printf("Executing Instruction: %s\n\n", Instruction);
    #endif
    int InstructionLength = strlen(Instruction);
    Any* Return;
    char* KeywordBuffer;
    StringList InstructionSet;
    bool InitialCharacterFound = false;
    int SearchIndex;
    for (int CharacterIndex = 0; CharacterIndex < InstructionLength; CharacterIndex++){
        if (Instruction[CharacterIndex] != ' ') {
            InitialCharacterFound = true;
            SearchIndex = CharacterIndex;
            break;
        }
    }
    for (int CharacterIndex = SearchIndex; CharacterIndex < InstructionLength-SearchIndex; CharacterIndex++){
        if (InitialCharacterFound == true && Instruction[CharacterIndex] == ' ' | Instruction[CharacterIndex] == '('){
            KeywordBuffer = malloc(((CharacterIndex-SearchIndex) + 1) * sizeof(char));
            String_Pointer_Check(KeywordBuffer, "Keyword Buffer Allocation Fail");
            KeywordBuffer[CharacterIndex-SearchIndex] = '\0';
            strncpy(KeywordBuffer, Instruction+SearchIndex, CharacterIndex-SearchIndex);
            Any* InstructionKeyword = Lookup(Globals, KeywordBuffer);
            if (InstructionKeyword != NULL) {
                Return = Execute_Statement(Instruction, KeywordBuffer, InstructionKeyword, InstructionLength, CharacterIndex, LineNumber);
                free(InstructionKeyword);
            }
            free(KeywordBuffer);
            return Return;
        }
    }
    return NULL;
}


void Setup_Internal_Types(){
    Type* StringType = (Type*) malloc(sizeof(Type));
    Type* IntType = (Type*) malloc(sizeof(Type));
    Type* OutputType = (Type*) malloc(sizeof(Type));
    *StringType = STRING;
    *IntType = INT;
    *OutputType = OUTPUT;

    InternalTypeMap = Create_Dictionary(50);
    
    Insert(InternalTypeMap, strdup("String"), STRING, StringType, TYPE);
    Insert(InternalTypeMap, strdup("Int"), STRING, IntType, TYPE);
    Insert(InternalTypeMap, strdup("Out"), STRING, OutputType, TYPE);
    
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

    // Variable Types
    Insert(Globals, strdup("String"), STRING, VarDecl, DECLARATION);
    Insert(Globals, strdup("Int"), STRING, VarDecl, DECLARATION);
    Insert(Globals, strdup("Float"), STRING, VarDecl, DECLARATION);
    Insert(Globals, strdup("List"), STRING, VarDecl, DECLARATION);

    // Built-In Functions
    Insert(Globals, strdup("Out"), STRING, OutputFunc, OUTPUT);
    Insert(Globals, strdup("In"), STRING, InputFunc, INPUT);
    
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
            }
        }
    }
    #endif
}


void Run_Interpreter(){
    FILE* FilePointer = fopen(FileName, "r");
    File_Pointer_Check(FilePointer, "Read File Pointer Allocation Fail");

    int LineBufferSize = 1024;
    int LineCount = 0;
    char* LineBuffer = malloc(LineBufferSize * sizeof(char));
    String_Pointer_Check(LineBuffer, "Line Buffer Allocation Fail");
    
    while (fgets(LineBuffer, LineBufferSize, FilePointer)) {
        if (strcmp(LineBuffer, "\n") == 0) { continue; }
        int LineLength = strlen(LineBuffer);
        if (LineLength > 0 && LineBuffer[LineLength-1] == '\n') {
            LineBuffer[LineLength-1] = '\0';
            LineLength--;
        }
        Evaluate_Instruction(LineBuffer, LineCount);
        LineCount += 1;
    }

    free(LineBuffer);
    fclose(FilePointer);

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
    if (FileName == NULL){
        printf("Invalid Pineapple Filename");
        exit(EXIT_FAILURE);
    }
}


void Parse_User_Arguments(int ArgumentsCount, char* Arguments[]){
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


void Run_Iwa(int ArgumentsCount, char* Arguments[]){
    Setup_Globals();
    Setup_Internal_Types();

    if (ArgumentsCount > 1){
        Setup_Working_Directory();
        Parse_User_Arguments(ArgumentsCount, Arguments);
        Check_Windows_Style_Path();

        Run_Interpreter();
        free(FileName);
    }

    Free_Dictionary(Globals);
    Free_Dictionary(InternalTypeMap);
}


int main(int ArgumentsCount, char* Arguments[]) {
    Run_Iwa(ArgumentsCount, Arguments);
    return 0;
}
