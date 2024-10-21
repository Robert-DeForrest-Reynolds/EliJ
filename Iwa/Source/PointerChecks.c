#include <stdio.h>
#include <stdlib.h>
#include "Structures.h"

void String_Pointer_Check(char* Pointer, const char* PointerName){
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