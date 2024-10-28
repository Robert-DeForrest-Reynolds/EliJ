#include <stdio.h.>
#include <string.h>
#include "Structures.h"
#include "PointerChecks.h"

void Output(Any* Pointer){
    switch (Pointer->ValueType){
        case STRING:
            printf("%s\n", (char*) Pointer->Value);
            break;
        case INT:{
            int Value = *(int*) Pointer->Value;
            printf("%d\n", Value);
            break;
        }
        case FUNCTION: {
            // Function* Func = (Function* ) Pointer->Value;
            // Function_Pointer_Check(Func, "Output Function Pointer Allocation Fail");
            // printf("%s\n", Func->FunctionName);
            break;
        }
        default:
            puts("Unknown ValueType when searching for output type\n");
            break;
    }
}