#ifndef ENUMS_H
#define ENUMS_H

#include "Structures.h"

typedef struct Dictionary Dictionary;

typedef enum{
    FIND_BETWEEN,
} FunctionType;

typedef enum{
    CHAR,
    STRING,
    INT,
    FLOAT,
    DICTIONARY,
    ANY,
    FUNCTION,
    DECLARATION,
    ASSIGNMENT,
    TYPE,
    OUTPUT,
    INPUT,
    STRING_RTN,
    BOOL,
    MULTILINE,
} Type;

extern char* TypesAsStrings[];
extern Dictionary* InternalTypeMap;

#endif