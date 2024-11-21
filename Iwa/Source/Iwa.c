#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "ctype.h"
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
#include "LeftTrim.h"
#include "Reverse.h"
#include "Split.h"
#include "Trim.h"

Dictionary* Globals;
char* ArgumentBuffer;
char* FileName;
char WorkingDirectory[1024 * 1024]; // 1MB
int WorkingDirectoryLength;
char* FinalWorkingDirectory;
StringList* Instructions;

void Variable_Declaration(char* VariableName, char* VariableValue, Type VariableValueType);
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
    int VariableValueLength = strlen(VariableValue);
    switch(VariableValueType){
        case STRING:{
            // We need to check if the string is properly wrapped in quotes, if not, wrap it
            if (VariableValue[0] != '\"' && VariableValue[strlen(VariableValue)-1] != '\"'){
                char* WrappedString = malloc((VariableValueLength + 3) * sizeof(char));
                WrappedString[VariableValueLength + 2] = '\0';
                strcpy(WrappedString+1, VariableValue);
                WrappedString[0] = '"';
                WrappedString[VariableValueLength + 1] = '"';
                Insert(Globals, strdup(VariableName), STRING, strdup(WrappedString), VariableValueType);
                break;
            }
            Insert(Globals, strdup(VariableName), STRING, strdup(VariableValue), VariableValueType);
            break;
        }
        case INT:{
            Insert(Globals, strdup(VariableName), STRING, strdup(VariableValue), VariableValueType);
            break;
        }
        default:{
            printf("Couldn't determine variable type during variable declaration");
        }
    }
}

char* Check_If_Function(char* VariableValue, int LineNumber){
    // If variable value is a function call
    int PotentialFunctionParan = Find(VariableValue, "(");
    if (PotentialFunctionParan == -1) { return NULL; }
    char* PotentialKeyword = malloc(((PotentialFunctionParan) + 1) * sizeof(char));
    PotentialKeyword[PotentialFunctionParan] = '\0';
    strncpy(PotentialKeyword, VariableValue, PotentialFunctionParan);
    Any* PotentialFunction = Lookup(Globals, PotentialKeyword);
    if (PotentialFunction != NULL){
        switch(PotentialFunction->ValueType){
            case OUTPUT:{
                printf("Out() does not return any value, do not user it's return.");
                exit(EXIT_FAILURE);
            }
            case INPUT:{
                Any* InstructionReturn = Evaluate_Instruction(VariableValue, LineNumber);
                if (InstructionReturn != NULL){
                    switch (InstructionReturn->ValueType){
                        case STRING:{
                            return (char*) InstructionReturn->Value;
                            break;
                        }
                        default:
                            puts("Unknown ValueType when searching for instruction return type\n");
                            break;
                    }
                }
            }
            case STRING_RTN:{
                char* Parameters = Find_Between(VariableValue + PotentialFunctionParan, "(", ")");
                Any* InstructionReturn = Evaluate_Instruction(VariableValue, LineNumber);
                if (InstructionReturn != NULL){
                    free(VariableValue);
                    free(PotentialFunction);
                    free(InstructionReturn);
                    return (char*) InstructionReturn->Value;
                }
                break;
            }
        }
    }
    free(PotentialFunction);
    return NULL;
}

// God damn PEMDAS
char* Check_If_Expression(char* VariableValue, int LineNumber){
    #if DEBUG
    printf("Potential Expression: %s\n", VariableValue);
    #endif
    int ExpressionStackMax = 1024;
    int*                 * Values = malloc(ExpressionStackMax * sizeof(int*));
    int DigitCounter = 0;
    int VariableValueLength = strlen(VariableValue);
    for (int Index = 0; Index < VariableValueLength; Index++){
        if (isdigit(VariableValue[Index])){
            printf("Found digit\n");
            DigitCounter++;
        }
        if (Index == (VariableValueLength - 1)){
            char* Number = malloc((DigitCounter + 1) * sizeof(char));
            Number[DigitCounter] = '\0';
            if (DigitCounter == 1){
                strcpy(Number, (VariableValue+Index));
                printf("%d, Last Number: %s\n", DigitCounter, Number);
                DigitCounter = 0;
            }
            else {
                strncpy(Number, (VariableValue+Index)-DigitCounter, DigitCounter);
                printf("%d, %c, Last Number: %s\n", DigitCounter, VariableValue[Index], Number);
                DigitCounter = 0;
            }
        }
        else if (DigitCounter != 0 && VariableValue[Index] == ' ' || VariableValue[Index] == '+'){
            char* Number = malloc((DigitCounter + 1) * sizeof(char));
            Number[DigitCounter] = '\0';
            strncpy(Number, (VariableValue+Index)-DigitCounter, DigitCounter);
            DigitCounter = 0;
            printf("Number: %s\n", Number);
        }
    }
    return NULL;
}


