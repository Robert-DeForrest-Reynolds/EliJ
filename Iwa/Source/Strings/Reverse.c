#include "string.h"
#include "stdlib.h"
#include "PointerChecks.h"

char* Reverse(char* String){
    int StringLength = strlen(String);
    char* ReversedString = malloc((StringLength + 1) * sizeof(char));
    String_Pointer_Check(ReversedString, "Reversed String Allocation Fail");
    ReversedString[StringLength] = '\0';
    int Start = 0;
    int End = StringLength - 1;

    if (String[End] == '\n'){
        End--;
    }

    // I willfully choose not to XOR this
    while (Start < End){
        ReversedString[Start] = String[End];
        ReversedString[End] = String[Start];
        Start++;
        End--;
    }
    if (StringLength % 2 == 1) {
        ReversedString[Start] = String[Start];
    }

    return ReversedString;
}