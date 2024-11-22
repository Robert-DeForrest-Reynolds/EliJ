#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int Find_From_End(char* String, char* Query){
    int StringLength = strlen(String);
    int QueryLength = strlen(Query);

    if (QueryLength == 0 || QueryLength > StringLength) {
        return -1;
    }

    for (int Index = StringLength - QueryLength; Index >= 0; Index--) {
        if (strncmp(String + Index, Query, QueryLength) == 0) {
            return Index;
        }
    }

    return -1;
}