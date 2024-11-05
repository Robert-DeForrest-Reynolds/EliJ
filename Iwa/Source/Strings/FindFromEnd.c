#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int Find_From_End(char* String, char* Query){
    int StringLength = strlen(String);
    int QueryLength = strlen(Query);
    for (int Index = StringLength; Index >= 0; Index--){
        if (Index + QueryLength > StringLength) { continue; } // Skip first end character if query length exceeds window
        char* Window = malloc((QueryLength + 1) * sizeof(char));
        Window[QueryLength] = '\0';
        strncpy(Window, String+(Index), QueryLength);
        return Index;
    }
    return -1;
}