#include <stdio.h>
#include <stdlib.h>
#include "Structures.h"

void String_Pointer_Check(char* Pointer, const char* PointerName){
    if (Pointer == NULL) {
        puts(PointerName);
        exit(EXIT_FAILURE);
    }
}

void CharList_Pointer_Check(char** Pointer, const char* PointerName){
    if (Pointer == NULL) {
        puts(PointerName);
        exit(EXIT_FAILURE);
    }
}

void StringList_Pointer_Check(StringList* Pointer, const char* PointerName){
    if (Pointer == NULL) {
        puts(PointerName);
        exit(EXIT_FAILURE);
    }
}

void File_Pointer_Check(FILE* Pointer, const char* PointerName){
    if (Pointer == NULL) {
        puts(PointerName);
        exit(EXIT_FAILURE);
    }
}

void VariableDeclaration_Pointer_Check(VariableDeclaration* Pointer, const char* PointerName){
    if (Pointer == NULL) {
        puts(PointerName);
        exit(EXIT_FAILURE);
    }
}

void Output_Pointer_Check(OutputFunction* Pointer, const char* PointerName){
    if (Pointer == NULL) {
        puts(PointerName);
        exit(EXIT_FAILURE);
    }
}

void Input_Pointer_Check(InputFunction* Pointer, const char* PointerName){
    if (Pointer == NULL) {
        puts(PointerName);
        exit(EXIT_FAILURE);
    }
}

void Pair_Pointer_Check(Pair* Pointer, const char* PointerName){
    if ((Pair*) Pointer == NULL |
        Pointer->Key == NULL |
        Pointer->Value == NULL) {
        puts(PointerName);
        exit(EXIT_FAILURE);
    }
}