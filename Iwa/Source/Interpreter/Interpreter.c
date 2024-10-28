#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Structures.h"
#include "Enums.h"
#include "Contains.h"
#include "PointerChecks.h"
#include "Dictionary.h"
#include "Output.h"
#include "Input.h"
#include "Split.h"
#include "FindBetween.h"

/*

Any* values are used to deal with user declared values.
The built-in functions are usable in the source code for the interpreter, as well as usable for the user.
Be very attentative when using built-in functions within the source-code, that isn't usable by the user, as there is a good chance there's a better way.

*/

Dictionary* Globals;


char* File_Name_Check(char* PotentialFileName, int ArgumentLength, int WorkingDirectoryLength){
    bool IsFileName = Contains(PotentialFileName, ".");
    char* FileNamePointer = (char *) malloc((WorkingDirectoryLength + ArgumentLength) * sizeof(char));
    if (IsFileName == true){
        String_Pointer_Check(FileNamePointer, "File Name Pointer Allocation Fail");
        strcpy(FileNamePointer, PotentialFileName);
    }
    return FileNamePointer;
}


StringList* Parse_Source_Code(char* FileName){
    printf("Trying to read source file %s\n", FileName);
    FILE* FilePointer = fopen(FileName, "r");
    File_Pointer_Check(FilePointer, "Read File Pointer Allocation Fail");

    int LineBufferSize = 1024;
    int LineCount = 0;
    char* LineBuffer = malloc(LineBufferSize * sizeof(char));

    while (fgets(LineBuffer, LineBufferSize, FilePointer)) {
        LineCount += 1;
    }

    StringList* Contents = (StringList*)malloc(sizeof(StringList));
    Contents->List = malloc((LineCount + 1) * sizeof(char*));
    StringList_Pointer_Check(Contents, "Read File Contents Pointer Allocation Fail");

    rewind(FilePointer);
    LineCount = 0;

    while (fgets(LineBuffer, LineBufferSize, FilePointer)) {
        if (strcmp(LineBuffer, "\n") == 0) { continue; }
        size_t LineLength = strlen(LineBuffer);
        if (LineLength > 0 && LineBuffer[LineLength - 1] == '\n') {
            LineBuffer[LineLength - 1] = '\0';
        }

        Contents->List[LineCount] = malloc((LineLength + 1) * sizeof(char));
        String_Pointer_Check(Contents->List[LineCount], "Read File Lines Inner String Allocation Fail");
        strcpy(Contents->List[LineCount], LineBuffer);

        LineCount += 1;
    }

    free(LineBuffer);
    fclose(FilePointer);

    Contents->List[LineCount] = NULL;
    Contents->ElementCount = LineCount;

    return Contents;
}


void Variable_Declaration(char* VariableName, char* VariableValue, Type VariableValueType){
    Insert(Globals, VariableName, STRING, VariableValue, VariableValueType);
}


// Most of this will be cleaned up when the program closes, and doesn't need to be freed during runtime at all
void Functions_Setup(){ printf("\nExecuting Functions_Setup\n");
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
    Insert(Globals, "String", STRING, VarDecl, DECLARATION);
    Insert(Globals, "Int", STRING, VarDecl, DECLARATION);
    Insert(Globals, "Float", STRING, VarDecl, DECLARATION);
    Insert(Globals, "List", STRING, VarDecl, DECLARATION);

    // Built-In Functions
    Insert(Globals, "Out", STRING, OutputFunc, OUTPUT);
    Insert(Globals, "In", STRING, InputFunc, INPUT);
}


// Declarations are correctly formatted as so:
// <space> == " "      (I hope that is obvious)
// <space>VariableName<space>=<space>Value
// Iterate past any space, and get the first character, and buffer out that word as the variable name
// Iterate past two spaces, and get the first character, and buffer out the value
// Delcare the variable dependant on the value's type
char** Find_Declaration_Values(Type VariableType, char* UnparsedValues){
    char** Values = malloc(2 * sizeof(char*));
    CharList_Pointer_Check(Values, "Declaration Values Allocation Fail");
    int UnparsedValuesLength = strlen(UnparsedValues);
    bool InitialCharacterFound = false;
    int SearchIndex;
    // Skip whitespace loop
    for (int CharacterIndex = 0; CharacterIndex < UnparsedValuesLength; CharacterIndex++){
        if (UnparsedValues[CharacterIndex] != ' ') {
            InitialCharacterFound = true;
            SearchIndex = CharacterIndex;
            break;
        }
    }
    // Get variable name loop
    for (int CharacterIndex = SearchIndex; CharacterIndex < UnparsedValuesLength; CharacterIndex++){
        if (UnparsedValues[CharacterIndex] == ' ') {
            Values[0] = malloc(((CharacterIndex-SearchIndex) + 1) * sizeof(char));
            Values[0][CharacterIndex-SearchIndex] = '\0';
            strncpy(Values[0], UnparsedValues+SearchIndex, CharacterIndex-SearchIndex);
            printf("Variable Name: %s\n", Values[0]);
            SearchIndex = CharacterIndex;
            break;
        }
    }
    // Get variable value loop
    int SpaceCount = 0;
    for (int CharacterIndex = SearchIndex; CharacterIndex < UnparsedValuesLength; CharacterIndex++){
        if (UnparsedValues[CharacterIndex] == ' '){
            SpaceCount++;
            continue;
        }
        if (SpaceCount == 1 && UnparsedValues[CharacterIndex] != '='){
            puts("Missing a =");
        }
        if (SpaceCount == 2){
            switch (VariableType){
                case STRING:{
                    Values[1] = malloc(((CharacterIndex-SearchIndex) + 1) * sizeof(char));
                    String_Pointer_Check(Values[1], "Failed to allocate for the variable value");
                    Values[1][UnparsedValuesLength-CharacterIndex] = '\0';
                    strncpy(Values[1], UnparsedValues+CharacterIndex, UnparsedValuesLength - CharacterIndex);
                    printf("Variable Value: %s\n", Values[1]);
                    SearchIndex = CharacterIndex;
                    break;
                }
                case INT:{
                    Values[1] = malloc(((CharacterIndex-SearchIndex) + 1) * sizeof(char));
                    String_Pointer_Check(Values[1], "Failed to allocate for the variable value");
                    Values[1][UnparsedValuesLength-CharacterIndex] = '\0';
                    strncpy(Values[1], UnparsedValues+CharacterIndex, UnparsedValuesLength - CharacterIndex);
                    int ValueAsInt = atoi(Values[1]);
                    printf("Variable Value: %d\n", ValueAsInt);
                    SearchIndex = CharacterIndex;
                    break;
                }
                default:
                    puts("Unknown ValueType when searching for declaration value type\n");
                    break;
            }
            break;
        }
    }
    return Values;
}


