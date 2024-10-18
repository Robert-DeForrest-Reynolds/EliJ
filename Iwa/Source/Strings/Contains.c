#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "PointerChecks.h"

bool Contains(char* String, char* Query){
    int StringLength = strlen(String);
    int QueryLength = strlen(Query);
    if (QueryLength > StringLength) { return false; }
    char* Slice = malloc(QueryLength + 1);
    for (int Iteration = 0; Iteration <= StringLength - QueryLength; Iteration++) {
        String_Pointer_Check(Slice, "Slice in Contains Allocation Fail");
        if (strncmp(&String[Iteration], Query, QueryLength) == 0) {
            free(Slice);
            return true;
        }
    }
    return false;
}