#include <stdio.h.>
#include <string.h>
#include "Structures.h"

void Output(Any* Pointer){
    switch (Pointer->ValueType){
        case STRING:
            fwrite((char*) Pointer->Value, sizeof(char), strlen((char*) Pointer->Value), stdout);
            break;
        case FUNCTION: {
            Function* Func = (Function* ) Pointer->Value;
            printf("%s\n", Func->FunctionName);
            break;
        }
        default:
            puts("Unknown ValueType\n");
            break;
    }
}