#ifndef POINTERCHECKS_H
#define POINTERCHECKS_H
#include "stdio.h"
#include "Structures.h"

void String_Pointer_Check(char* Pointer, const char* PointerName);
void CharList_Pointer_Check(char** Pointer, const char* PointerName);
void StringList_Pointer_Check(StringList* Pointer, const char* PointerName);
void File_Pointer_Check(FILE* Pointer, const char* PointerName);
void Function_Pointer_Check(Function* Pointer, const char* PointerName);

#endif