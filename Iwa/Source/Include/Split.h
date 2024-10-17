#ifndef SPLIT_H
#define SPLIT_H

typedef struct SplitResult{
    bool Successful;
    char** Result;
} SplitResult;

SplitResult* Split(char* String, char SplitCharacter);

#endif