#ifndef POINTERCHECKS_H
#define POINTERCHECKS_H
#include "stdio.h"

void String_Pointer_Check(char* Pointer, const char* PointerName);
void String_List_Pointer_Check(char** Pointer, const char* PointerName);
void File_Pointer_Check(FILE* Pointer, const char* PointerName);

#endif