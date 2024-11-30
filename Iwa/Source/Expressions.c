#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "Split.h"
#include "FindBetween.h"
#include "Structures.h"

long Solve_Addition(long OperandOne, long OperandTwo){
    #if DEBUG
        printf("\nAddition: %lu + %lu\n", OperandOne, OperandTwo);
    #endif
    return OperandOne + OperandTwo;
}

long Solve_Subtraction(long OperandOne, long OperandTwo){
    #if DEBUG
        printf("\nSubtraction: %lu - %lu\n", OperandOne, OperandTwo);
    #endif
    return OperandOne - OperandTwo;
}


long Solve_Multiplication(long OperandOne, long OperandTwo){
    #if DEBUG
        printf("\nMultiplication: %lu * %lu\n", OperandOne, OperandTwo);
    #endif
    return OperandOne * OperandTwo;
}

long Solve_Division(long OperandOne, long OperandTwo){
    #if DEBUG
        printf("\nDivision: %lu / %lu\n", OperandOne, OperandTwo);
    #endif
    return OperandOne / OperandTwo;
}

long** Find_Operands(char* WorkingExpression, int Index, int LeftStart, int RightEnd){
    char* LeftStr = malloc(Index - LeftStart + 1);
    char* RightStr = malloc(RightEnd - Index);
    if (!LeftStr || !RightStr) {
        free(LeftStr);
        free(RightStr);
        return NULL;
    }

    strncpy(LeftStr, WorkingExpression + LeftStart, Index - LeftStart);
    LeftStr[Index - LeftStart] = '\0';
    strncpy(RightStr, WorkingExpression + Index + 1, RightEnd - (Index + 1));
    RightStr[RightEnd - (Index + 1)] = '\0';

    char* EndPointer;
    long OperandOne = strtol(LeftStr, &EndPointer, 10);
    if (*EndPointer != '\0') { // OperandOne is not a number
        free(LeftStr);
        free(RightStr);
        return NULL;
    }
    long OperandTwo = strtol(RightStr, &EndPointer, 10);
    if (*EndPointer != '\0') { // OperandTwo is not a number
        free(LeftStr);
        free(RightStr);
        return NULL;
    }

    free(LeftStr);
    free(RightStr);

    long** Result = malloc(2 * sizeof(long*));
    Result[0] = malloc(sizeof(long));
    Result[1] = malloc(sizeof(long));
    *Result[0] = OperandOne;
    *Result[1] = OperandTwo;

    return Result;

}


char* Convert_Expression_Result(char* WorkingExpression, long Result, char ResultStr[], int ResultLen, int ExpressionLength, int LeftStart, int RightEnd){
    // Create new expression with result
    int NewLength = ExpressionLength - (RightEnd - LeftStart) + ResultLen;
    char* NewExpression = malloc((NewLength + 1) * sizeof(char));
    if (!NewExpression) {
        return NULL;
    }
    NewExpression[NewLength] = '\0';

    strncpy(NewExpression, WorkingExpression, LeftStart);
    strcpy(NewExpression + LeftStart, ResultStr);
    strcpy(NewExpression + LeftStart + ResultLen, WorkingExpression + RightEnd);
    return NewExpression;
}


char* Resolve_Any_Multiplication(char* WorkingExpression, int ExpressionLength){
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

            long** Operands = Find_Operands(WorkingExpression, Index, LeftStart, RightEnd);

            long Result = Solve_Multiplication(*Operands[0], *Operands[1]);
            free(Operands[0]);
            free(Operands[1]);
            free(Operands);

            // Convert result back to string
            char* ResultStr = malloc(33 * sizeof(char));
            ResultStr[33] = '\0';
            snprintf(ResultStr, sizeof(33), "%ld", Result);
            int ResultLength = strlen(ResultStr);

            // Convert result from long to char*
            WorkingExpression = Convert_Expression_Result(WorkingExpression, Result, ResultStr, ResultLength, ExpressionLength, LeftStart, RightEnd);
            if (WorkingExpression == NULL){
                free(ResultStr);
                return NULL;
            }
            ExpressionLength = strlen(WorkingExpression);
            Index = LeftStart + ResultLength; // Adjust index to continue after inserted result
            free(ResultStr);
        }
    }
    return WorkingExpression;
}


