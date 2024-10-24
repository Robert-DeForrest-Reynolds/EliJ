#ifndef STRUCTURES_H
#define STRUCTURES_H

#include "Enums.h"

typedef struct Function{
    void* Function;
    char* FunctionName;
} Function;

typedef struct Any {
    void* Value;
    Type ValueType;
} Any;

typedef struct Pair {
    void* Key;
    Type KeyType;
    void* Value;
    Type ValueType;
    struct Pair* Next;  // Pointer for handling collisions (linked list)
} Pair;

typedef struct Dictionary {
    Pair** Table;
    int Filled;
    int Size;
    int* InnerDepth;  // Keeps track of collision depths for each index
} Dictionary;

typedef struct StringList{
    char** List;
    int ElementCount;
} StringList;

#endif