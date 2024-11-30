
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "Dictionary.h"
#include "Find.h"
#include "FindBetween.h"
#include "Split.h"
#include "LeftTrimIndex.h"
#include "Trim.h"
#include "Remove.h"

#include "Expressions.h"
#include "Structures.h"
#include "Globals.h"
#include "Split.h"
#include "PointerChecks.h"
#include "Error.h"

void Variable_Declaration(char* VariableName, char* VariableValue, Type VariableValueType);
char* Check_If_Function(char* VariableValue, int LineNumber);
char* Check_If_Expression(char* VariableValue, int LineNumber);
int Find_Wrapped_Parenthesis(char* String);
char** Find_Declaration_Values(char* UnparsedValues, char* Instruction, int LineNumber);
Any* Globals_Lookup(char* Parameter, char* Instruction);
Any* Handle_String_Return(char* Instruction, Any* InstructionKeyword, int InstructionLength, int ValuesStartIndex, int LineNumber);
Any* Execute_Statement(char* Instruction, char* VariableDeclarationType, Any* InstructionKeyword, int InstructionLength, int ValuesStartIndex, int LineNumber);
Any* Evaluate_Instruction(char* Instruction, int LineNumber);
void Run_Interpreter();

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
                free(WrappedString);
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
                Insert(Globals, strdup(VariableName), STRING, strdup(VariableValue), VariableValueType);
            }
            break;
        }
        case FLOAT:{
            char* EndCharacter;
            long ValueConverted = strtof(VariableValue, &EndCharacter);
            if (*EndCharacter != '\0'){
                printf("INVALID_CONVERSION: Failed to validate Float can convert to float\n");
                exit(EXIT_FAILURE);
            }
            else {
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
            default:
                break;
        }
    }
    free(PotentialFunction);
    return NULL;
}


char* Solve_Concat(char* ConcatenationExpression, int ExpressionLength){
    #if DEBUG
        printf("\nConcatenation: %s\n", ConcatenationExpression);
    #endif
    StringList* ConcatSplit = Split(ConcatenationExpression, '+');
    int ConcatLength = 0;
    for (int Index = 0; Index < ConcatSplit->ElementCount; Index++){
        ConcatLength += strlen(ConcatSplit->List[Index]);
    }
    char* Concatenation = malloc((ConcatLength + 1) * sizeof(char));
    Concatenation[ConcatLength] = '\0';
    for (int Index = 0; Index < ConcatSplit->ElementCount; Index++){
        char* String = Find_Between(ConcatSplit->List[Index], "\"", "\"");
        strcat(Concatenation, String);
        free(String);
    }
    printf("Final concat: %s\n", Concatenation);
    return Concatenation;
}


char* Check_If_Expression(char* VariableValue, int LineNumber){
    #if DEBUG
    printf("\nPotential Expression: %s\n", VariableValue);
    #endif

    int VariableValueLength = strlen(VariableValue);
    for (int Index = 0; Index < VariableValueLength; Index++){
        if (VariableValue[Index] == '"'){
            char* ConcatenatedString = Solve_Concat(VariableValue, VariableValueLength);
            return ConcatenatedString;
        }
    }

    char* SpacelessExpression = Remove(VariableValue, " ");
    int SpacelessExpressionLength = strlen(SpacelessExpression);
    char* Result = Resolve_Expression(SpacelessExpression, SpacelessExpressionLength, false);

    if (Result != NULL){
        return Result;
    }
    else {
        return NULL;
    }
}


