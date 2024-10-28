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
    
    Dict->InnerDepth = (int*) calloc(Size, sizeof(int));
    if (Dict->InnerDepth == NULL) {
        free(Dict->Table);
        free(Dict);
        return NULL;
    }
    
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
    printf("Inserting Key: %s\n", (char*) Key);
    unsigned int Index = Hash(Key, Dict->Size);
    printf("Hash Value: %u\n", Index);
    Pair* NewPair = Create_Pair(Key, KeyType, Value, ValueType);
    printf("Created Pair\n");
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
            printf("Warning: High collision depth (%d) detected at index %u.\n", Dict->InnerDepth[Index], Index);
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
                if (FoundValue != NULL) {
                    FoundValue->Value = Current->Value;
                    FoundValue->ValueType = Current->ValueType;
                    return FoundValue;
                }
            }
        }
        Current = Current->Next;
    }
    return NULL;
}

void Free_Dictionary(Dictionary* Dict) {
    if (Dict == NULL) return;
    
    for (int Iteration = 0; Iteration < Dict->Size; Iteration++) {
        Pair* Current = Dict->Table[Iteration];
        while (Current != NULL) {
            Pair* Next = Current->Next;
            // Free string keys if they were dynamically allocated
            if (Current->KeyType == STRING) {
                free(Current->Key);
            }
            // Free string values if they were dynamically allocated
            if (Current->ValueType == STRING) {
                free(Current->Value);
            }
            free(Current);
            Current = Next;
        }
    }
    free(Dict->Table);
    free(Dict->InnerDepth);
    free(Dict);
}