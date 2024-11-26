#ifndef GLOBALS_H
#define GLOBALS_H


extern Dictionary* Globals;
extern Dictionary* ValidOperators;
extern char* ArgumentBuffer;
extern char* FileName;
extern char WorkingDirectory[1024 * 1024]; // 1MB
extern int WorkingDirectoryLength;
extern char* FinalWorkingDirectory;
extern StringList* Instructions;
extern int SAFE_LONG_LENGTH;


#endif