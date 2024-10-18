#include <stdio.h>
#include <stdlib.h>

void String_Pointer_Check(char* Pointer, const char* PointerName){
    if (Pointer == NULL) {
        puts(PointerName);
        exit(EXIT_FAILURE);
    }
}

void String_List_Pointer_Check(char** Pointer, const char* PointerName){
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