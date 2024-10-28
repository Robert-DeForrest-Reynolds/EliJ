#ifndef INTERPRETER_H
#define INTERPRETER_H

char* File_Name_Check(char* PotentialFileName, int ArgumentLength, int WorkingDirectoryLength);
StringList* Parse_Source_Code(char* FileName);
void Run_Interpreter(StringList* Instructions);
Pair* Variable_Declaration(char* VariableName, char* VariableValue, Type VariableValueType);

#endif