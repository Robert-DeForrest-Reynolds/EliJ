#ifndef EXPRESSIONS_H
#define EXPRESSIONS_H

#include <stdbool.h>

long Solve_Addition(long OperandOne, long OperandTwo);
long Solve_Multiplication(long OperandOne, long OperandTwo);
char* Resolve_Expression(char* Expression, int ExpressionLength, bool Recursive);

#endif