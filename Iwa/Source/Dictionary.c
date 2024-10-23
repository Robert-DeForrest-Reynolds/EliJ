/*

A dictionary implementation for Pineapple

A HashTable holds:
    Pairs**;
    PairValues**;
    InnerDepth;
    CollisionCount;


A Pair holds:
    void* Key;
    char* KeyType;
    void* Value;
    char* valueType;

Linked lists to handle collisions at a depth of 5, as through a bit of rough testing that's the reliable
max to force the compiler to generate a jump table. We only check the collision count upon finding a
collision in the first place. If a collision depth of 5 is reached, we resort to expanding turning if the
linked list into an inner hash table. 

Keep account of recursion depth at each collision, and report copies to the user
If we have 2 or more collisions depths reached, we report to the user
We only check afterward we've found a collision at all
Ensure that hash recursion is checked against. If a collision is found, we need to start a counter of collisions, if the collision counter reaches 3
the program informs the user that the our hashing does not work for their intended implementation.
The user, and/or we as developers can deal with implementations to cover specified implementation detail for avoid these specified patterns that are dug up.

// If we collide with an existing value when adding a new value, we'll add a secondary variable to the hash formula to resolve a new position
// A has a collision count

*/
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

Pair* Create_Pair(void* Key, char* KeyType, void* Value, char* ValueType) {
    Pair* NewPair = (Pair*)malloc(sizeof(Pair));
    NewPair->Key = Key;
    NewPair->KeyType = KeyType;
    NewPair->Value = Value;
    NewPair->ValueType = ValueType;
    NewPair->Next = NULL;
    return NewPair;
}

void Insert(Dictionary* Dict, void* Key, char* KeyType, void* Value, char* ValueType) {
    unsigned int Index = Hash(Key, Dict->Size);
    Pair* NewPair = Create_Pair(Key, KeyType, Value, ValueType);

    if (Dict->Table[Index] == NULL) {
        Dict->Table[Index] = NewPair;
    } else {
        Pair* Current = Dict->Table[Index];
        int Depth = 0;

        if (Current->Next == NULL) {
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

char* Find(Dictionary* Dict, void* Key) {
    unsigned int Index = Hash(Key, Dict->Size);
    Pair* Current = Dict->Table[Index];

    while (Current != NULL) {
        if (Current->Key == Key) {
            return Current->Value;
        }
        Current = Current->Next;
    }
    return "Couldn't find anything";
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