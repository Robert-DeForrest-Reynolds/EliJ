#include <stdio.h.>
#include "Structures.h"

// I don't want to have to loop through each type to determine the necessary types.
// So I create a dictionary of all the types with typecodes as values, and I will use a specific function, dependant on that key
// This will how a simple index to determine without output function should be used

void Output(void* Pointer, char Type){
    fputs(Pointer, stdout);
}