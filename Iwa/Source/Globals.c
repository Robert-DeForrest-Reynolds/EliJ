#include "Structures.h"

Dictionary* Globals;
Dictionary* ValidOperators;
char* ArgumentBuffer;
char* FileName;
char WorkingDirectory[1024 * 1024]; // 1MB
int WorkingDirectoryLength;
char* FinalWorkingDirectory;
StringList* Instructions;
int SAFE_LONG_LENGTH = 20;