void Execute_Instruction(char* Instruction){ printf("\nExecuting Execute_Instruction\n");
    int InstructionLength = strlen(Instruction);
    char* KeyWordBuffer = malloc((InstructionLength + 1) * sizeof(char));
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
    for (int CharacterIndex = SearchIndex; CharacterIndex < InstructionLength; CharacterIndex++){
        if (InitialCharacterFound == true && Instruction[CharacterIndex] == ' ' | Instruction[CharacterIndex] == '('){
            strncpy(KeyWordBuffer, Instruction+SearchIndex, CharacterIndex-SearchIndex);
            KeyWordBuffer[CharacterIndex] = '\0';
            Any* InstructionKeyword = Lookup(Globals, (char *) KeyWordBuffer);
            if (InstructionKeyword != NULL){
                switch (InstructionKeyword->ValueType){
                    case DECLARATION:{
                        VariableDeclaration* VarDecl = (VariableDeclaration*) InstructionKeyword->Value;
                        VariableDeclaration_Pointer_Check(VarDecl, "Variable Declaration Pointer Allocation Fail");
                        char* ValueBuffer = malloc((InstructionLength - CharacterIndex + 1) * sizeof(char));
                        ValueBuffer[InstructionLength - CharacterIndex] = '\0';
                        strncpy(ValueBuffer, Instruction + CharacterIndex, InstructionLength - CharacterIndex);
                        Any* ValueType = Lookup(InternalTypeMap, KeyWordBuffer);
                        if (ValueType == NULL){ puts("You magical fuck, how did you break this? That internal type doesn't exist."); exit(EXIT_FAILURE); }
                        if (ValueType->ValueType == TYPE){
                            Type DeclType = (Type) ValueType->Value;
                            char** Values = Find_Declaration_Values(DeclType, ValueBuffer);
                            VarDecl->Function(Values[0], Values[1], DeclType);
                        }
                        free(ValueBuffer);
                        break;
                    }
                    case OUTPUT:{
                        OutputFunction* Func = (OutputFunction*) InstructionKeyword->Value;
                        Output_Pointer_Check(Func, "Output Function Instruction Allocation Fail");
                        char* ValueBuffer = malloc((InstructionLength - CharacterIndex + 1) * sizeof(char));
                        char* Parameter;
                        ValueBuffer[InstructionLength - CharacterIndex] = '\0';
                        strncpy(ValueBuffer, Instruction + CharacterIndex, InstructionLength - CharacterIndex);
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
                            puts(Parameter);
                            Any* ParameterValue = Lookup(Globals, Parameter);
                            if (ParameterValue == NULL){
                                printf("%s does not exist", Parameter);
                                exit(EXIT_FAILURE);
                            } else {
                                int ParameterValueLength = strlen((char*) ParameterValue->Value);
                                char* StrippedString = malloc(((ParameterValueLength - 2) + 1) * sizeof(char));
                                String_Pointer_Check(StrippedString, "Stripped String Allocation Fail");
                                StrippedString[ParameterValueLength] = '\0';
                                strncpy(StrippedString, (char*) ParameterValue->Value+1, ParameterValueLength-2);
                                ParameterValue->Value = StrippedString;
                                Func->Function(ParameterValue);
                                free(StrippedString);
                            }
                        }
                        free(ValueBuffer);
                        free(Parameter);
                        break;
                    }
                    default:
                        printf("%d", InstructionKeyword->ValueType);
                        puts("Unknown ValueType when searching for instruction type\n");
                        break;
                }
            }
            free(InstructionKeyword);
        }
    }
    free(KeyWordBuffer);
}


void Run_Interpreter(StringList* Instructions){
    printf("\nExecuting Run_Interpreter\n");
    Globals = Create_Dictionary(50);
    Functions_Setup();

    for (int LineIndex = 0; LineIndex < Instructions->ElementCount; LineIndex++){
        if (Instructions->List[LineIndex] != NULL){
            puts("\nExecuting instruction...\n");
            printf("Instruction: %s\n", Instructions->List[LineIndex]);
            Execute_Instruction(Instructions->List[LineIndex]);
            puts("Finished instruction");
        }
    }
}