#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Find.h"
#include "PointerChecks.h"
#include "FindFromEnd.h"

// This function needs to take into account if left query and right query are not on the ends of the string
// For example FindBetweenTest = Find_Between(Greeting, "(", ")") needs to get Greeting, "(", ")" if LeftQuery="("  , and RightQuery=")"
char* Find_Between(char* String, char* LeftQuery, char* RightQuery){
    int StringLength = strlen(String);
    int LeftQueryLength = strlen(LeftQuery);
    int IndexOfLeftBounds = Find(String, LeftQuery);
    int IndexOfRightBounds = Find_From_End(String, RightQuery);
    if (IndexOfLeftBounds != -1 && IndexOfRightBounds != -1){
        IndexOfLeftBounds += LeftQueryLength;
        int LengthOfFoundString = IndexOfRightBounds - IndexOfLeftBounds;
        char* FoundString = malloc((LengthOfFoundString + 1) * sizeof(char));
        String_Pointer_Check(FoundString, "Find Between Substring Allocation Fail");
        FoundString[LengthOfFoundString] = '\0';
        strncpy(FoundString, String + IndexOfLeftBounds, LengthOfFoundString);
        return FoundString;
    }
    return NULL;
}