char** Find_Declaration_Values(Type VariableType, char* UnparsedValues, char* Instruction, int LineNumber){
    #if DEBUG
        printf("Finding Declaration Values\n");
    #endif
    char** Values = malloc(2 * sizeof(char*));
    CharList_Pointer_Check(Values, "Declaration Values Allocation Fail");
    bool NoSeparation = false;

    int SearchIndex = Left_Trim(UnparsedValues);

    for (int CharacterIndex = SearchIndex; CharacterIndex < strlen(UnparsedValues+SearchIndex); CharacterIndex++){
        if (UnparsedValues[CharacterIndex] == ' ' | UnparsedValues[CharacterIndex] == '='){
            int NameLength = (CharacterIndex - SearchIndex);
            Values[0] = malloc((NameLength + 1) * sizeof(char));
            String_Pointer_Check(Values[0], "Variable Name Allocation Fail");
            Values[0][NameLength] = '\0';
            strncpy(Values[0], UnparsedValues+SearchIndex, NameLength);
            if (UnparsedValues[CharacterIndex] == '='){
                SearchIndex = Left_Trim(UnparsedValues+CharacterIndex) + CharacterIndex;
            } else {
                SearchIndex = Left_Trim(UnparsedValues+CharacterIndex) + CharacterIndex;
                if (UnparsedValues[SearchIndex] != '='){
                    printf("Missing a = sign at line: %d, index: %d\n", LineNumber, SearchIndex);
                    exit(EXIT_FAILURE);
                }
                SearchIndex += 1;
                SearchIndex = Left_Trim(UnparsedValues+SearchIndex) + SearchIndex;
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
    
    #if DEBUG
    printf("Variable Declaration Value: %s\n", Values[1]);
    #endif
    
    // Yo, this is just a string man, just return, nothing else
    if (Values[1][0] == '"' && Values[1][ValueLength-1] == '"'){
        return Values;
    }

    char* PotentialFunctionValue = Check_If_Function(Values[1], LineNumber);
    if (PotentialFunctionValue != NULL){
        int FunctionValueLength = strlen(PotentialFunctionValue);
        free(Values[1]);
        Values[1] = malloc((FunctionValueLength + 1) * sizeof(char));
        Values[1][FunctionValueLength] = '\0';
        strcpy(Values[1], PotentialFunctionValue);
        free(PotentialFunctionValue);
        return Values;
    }

    char* PotentialExpressionValue = Check_If_Expression(Values[1], LineNumber);
    if (PotentialExpressionValue != NULL){
        int ExpressionValueLength = strlen(PotentialExpressionValue);
        free(Values[1]);
        Values[1] = malloc((ExpressionValueLength + 1) * sizeof(char));
        Values[1][ExpressionValueLength] = '\0';
        strcpy(Values[1], PotentialExpressionValue);
        free(PotentialExpressionValue);
        return Values;
    }

    return Values;
}


Any* Globals_Lookup(char* Parameter){
    Any* ParameterValue = Lookup(Globals, Parameter);
    if (ParameterValue == NULL){
        printf("%s does not exist\n", Parameter);
        exit(EXIT_FAILURE);
    }
    return ParameterValue;
}


Any* Handle_String_Return(char* Instruction, Any* InstructionKeyword, int InstructionLength, int ValuesStartIndex, int LineNumber){
    switch (InstructionKeyword->FuncType){
        case FIND_BETWEEN:{
            char* Parameters = Find_Between(Instruction, "(", ")");
            StringList* ParameterList = Split(Parameters, ',');
            char** ParametersValues = malloc(3 * sizeof(char*));
            for (int ElementIndex = 0; ElementIndex < ParameterList->ElementCount; ElementIndex++){
                char* TrimmedParameter = Trim(ParameterList->List[ElementIndex]);
                Any* PotentialVariable = Lookup(Globals, TrimmedParameter);
                if (PotentialVariable != NULL){
                    char* StrippedVariable = Find_Between((char*) PotentialVariable->Value, "\"", "\"");
                    ParametersValues[ElementIndex] = StrippedVariable;
                }
                else {
                    char* PotentialString = Find_Between((char*) ParameterList->List[ElementIndex], "\"", "\"");
                    if (PotentialString != NULL){
                        ParametersValues[ElementIndex] = PotentialString;
                    }
                }
            }
            Any* ReturnValue = (Any*) malloc(sizeof(Any));
            ReturnValue->Value = Find_Between(ParametersValues[0], ParametersValues[1], ParametersValues[2]);
            ReturnValue->ValueType = STRING;
            return ReturnValue;
        }
    }
    return NULL;
}


Any* Execute_Statement(char* Instruction, char* VariableDeclarationType, Any* InstructionKeyword, int InstructionLength, int ValuesStartIndex, int LineNumber){
    #if DEBUG
    printf("Executing Statement: %s\n\n", Instruction);
    #endif
    if (InstructionKeyword != NULL){
        char* InstructionsValues = malloc((InstructionLength - ValuesStartIndex + 1) * sizeof(char));
        switch (InstructionKeyword->ValueType){
            case DECLARATION:{
                VariableDeclaration* VarDecl = (VariableDeclaration*) InstructionKeyword->Value;
                VariableDeclaration_Pointer_Check(VarDecl, "Variable Declaration Pointer Allocation Fail");
                String_Pointer_Check(InstructionsValues, "Value Buffer Allocation Fail");
                InstructionsValues[InstructionLength - ValuesStartIndex] = '\0';
                strncpy(InstructionsValues, Instruction + ValuesStartIndex, InstructionLength - ValuesStartIndex);
                Any* ValueType = Lookup(InternalTypeMap, VariableDeclarationType);
                if (ValueType == NULL){
                    puts("You magical fuck, how did you break this? That internal type doesn't exist.");
                    exit(EXIT_FAILURE);
                }
                if (ValueType->ValueType == TYPE){
                    Type DeclType = *(Type*) ValueType->Value;
                    char** Values = Find_Declaration_Values(DeclType, InstructionsValues, Instruction, LineNumber);
                    VarDecl->Function(Values[0], Values[1], DeclType);
                }
                free(InstructionsValues);
                break;
            }
            case OUTPUT:{
                OutputFunction* Func = (OutputFunction*) InstructionKeyword->Value;
                Output_Pointer_Check(Func, "Output Function Instruction Allocation Fail");
                char* Parameter;
                InstructionsValues[InstructionLength - ValuesStartIndex] = '\0';
                strncpy(InstructionsValues, Instruction + ValuesStartIndex, InstructionLength - ValuesStartIndex);
                int InstructionsValuesLength = strlen(InstructionsValues);
                Parameter = Find_Between(InstructionsValues, "(", ")");
                
                char* PotentialInnerString = Find_Between(Parameter, "\"", "\"");
                if (PotentialInnerString != NULL){
                    Any* Content = (Any*) malloc(sizeof(Any));
                    Content->Value = PotentialInnerString;
                    Content->ValueType = STRING;
                    Func->Function(Content);
                }
                else {
                    Any* ParameterValue = Globals_Lookup(Parameter);
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
                free(InstructionsValues);
                free(Parameter);
                break;
            }
            case INPUT:{
                InputFunction* Func = (InputFunction*) InstructionKeyword->Value;
                Input_Pointer_Check(Func, "Input Function Instruction Allocation Fail");
                Any* ReturnValue = (Any*) malloc(sizeof(Any));
                InstructionsValues[InstructionLength - ValuesStartIndex] = '\0';
                strncpy(InstructionsValues, Instruction + ValuesStartIndex, InstructionLength - ValuesStartIndex);
                char* Parameters = Find_Between(InstructionsValues, "(", ")"); // We need to handle if we find nothing
                int ParametersLength = strlen(Parameters);
                if (Parameters[0] == '\"' && Parameters[ParametersLength-1] == '\"'){
                    char* String = Find_Between(Parameters, "\"", "\"");
                    char* UserInput = Func->Function(String);
                    ReturnValue->Value = UserInput;
                    ReturnValue->ValueType = STRING;
                    free(String);
                } else {
                    char* UserInput = Func->Function("");
                    ReturnValue->Value = UserInput;
                    ReturnValue->ValueType = STRING;
                }
                free(InstructionsValues);
                free(Parameters);
                return ReturnValue;
            }
            case STRING_RTN: {
                Any* ReturnValue = Handle_String_Return(Instruction, InstructionKeyword, InstructionLength, ValuesStartIndex, LineNumber);
                return ReturnValue;
                break;
                
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
    int SearchIndex = Left_Trim(Instruction);
    for (int CharacterIndex = SearchIndex; CharacterIndex < InstructionLength-SearchIndex; CharacterIndex++){
        if (Instruction[CharacterIndex] == ' ' | Instruction[CharacterIndex] == '('){
            KeywordBuffer = malloc(((CharacterIndex-SearchIndex) + 1) * sizeof(char));
            String_Pointer_Check(KeywordBuffer, "Keyword Buffer Allocation Fail");
            KeywordBuffer[CharacterIndex-SearchIndex] = '\0';
            strncpy(KeywordBuffer, Instruction+SearchIndex, CharacterIndex-SearchIndex);
            Any* InstructionKeyword = Globals_Lookup(KeywordBuffer);
            Return = Execute_Statement(Instruction, KeywordBuffer, InstructionKeyword, InstructionLength, CharacterIndex, LineNumber);
            free(InstructionKeyword);
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
