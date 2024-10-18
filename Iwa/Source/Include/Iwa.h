#ifndef IWA_H
#define IWA_H
#include <stdbool.h>

char* SourceCode;
char* ArgumentBufferPointer;
char* FileNamePointer;
char WorkingDirectory[1024 * 1024]; // 1MB
char* FinalWorkingDirectory;

#endif