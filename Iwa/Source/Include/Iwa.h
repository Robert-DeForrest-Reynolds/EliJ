#ifndef IWA_H
#define IWA_H

#include <stdbool.h>
#include "Structures.h"

char* ArgumentBufferPointer;
char* FileNamePointer;
char WorkingDirectory[1024 * 1024]; // 1MB
char* FinalWorkingDirectory;
StringList* SourceCode;
StringList* Instructions;

#endif