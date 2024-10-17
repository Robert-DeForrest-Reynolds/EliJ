#ifndef POINTERCHECKS_H
#define POINTERCHECKS_H
#include "Split.h"

void String_Pointer_Check(char* Pointer, const char* PointerName);
void String_List_Pointer_Check(char** Pointer, const char* PointerName);
void SplitResult_Pointer_Check(SplitResult* Pointer, const char* PointerName);

#endif