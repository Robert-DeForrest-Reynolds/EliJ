#include <string.h>
#include "stdbool.h"

bool Contains(char * String, char * Query){
    int StringLength = strlen(String);
    int QueryLength = strlen(Query);
    if (QueryLength > StringLength) { return false; }
    for (int Iteration = 0; Iteration <= StringLength - QueryLength; Iteration++) {
        if (strncmp(&String[Iteration], Query, QueryLength) == 0) { return true; }
    }
    return false;
}