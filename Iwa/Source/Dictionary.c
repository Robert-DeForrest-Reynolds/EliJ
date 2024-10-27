#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Dictionary.h"
#include "Structures.h"
#include "Hash.h"

Dictionary* Create_Dictionary(int Size) {
    Dictionary* Dict = (Dictionary*) malloc(sizeof(Dictionary));
    Dict->Size = Size;
    Dict->Table = (Pair**) malloc(Size * sizeof(Pair*));
    Dict->InnerDepth = (int*) calloc(Size, sizeof(int));

    for (int Index = 0; Index < Size; Index++) {
        Dict->Table[Index] = NULL;
    }
    return Dict;
}

Pair* Create_Pair(void* Key, Type KeyType, void* Value, Type ValueType) {
    Pair* NewPair = (Pair*)malloc(sizeof(Pair));
    NewPair->Key = Key;
    NewPair->KeyType = KeyType;
    NewPair->Value = Value;
    NewPair->ValueType = ValueType;
    NewPair->Next = NULL;
    return NewPair;
}

void Insert(Dictionary* Dict, void* Key, Type KeyType, void* Value, Type ValueType) {
    unsigned int Index = Hash(Key, Dict->Size);
    printf("%s: %d\n", (char*) Key, Index);
    Pair* NewPair = Create_Pair(Key, KeyType, Value, ValueType);

    if (Dict->Table[Index] == NULL) {
        Dict->Table[Index] = NewPair;
    } else {
        Pair* Current = Dict->Table[Index];
        int Depth = 0;

        while (Current->Next != NULL) {
            Depth++;
            Current = Current->Next;
        }
        Current->Next = NewPair;

        Dict->InnerDepth[Index] = Depth + 1;

        if (Dict->InnerDepth[Index] >= 5) {
            printf("Warning: High collision depth (%d) detected at index %d.\n", Dict->InnerDepth[Index], Index);
        }
    }
}

Any* Find(Dictionary* Dict, void* Key) {
    unsigned int Index = Hash(Key, Dict->Size);
    Pair* Current = Dict->Table[Index];

    while (Current != NULL) {
        if (Current->KeyType == STRING){
            if (strcmp((char*) Current->Key, (char *) Key) == 0) {
                Any* FoundValue = (Any*) malloc(sizeof(Any));
                FoundValue->Value = Current->Value;
                FoundValue->ValueType = Current->ValueType;
                puts("Found a value");
                return FoundValue;
            }
        }
        Current = Current->Next;
    }
    return NULL;
}

void Free_Dictionary(Dictionary* Dict) {
    for (int i = 0; i < Dict->Size; i++) {
        Pair* Current = Dict->Table[i];
        while (Current != NULL) {
            Pair* Temp = Current;
            Current = Current->Next;
            free(Temp);
        }
    }
    free(Dict->Table);
    free(Dict->InnerDepth);
    free(Dict);
}