
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

#include "Contains.h"
#include "Count.h"
#include "Dictionary.h"
#include "Expressions.h"
#include "Find.h"
#include "FindBetween.h"
#include "FindFromEnd.h"
#include "Hash.h"
#include "Input.h"
#include "LeftTrim.h"
#include "Output.h"
#include "ReadFile.h"
#include "ReadFileLines.h"
#include "Remove.h"
#include "Replace.h"
#include "Reverse.h"
#include "Split.h"
#include "Trim.h"

#include "Enums.h"
#include "Interpreter.h"
#include "PointerChecks.h"
#include "Structures.h"
#include "Globals.h"
#include "Setup.h"
#include "Error.h"

void Run_Iwa(int ArgumentsCount, char* Arguments[]){
    Setup_Globals();
    Setup_Internal_Types();

    Parse_User_Arguments(ArgumentsCount, Arguments);

    Setup_Working_Directory();
    Check_Windows_Style_Path();

    Run_Interpreter();
    free(FileName);

    Free_Dictionary(Globals);
    Free_Dictionary(InternalTypeMap);
}


int main(int ArgumentsCount, char* Arguments[]) {
    Run_Iwa(ArgumentsCount, Arguments);
    return 0;
}
