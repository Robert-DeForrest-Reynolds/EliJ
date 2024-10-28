#ifndef ENUMS_H
#define ENUMS_H

#include "Structures.h"

typedef struct Dictionary Dictionary;

typedef enum {
    CHAR,
    STRING,
    INT,
    FLOAT,
    DICTIONARY,
    ANY,
    FUNCTION,
    DECLARATION,
    TYPE,
} Type;

extern char* TypesAsStrings[];
extern Dictionary* InternalTypeMap;

#endif