#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Find.h"
#include "PointerChecks.h"

char* Find_Between(char* String, char* LeftQuery, char* RightQuery){
    int StringLength = strlen(String);
    int IndexOfLeftBounds = Find(String, LeftQuery);
    int IndexOfRightBounds = Find(String+IndexOfLeftBounds+1, RightQuery) + 1;
    if (IndexOfLeftBounds != -1 && IndexOfRightBounds != -1){
        IndexOfLeftBounds += 1;
        IndexOfRightBounds -= 1;
        int LengthOfFoundString = StringLength - strlen(LeftQuery) - strlen(RightQuery);
        char* FoundString = malloc(LengthOfFoundString + 1 * sizeof(char));
        String_Pointer_Check(FoundString, "Find Between Substring Allocation Fail");
        FoundString[LengthOfFoundString] = '\0';
        strncpy(FoundString, String + IndexOfLeftBounds, IndexOfRightBounds);
        return FoundString;
    }
    return NULL;
}