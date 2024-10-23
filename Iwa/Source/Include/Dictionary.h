#ifndef DICTIONARY_H
#define DICTIONARY_H
#define MAX_COLLISION_DEPTH 3

#include "Structures.h"

Dictionary* Create_Dictionary(int Size);
Pair* Create_Pair(void* Key, char* KeyType, void* Value, char* ValueType);
void Insert(Dictionary* Dict, void* Key, char* KeyType, void* Value, char* ValueType);
char* Find(Dictionary* Dict, void* Key);
void Free_Dictionary(Dictionary* Dict);

#endif