#ifndef SETUP_H
#define SETUP_H

void Setup_Internal_Types(void);
void Setup_Valid_Operators(void);
void Setup_Globals(void);
void Check_Windows_Style_Path(void);
void Verify_Valid_Papple_File(char* PotentialFileName, int ArgumentLength, int WorkingDirectoryLength);
void Parse_User_Arguments(int ArgumentsCount, char* Arguments[]);
void Setup_Working_Directory(void);

#endif