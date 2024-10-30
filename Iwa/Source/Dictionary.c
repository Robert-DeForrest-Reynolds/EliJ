#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Dictionary.h"
#include "Structures.h"
#include "Hash.h"
#include "PointerChecks.h"

Dictionary* Create_Dictionary(int Size) {
    Dictionary* Dict = (Dictionary*) malloc(sizeof(Dictionary));
    if (Dict == NULL) {
        return NULL;
    }
    
    Dict->Table = (Pair**) malloc(Size * sizeof(Pair*));
    if (Dict->Table == NULL) {
        free(Dict);
        return NULL;
    }
    
    Dict->InnerDepth = 0;
    
    Dict->Size = Size;
    Dict->Filled = 0;  // Initialize this field
    
    for (int Index = 0; Index < Size; Index++) {
        Dict->Table[Index] = NULL;
    }
    return Dict;
}

Pair* Create_Pair(void* Key, Type KeyType, void* Value, Type ValueType) {
    Pair* NewPair = (Pair*) malloc(sizeof(Pair));
    if (NewPair == NULL) {
        puts("New Pair Allocation Fail");
        exit(EXIT_FAILURE);
    }
    NewPair->Key = Key;
    NewPair->KeyType = KeyType;
    NewPair->Value = Value;
    NewPair->ValueType = ValueType;
    NewPair->Next = NULL;
    Pair_Pointer_Check(NewPair, "New Pair Allocation Fail");
    return NewPair;
}

void Insert(Dictionary* Dict, void* Key, Type KeyType, void* Value, Type ValueType) {
    unsigned int Index = Hash(Key, Dict->Size);
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

        Dict->InnerDepth = Depth + 1;

        if (Dict->InnerDepth >= 5) {
            printf("Warning: High collision depth (%d) detected at index %u.\n", Dict->InnerDepth, Index);
        }
    }
}

Any* Lookup(Dictionary* Dict, void* Key) {
    unsigned int Index = Hash((char*) Key, Dict->Size);
    if (Dict->Table[Index] != NULL){
        Pair* Current = Dict->Table[Index];
        while (Current != NULL) {
            if (Current->KeyType == STRING){
                if (strcmp((char*) Current->Key, (char *) Key) == 0) {
                    Any* FoundValue = (Any*) malloc(sizeof(Any));
                    if (FoundValue != NULL) {
                        FoundValue->Value = Current->Value;
                        FoundValue->ValueType = Current->ValueType;
                        return FoundValue;
                    }
                }
            }
            Current = Current->Next;
        }
    }
    return NULL;
}

void Free_Dictionary(Dictionary* Dict) {
    if (Dict == NULL) return;
    
    for (int Iteration = 0; Iteration < Dict->Size; Iteration++) {
        if (Dict->Table[Iteration] != NULL){
            Pair* Current = Dict->Table[Iteration];
            while (Current != NULL) {
                if (Current->Key != NULL){
                    free(Current->Key);
                }
                // Do not free DECLARATIONS, as they are the pointers to use the built-in functions
                if (Current->ValueType != DECLARATION && Current->Value != NULL){
                    free(Current->Value);
                }
                Pair* Next = Current->Next;
                free(Current);
                Current = Next;  
            }
        }
    }
    free(Dict->Table);
    free(Dict);
}