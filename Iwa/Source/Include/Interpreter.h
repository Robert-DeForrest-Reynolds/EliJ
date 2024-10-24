#ifndef INTERPRETER_H
#define INTERPRETER_H

char* File_Name_Check(char* PotentialFileName, int ArgumentLength, int WorkingDirectoryLength);
StringList* Parse_Source_Code(char* FileName);
void Execute_Instructions(StringList* Instructions);

#endif