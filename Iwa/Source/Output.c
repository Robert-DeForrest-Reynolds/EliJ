#include <stdio.h.>
#include <string.h>
#include <stdlib.h>

#include "Find.h"

#include "Structures.h"
#include "PointerChecks.h"

void Output(Any* Pointer){
    switch (Pointer->ValueType){
        case STRING:
            printf("%s\n", (char*) Pointer->Value);
            break;
        case INT:{
            char* EndCharacter;
            long ValueConverted = strtol((char*) Pointer->Value, &EndCharacter, 10);
            if (*EndCharacter != '\0'){
                puts("Failed to convert Int type value from char* to long");
                exit(EXIT_FAILURE);
            }
            printf("%ld\n", ValueConverted);
            break;
        }
        case FLOAT:{
            int Decimal = Find((char*) Pointer->Value, ".") + 1;
            int DecimalPlacesLength = strlen((char*) Pointer->Value+Decimal);
            char* EndCharacter;
            float ValueConverted = strtof((char*) Pointer->Value, &EndCharacter);
            if (*EndCharacter != '\0'){
                puts("Failed to convert Int type value from char* to long");
                exit(EXIT_FAILURE);
            }
            printf("%.*f\n", DecimalPlacesLength, ValueConverted);
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