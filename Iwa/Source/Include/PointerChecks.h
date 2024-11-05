#ifndef POINTERCHECKS_H
#define POINTERCHECKS_H
#include "stdio.h"
#include "Structures.h"

void String_Pointer_Check(char* Pointer, const char* PointerName);
void CharList_Pointer_Check(char** Pointer, const char* PointerName);
void StringList_Pointer_Check(StringList* Pointer, const char* PointerName);
void File_Pointer_Check(FILE* Pointer, const char* PointerName);
void VariableDeclaration_Pointer_Check(VariableDeclaration* Pointer, const char* PointerName);
void Output_Pointer_Check(OutputFunction* Pointer, const char* PointerName);
void Input_Pointer_Check(InputFunction* Pointer, const char* PointerName);
void FindBetween_Pointer_Check(FindBetweenFunction* Pointer, const char* PointerName);
void Pair_Pointer_Check(Pair* Pointer, const char* PointerName);

#endif