char* Resolve_Any_Division(char* WorkingExpression, int ExpressionLength){
    // Handle multiplication first (operator precedence)
    for (int Index = 0; Index < ExpressionLength; Index++) {
        if (WorkingExpression[Index] == '/') {
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

            long** Operands = Find_Operands(WorkingExpression, Index, LeftStart, RightEnd);

            long Result = Solve_Division(*Operands[0], *Operands[1]);
            free(Operands[0]);
            free(Operands[1]);
            free(Operands);

            // Convert result back to string
            char* ResultStr = malloc(33 * sizeof(char));
            ResultStr[33] = '\0';
            snprintf(ResultStr, sizeof(33), "%ld", Result);
            int ResultLength = strlen(ResultStr);

            // Convert result from long to char*
            WorkingExpression = Convert_Expression_Result(WorkingExpression, Result, ResultStr, ResultLength, ExpressionLength, LeftStart, RightEnd);
            if (WorkingExpression == NULL){
                free(ResultStr);
                return NULL;
            }
            ExpressionLength = strlen(WorkingExpression);
            Index = LeftStart + ResultLength; // Adjust index to continue after inserted result
            free(ResultStr);
        }
    }
    return WorkingExpression;
}


char* Resolve_Any_Addition(char* WorkingExpression, int ExpressionLength){
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

            long** Operands = Find_Operands(WorkingExpression, Index, LeftStart, RightEnd);
            long Result = Solve_Addition(*Operands[0], *Operands[1]);
            free(Operands[0]);
            free(Operands[1]);
            free(Operands);

            // Convert result back to string
            char* ResultStr = malloc(33 * sizeof(char));
            ResultStr[33] = '\0';
            snprintf(ResultStr, sizeof(33), "%ld", Result);
            int ResultLength = strlen(ResultStr);

            // Convert result from long to char*
            WorkingExpression = Convert_Expression_Result(WorkingExpression, Result, ResultStr, ResultLength, ExpressionLength, LeftStart, RightEnd);
            if (WorkingExpression == NULL){
                free(ResultStr);
                return NULL;
            }
            ExpressionLength = strlen(WorkingExpression);
            Index = LeftStart + ResultLength; // Adjust index to continue after inserted result
            free(ResultStr);
        }
    }
    return WorkingExpression;
}


char* Resolve_Any_Subtraction(char* WorkingExpression, int ExpressionLength){
    // Handle addition
    for (int Index = 0; Index < ExpressionLength; Index++) {
        if (WorkingExpression[Index] == '-') {
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

            long** Operands = Find_Operands(WorkingExpression, Index, LeftStart, RightEnd);
            long Result = Solve_Subtraction(*Operands[0], *Operands[1]);
            free(Operands[0]);
            free(Operands[1]);
            free(Operands);

            // Convert result back to string
            char* ResultStr = malloc(33 * sizeof(char));
            ResultStr[33] = '\0';
            snprintf(ResultStr, sizeof(33), "%ld", Result);
            int ResultLength = strlen(ResultStr);

            // Convert result from long to char*
            WorkingExpression = Convert_Expression_Result(WorkingExpression, Result, ResultStr, ResultLength, ExpressionLength, LeftStart, RightEnd);
            if (WorkingExpression == NULL){
                free(ResultStr);
                return NULL;
            }
            ExpressionLength = strlen(WorkingExpression);
            Index = LeftStart + ResultLength; // Adjust index to continue after inserted result
            free(ResultStr);
        }
    }
    return WorkingExpression;
}


// I hate comments, but this'll definitely need em
char* Resolve_Expression(char* Expression, int ExpressionLength, bool Recursive){
    #if Debug
    printf("Resolving Expression: %s\n", Expression);
    #endif
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

    WorkingExpression = Resolve_Any_Multiplication(WorkingExpression, ExpressionLength);
    ExpressionLength = strlen(WorkingExpression);
    
    WorkingExpression = Resolve_Any_Division(WorkingExpression, ExpressionLength);
    ExpressionLength = strlen(WorkingExpression);

    WorkingExpression = Resolve_Any_Addition(WorkingExpression, ExpressionLength);
    ExpressionLength = strlen(WorkingExpression);
    
    WorkingExpression = Resolve_Any_Subtraction(WorkingExpression, ExpressionLength);
    ExpressionLength = strlen(WorkingExpression);
    

    return WorkingExpression;
}