int Find_Wrapped_Parenthesis(char* String){
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


char** Find_Declaration_Values(char* UnparsedValues, char* Instruction, int LineNumber){
    #if DEBUG
        printf("Finding Declaration Values, unparsed values: %s\n", UnparsedValues);
    #endif
    char** Values = malloc(2 * sizeof(char*));
    CharList_Pointer_Check(Values, "Declaration Values Allocation Fail");
    bool NoSeparation = false;

    int SearchIndex = Left_Trim_Index(UnparsedValues);

    for (int CharacterIndex = SearchIndex; CharacterIndex < strlen(UnparsedValues+SearchIndex); CharacterIndex++){
        if (UnparsedValues[CharacterIndex] == ' ' | UnparsedValues[CharacterIndex] == '='){
            int NameLength = (CharacterIndex - SearchIndex);
            Values[0] = malloc((NameLength + 1) * sizeof(char));
            String_Pointer_Check(Values[0], "Variable Name Allocation Fail");
            Values[0][NameLength] = '\0';
            strncpy(Values[0], UnparsedValues+SearchIndex, NameLength);
            if (UnparsedValues[CharacterIndex] == '='){
                SearchIndex += Left_Trim_Index(UnparsedValues+(CharacterIndex+1)) + 1;
            } else {
                SearchIndex = Left_Trim_Index(UnparsedValues+CharacterIndex) + CharacterIndex;
                SearchIndex += 1;
                SearchIndex = Left_Trim_Index(UnparsedValues+SearchIndex) + SearchIndex;
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

    // Yo, this is just a string man, just return, nothing else
    if (Values[1][0] == '"' && Values[1][ValueLength-1] == '"'){
        printf("Just a string\n");
        return Values;
    }

    return Values;
}


Any* Globals_Lookup(char* Parameter, char* Instruction){
    Any* ParameterValue = Lookup(Globals, Parameter);
    if (ParameterValue == NULL){
        puts(Create_Error_Message(Instruction, "Identifier does not exist.", Find(Instruction, Parameter), strlen(Parameter)));
        exit(EXIT_FAILURE);
    }
    return ParameterValue;
}

// This handles any functions that return a String
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
        default:
            break;
    }
    return NULL;
}


Any* Execute_Statement(char* Instruction, char* VariableDeclarationType, Any* InstructionKeyword, int InstructionLength, int ValuesStartIndex, int LineNumber){
    #if DEBUG
    printf("Executing Statement: %s\n\n", Instruction);
    #endif
    if (InstructionKeyword != NULL){
        int InstructionsValuesLength = InstructionLength - ValuesStartIndex;
        char* InstructionsValues = malloc((InstructionsValuesLength + 1) * sizeof(char));
        String_Pointer_Check(InstructionsValues, "Value Buffer Allocation Fail");
        InstructionsValues[InstructionsValuesLength] = '\0';
        strncpy(InstructionsValues, Instruction + ValuesStartIndex, InstructionsValuesLength);
        switch (InstructionKeyword->ValueType){
            case DECLARATION:{
                VariableDeclaration* VarDecl = (VariableDeclaration*) InstructionKeyword->Value;
                VariableDeclaration_Pointer_Check(VarDecl, "Variable Declaration Pointer Allocation Fail");
            
                Any* ValueType = Lookup(InternalTypeMap, VariableDeclarationType);
                if (!ValueType){
                    puts("That internal type doesn't exist.");
                    exit(EXIT_FAILURE);
                }
                if (ValueType->ValueType == TYPE){
                    Type DeclType = *(Type*) ValueType->Value;
                    char** Values = Find_Declaration_Values(InstructionsValues, Instruction, LineNumber);
                    VarDecl->Function(Values[0], Values[1], DeclType);
                }
                free(InstructionsValues);
                break;
            }
            case INT:
            case FLOAT:
            case STRING:{
                Any* ExistingVariable = Globals_Lookup((char*) VariableDeclarationType, Instruction);
                char** Values = Find_Declaration_Values(Instruction+ValuesStartIndex, Instruction, LineNumber);
                Replace_Pair(Globals, (char*) VariableDeclarationType, STRING, Values[1], ExistingVariable->ValueType);
                free(InstructionsValues);
                break;
            }
            case OUTPUT:{
                OutputFunction* Func = (OutputFunction*) InstructionKeyword->Value;
                Output_Pointer_Check(Func, "Output Function Instruction Allocation Fail");
                char* Parameter;
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
                    Any* ParameterValue = Globals_Lookup(Parameter, Instruction);
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
                    else {
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
    printf("\nExecuting Instruction: %s\n\n", Instruction);
    #endif
    int InstructionLength = strlen(Instruction);
    Any* Return;
    char* KeywordBuffer;
    StringList InstructionSet;
    bool InitialCharacterFound = false;
    
    int KeywordIndexStart = Left_Trim_Index(Instruction); // Get rid of whitespace in case we have any tabs
    for (int CharacterIndex = KeywordIndexStart; CharacterIndex < InstructionLength - KeywordIndexStart; CharacterIndex++){
        if (Instruction[CharacterIndex] == ' ' | Instruction[CharacterIndex] == '(' | Instruction[CharacterIndex] == '='){
            int KeywordLength = CharacterIndex - KeywordIndexStart;
            KeywordBuffer = malloc((KeywordLength + 1) * sizeof(char));
            if (!KeywordBuffer){
                puts("Failed to allocation char* for KeywordBuffer in Evaluate_Instruction");
                exit(EXIT_FAILURE);
            }
            KeywordBuffer[KeywordLength] = '\0';
            strncpy(KeywordBuffer, Instruction+KeywordIndexStart, KeywordLength);
    
            Any* InstructionKeyword = Globals_Lookup(KeywordBuffer, Instruction);
            Return = Execute_Statement(Instruction, KeywordBuffer, InstructionKeyword, InstructionLength, CharacterIndex, LineNumber);
            free(InstructionKeyword);
            free(KeywordBuffer);
            return Return;
        }
    }
    return NULL;
}


void Run_Interpreter(){
    FILE* FilePointer = fopen(FileName, "r");
    char ErrorMessage[1024];
    snprintf(ErrorMessage, sizeof(ErrorMessage), "Failed to read %s. Most likely doesn't exist.", FileName);
    File_Pointer_Check(FilePointer, ErrorMessage);

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