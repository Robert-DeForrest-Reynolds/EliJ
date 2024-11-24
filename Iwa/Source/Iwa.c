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
#include "Count.h"
#include "Remove.h"

Dictionary* Globals;
Dictionary* ValidOperators;
char* ArgumentBuffer;
char* FileName;
char WorkingDirectory[1024 * 1024]; // 1MB
int WorkingDirectoryLength;
char* FinalWorkingDirectory;
StringList* Instructions;
int SAFE_LONG_LENGTH = 20;

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
char* Resolve_Expression(char* Expression, int ExpressionLength, bool Recursive);

void Variable_Declaration(char* VariableName, char* VariableValue, Type VariableValueType){
    #if DEBUG
    printf("Inserting Variable Declaration: %s = %s : %s\n\n", VariableName, VariableValue, TypesAsStrings[VariableValueType]);
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
            char* EndCharacter;
            long ValueConverted = strtol(VariableValue, &EndCharacter, 10);
            if (*EndCharacter != '\0'){
                printf("INVALID_CONVERSION: Failed to validate Int can convert to long\n");
                exit(EXIT_FAILURE);
            }
            else {
                printf("This is a valid int: %s\n\n", VariableValue);
                Insert(Globals, strdup(VariableName), STRING, strdup(VariableValue), VariableValueType);
            }
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


int Find_Closing_Parenthesis(char* String){
    int ClosingIndex;
    int StringLength = strlen(String);
    int SubClosingCount = 0;
    for (int Index = 0; Index < StringLength; Index++){
        if (String[Index] == '('){
            SubClosingCount++;
        }
        if (String[Index] == ')'){
            if (SubClosingCount > 0){
                SubClosingCount--;
            }
            else {
                return Index;
            }
        }
    }
    return -1;
}

long Solve_Addition(long OperandOne, long OperandTwo){
    #if DEBUG
        printf("\nAddition: %lu + %lu\n", OperandOne, OperandTwo);
    #endif
    return OperandOne + OperandTwo;
}

long Solve_Multiplication(long OperandOne, long OperandTwo){
    #if DEBUG
        printf("\nMultiplcation: %lu * %lu\n", OperandOne, OperandTwo);
    #endif
    return OperandOne * OperandTwo;
}

// I hate comments, but this'll definitely need em
char* Resolve_Expression(char* Expression, int ExpressionLength, bool Recursive){
    if (!Expression || strlen(Expression) == 0) {
        return NULL;
    }

    char* WorkingExpression = strdup(Expression);
    if (!WorkingExpression) return NULL;

    // Handle nested parentheses first
    int ParenthesisDepth = 0;
    int StartIndex = -1;
    int EndIndex = -1;

    for (int Index = 0; Index < ExpressionLength; Index++) {
        if (WorkingExpression[Index] == '(') {
            ParenthesisDepth++;
            if (ParenthesisDepth == 1) StartIndex = Index;
        }
        else if (WorkingExpression[Index] == ')') {
            ParenthesisDepth--;
            if (ParenthesisDepth == 0) {
                EndIndex = Index;
                
                // Extract inner expression
                int InnerLength = EndIndex - StartIndex - 1;
                char* InnerExpression = malloc(InnerLength + 1);
                if (!InnerExpression) {
                    free(WorkingExpression);
                    return NULL;
                }
                strncpy(InnerExpression, WorkingExpression + StartIndex + 1, InnerLength);
                InnerExpression[InnerLength] = '\0';

                // Recursively evaluate inner expression
                char* InnerResult = Resolve_Expression(InnerExpression, InnerLength, true);
                free(InnerExpression);

                if (!InnerResult) {
                    free(WorkingExpression);
                    return NULL;
                }

                // Replace parenthesis expression with result
                int ResultLength = strlen(InnerResult);
                int NewLength = ExpressionLength - (EndIndex - StartIndex + 1) + ResultLength;
                char* NewExpression = malloc(NewLength + 1);
                if (!NewExpression) {
                    free(WorkingExpression);
                    free(InnerResult);
                    return NULL;
                }

                // Copy parts before parenthesis
                strncpy(NewExpression, WorkingExpression, StartIndex);
                // Copy evaluated result
                strcpy(NewExpression + StartIndex, InnerResult);
                // Copy parts after parenthesis
                strcpy(NewExpression + StartIndex + ResultLength, 
                      WorkingExpression + EndIndex + 1);

                free(InnerResult);
                free(WorkingExpression);
                WorkingExpression = NewExpression;
                ExpressionLength = NewLength;
                Index = StartIndex + ResultLength - 1; // Adjust index to continue after inserted result
            }
        }
    }

    // Handle multiplication first (operator precedence)
    for (int Index = 0; Index < ExpressionLength; Index++) {
        if (WorkingExpression[Index] == '*') {
            // Find left operand
            int LeftStart = Index - 1;
            while (LeftStart >= 0 && isdigit(WorkingExpression[LeftStart])) {
                LeftStart--;
            }
            LeftStart++;

            // Find right operand
            int RightEnd = Index + 1;
            while (RightEnd < ExpressionLength && isdigit(WorkingExpression[RightEnd])) {
                RightEnd++;
            }

            // Extract and convert operands
            char* LeftStr = malloc(Index - LeftStart + 1);
            char* RightStr = malloc(RightEnd - Index);
            if (!LeftStr || !RightStr) {
                free(LeftStr);
                free(RightStr);
                free(WorkingExpression);
                return NULL;
            }

            strncpy(LeftStr, WorkingExpression + LeftStart, Index - LeftStart);
            LeftStr[Index - LeftStart] = '\0';
            strncpy(RightStr, WorkingExpression + Index + 1, RightEnd - (Index + 1));
            RightStr[RightEnd - (Index + 1)] = '\0';

            char* EndPointer;
            long OperandOne = strtol(LeftStr, &EndPointer, 10);
            long OperandTwo = strtol(RightStr, &EndPointer, 10);
            long Result = Solve_Multiplication(OperandOne, OperandTwo);

            free(LeftStr);
            free(RightStr);

            // Convert result back to string
            char ResultStr[32];
            snprintf(ResultStr, sizeof(ResultStr), "%ld", Result);
            int ResultLen = strlen(ResultStr);

            // Create new expression with result
            int NewLength = ExpressionLength - (RightEnd - LeftStart) + ResultLen;
            char* NewExpression = malloc(NewLength + 1);
            if (!NewExpression) {
                free(WorkingExpression);
                return NULL;
            }

            strncpy(NewExpression, WorkingExpression, LeftStart);
            strcpy(NewExpression + LeftStart, ResultStr);
            strcpy(NewExpression + LeftStart + ResultLen, WorkingExpression + RightEnd);

            free(WorkingExpression);
            WorkingExpression = NewExpression;
            ExpressionLength = NewLength;
            Index = LeftStart + ResultLen - 1; // Adjust index to continue after inserted result
        }
    }

    // Handle addition
    for (int Index = 0; Index < ExpressionLength; Index++) {
        if (WorkingExpression[Index] == '+') {
            // Find left operand
            int LeftStart = Index - 1;
            while (LeftStart >= 0 && isdigit(WorkingExpression[LeftStart])) {
                LeftStart--;
            }
            LeftStart++;

            // Find right operand
            int RightEnd = Index + 1;
            while (RightEnd < ExpressionLength && isdigit(WorkingExpression[RightEnd])) {
                RightEnd++;
            }

            // Extract and convert operands
            char* LeftStr = malloc(Index - LeftStart + 1);
            char* RightStr = malloc(RightEnd - Index);
            if (!LeftStr || !RightStr) {
                free(LeftStr);
                free(RightStr);
                free(WorkingExpression);
                return NULL;
            }

            strncpy(LeftStr, WorkingExpression + LeftStart, Index - LeftStart);
            LeftStr[Index - LeftStart] = '\0';
            strncpy(RightStr, WorkingExpression + Index + 1, RightEnd - (Index + 1));
            RightStr[RightEnd - (Index + 1)] = '\0';

            char* EndPointer;
            long OperandOne = strtol(LeftStr, &EndPointer, 10);
            long OperandTwo = strtol(RightStr, &EndPointer, 10);
            long Result = Solve_Addition(OperandOne, OperandTwo);

            free(LeftStr);
            free(RightStr);

            // Convert result back to string
            char ResultStr[32];
            snprintf(ResultStr, sizeof(ResultStr), "%ld", Result);
            int ResultLen = strlen(ResultStr);

            // Create new expression with result
            int NewLength = ExpressionLength - (RightEnd - LeftStart) + ResultLen;
            char* NewExpression = malloc(NewLength + 1);
            if (!NewExpression) {
                free(WorkingExpression);
                return NULL;
            }

            strncpy(NewExpression, WorkingExpression, LeftStart);
            strcpy(NewExpression + LeftStart, ResultStr);
            strcpy(NewExpression + LeftStart + ResultLen, WorkingExpression + RightEnd);

            free(WorkingExpression);
            WorkingExpression = NewExpression;
            ExpressionLength = NewLength;
            Index = LeftStart + ResultLen - 1; // Adjust index to continue after inserted result
        }
    }

    return WorkingExpression;
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
        printf("INVALID_GLOBAL: %s does not exist\n", Parameter);
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
