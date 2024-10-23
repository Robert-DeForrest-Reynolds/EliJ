#ifndef INTERPRETER_H
#define INTERPRETER_H

void File_Name_Check(char* FileNamePointer, char* PotentialFileName, int ArgumentLength, int WorkingDirectoryLength);
StringList* Parse_Source_Code(char* FileName);

#endif