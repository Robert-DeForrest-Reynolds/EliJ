#ifndef STRUCTURES_H
#define STRUCTURES_H

typedef struct Pair {
    void* Key;
    char* KeyType;
    void* Value;
    char* ValueType;
    struct Pair* Next;  // Pointer for handling collisions (linked list)
} Pair;

typedef struct Dictionary {
    Pair** Table;
    int Size;
    int* InnerDepth;  // Keeps track of collision depths for each index
} Dictionary;

typedef struct StringList{
    char** List;
    int ElementCount;
} StringList;

#endif