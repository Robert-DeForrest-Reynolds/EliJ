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


void Parse_Source_Code(){
    FILE* FilePointer = fopen(FileName, "r");
    File_Pointer_Check(FilePointer, "Read File Pointer Allocation Fail");

    int LineBufferSize = 1024;
    int LineCount = 0;
    char* LineBuffer = malloc(LineBufferSize * sizeof(char));

    while (fgets(LineBuffer, LineBufferSize, FilePointer)) {
        LineCount += 1;
    }

    Instructions = (StringList*)malloc(sizeof(StringList));
    Instructions->List = malloc((LineCount + 1) * sizeof(char*));
    StringList_Pointer_Check(Instructions, "Read File Contents Pointer Allocation Fail");

    rewind(FilePointer);
    LineCount = 0;

    while (fgets(LineBuffer, LineBufferSize, FilePointer)) {
        if (strcmp(LineBuffer, "\n") == 0) { continue; }
        size_t LineLength = strlen(LineBuffer);
        if (LineLength > 0 && LineBuffer[LineLength - 1] == '\n') {
            LineBuffer[LineLength - 1] = '\0';
        }

        Instructions->List[LineCount] = malloc((LineLength + 1) * sizeof(char));
        String_Pointer_Check(Instructions->List[LineCount], "Read File Lines Inner String Allocation Fail");
        strcpy(Instructions->List[LineCount], LineBuffer);

        LineCount += 1;
    }

    free(LineBuffer);
    fclose(FilePointer);

    Instructions->List[LineCount] = NULL;
    Instructions->ElementCount = LineCount;
}


void Variable_Declaration(char* VariableName, char* VariableValue, Type VariableValueType){
    Insert(Globals, strdup(VariableName), STRING, strdup(VariableValue), VariableValueType);
}


int Next_NonWhitespace(char* Line){
    for (int Index = 0; Index < strlen(Line); Index++){
        if (Line[Index] == ' '){
            return Index+1;
        }
    }
    return -1;
}


// Declarations are correctly formatted as so:
// <space> == " "      (I hope that is obvious)
// <space>VariableName<space>=<space>Value
// Iterate past any space, and get the first character, and buffer out that word as the variable name
// Iterate past two spaces, and get the first character, and buffer out the value
// Delcare the variable dependant on the value's type
// Values[0] == Variable Names
// Values[1] == Variable Value
char** Find_Declaration_Values(Type VariableType, char* UnparsedValues, char* Instruction, int LineNumber){
    char** Values = malloc(2 * sizeof(char*));
    CharList_Pointer_Check(Values, "Declaration Values Allocation Fail");

    int SearchIndex = Next_NonWhitespace(UnparsedValues);

    // Get variable name
    int FirstCharacterIndex = SearchIndex;
    int NameLength = Find(UnparsedValues+SearchIndex, " ");
    Values[0] = malloc((NameLength + 1) * sizeof(char));
    String_Pointer_Check(Values[0], "Variable Name Allocation Fail");
    Values[0][NameLength] = '\0';
    strncpy(Values[0], UnparsedValues+FirstCharacterIndex, NameLength);
    
    SearchIndex = Next_NonWhitespace(UnparsedValues+SearchIndex) + SearchIndex;
    if (UnparsedValues[SearchIndex] != '='){
        printf("Missing a + sign at line: %d", LineNumber);
        SearchIndex += 1;
    }

    SearchIndex = Next_NonWhitespace(UnparsedValues+SearchIndex) + SearchIndex;

    // Get variable value
    int ValueLength = strlen(UnparsedValues+SearchIndex);
    Values[1] = malloc((ValueLength + 1) * sizeof(char));
    String_Pointer_Check(Values[1], "Variable Value Allocation Fail");
    Values[1][ValueLength] = '\0';
    strncpy(Values[1], UnparsedValues+SearchIndex, ValueLength);
    SearchIndex = SearchIndex;
    
    return Values;
}


void Execute_Statement(char* Instruction, char* KeywordBuffer, Any* InstructionKeyword, int InstructionLength, int CharacterIndex, int LineNumber){
    if (InstructionKeyword != NULL){
        switch (InstructionKeyword->ValueType){
            case DECLARATION:{
                VariableDeclaration* VarDecl = (VariableDeclaration*) InstructionKeyword->Value;
                VariableDeclaration_Pointer_Check(VarDecl, "Variable Declaration Pointer Allocation Fail");
                char* ValueBuffer = malloc((InstructionLength - CharacterIndex + 1) * sizeof(char));
                String_Pointer_Check(ValueBuffer, "Value Buffer Allocation Fail");
                ValueBuffer[InstructionLength - CharacterIndex] = '\0';
                strncpy(ValueBuffer, Instruction + CharacterIndex, InstructionLength - CharacterIndex);
                Any* ValueType = Lookup(InternalTypeMap, KeywordBuffer);
                if (ValueType == NULL){ puts("You magical fuck, how did you break this? That internal type doesn't exist."); exit(EXIT_FAILURE); }
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
                    Any* ParameterValue = Lookup(Globals, Parameter);
                    if (ParameterValue == NULL){
                        printf("%s does not exist\n", Parameter);
                        exit(EXIT_FAILURE);
                    } else {
                        if (ParameterValue->ValueType == STRING){
                            int ParameterValueLength = strlen((char*) ParameterValue->Value);
                            char* StrippedString = malloc(((ParameterValueLength - 2) + 1) * sizeof(char));
                            String_Pointer_Check(StrippedString, "Stripped String Allocation Fail");
                            StrippedString[ParameterValueLength] = '\0';
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
            default:
                puts("Unknown ValueType when searching for instruction type\n");
                break;
        }
    }
}


void Execute_Instruction(char* Instruction, int LineNumber){
    int InstructionLength = strlen(Instruction);
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
                Execute_Statement(Instruction, KeywordBuffer, InstructionKeyword, InstructionLength, CharacterIndex, LineNumber);
                free(InstructionKeyword);
            }
            free(KeywordBuffer);
            return;
        }
    }
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
}


void Run_Interpreter(){
    if (Instructions == NULL){
        printf("Instructions are null");
        exit(EXIT_FAILURE);
    }
    for (int LineIndex = 0; LineIndex < Instructions->ElementCount; LineIndex++){
        if (Instructions->List[LineIndex] != NULL){
            Execute_Instruction(Instructions->List[LineIndex], LineIndex);
        }
    }
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
    Setup_Working_Directory();
    Parse_User_Arguments(ArgumentsCount, Arguments);
    Check_Windows_Style_Path();
    Setup_Globals();
    Setup_Internal_Types();
    Parse_Source_Code();
    Run_Interpreter();

    Free_Dictionary(Globals);
    Free_Dictionary(InternalTypeMap);
    free(FileName);
}


int main(int ArgumentsCount, char* Arguments[]) {
    Run_Iwa(ArgumentsCount, Arguments);
    return 0;
}
