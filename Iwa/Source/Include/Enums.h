#ifndef ENUMS_H
#define ENUMS_H

typedef enum {
    CHAR,
    STRING,
    INT,
    FLOAT,
    DICTIONARY,
    ANY,
    FUNCTION,
} Type;

extern char* TypesAsStrings[];

#endif