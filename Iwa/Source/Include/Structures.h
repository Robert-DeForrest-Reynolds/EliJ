#ifndef STRUCTURES_H
#define STRUCTURES_H

#include "Enums.h"

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

typedef struct VariableDeclaration{
    Pair* (*Function)(char* VariableName, char* VariableValue, Type VariableValueType);
    char* FunctionName;
} VariableDeclaration;

typedef struct OutputFunction{
    void (*Function)();
    char* FunctionName;
} OutputFunction;

typedef struct InputFunction{
    StringList* (*Function)();
    char* FunctionName;
} InputFunction;

#endif