#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <stdbool.h>
#include "Structures.h"

void Variable_Declaration(char* VariableName, char* VariableValue, Type VariableValueType);
char** Find_Declaration_Values(Type VariableType, char* UnparsedValues, char* Instruction, int LineNumber);
Any* Execute_Statement(char* Instruction, char* KeywordBuffer, Any* InstructionKeyword, int InstructionLength, int CharacterIndex, int LineNumber);
Any* Evaluate_Instruction(char* Instruction, int LineNumber);
void Setup_Internal_Types(void);
void Setup_Globals(void);
void Run_Interpreter(void);
void Check_Windows_Style_Path(void);
void Verify_Valid_Papple_File(char* PotentialFileName, int ArgumentLength, int WorkingDirectoryLength);
void Parse_User_Arguments(int ArgumentsCount, char* Arguments[]);
char* Resolve_Expression(char* Expression, int ExpressionLength, bool Recursive);

#endif