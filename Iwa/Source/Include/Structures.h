#ifndef STRUCTURES_H
#define STRUCTURES_H

typedef struct Dictionary {
    char* Key;
    int Value;
} Dictionary;

typedef struct HashTable {
    Dictionary Dict;
    int Size;
} HashTable;

typedef struct StringList{
    char** List;
    int ElementCount;
} StringList;

#endif