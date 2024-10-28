#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Find.h"
#include "PointerChecks.h"

char* Find_Between(char* String, char* BoundingCharacter){
    int StringLength = strlen(String);
    int IndexOfLeftBounds = Find(String, BoundingCharacter);
    int IndexOfRightBounds;
    if (IndexOfLeftBounds != -1){
        int BufferLength = StringLength - (IndexOfLeftBounds+1);
        char* Buffer = malloc((BufferLength + 1) * sizeof(char));
        String_Pointer_Check(Buffer, "Buffer for Find Between Allocation Fail");
        Buffer[BufferLength] = '\0';
        strncpy(Buffer, String + (IndexOfLeftBounds+1), BufferLength);
        IndexOfRightBounds = Find(Buffer, BoundingCharacter) + (IndexOfLeftBounds+1);
        free(Buffer);
    }
    if (IndexOfRightBounds != -1){
        int LengthOfFoundString = StringLength - strlen(BoundingCharacter) * 2;
        char* FoundString = malloc(LengthOfFoundString + 1 * sizeof(char));
        String_Pointer_Check(FoundString, "Find Between Substring Allocation Fail");
        FoundString[LengthOfFoundString] = '\0';
        strncpy(FoundString, String + (IndexOfLeftBounds+1), IndexOfRightBounds - (StringLength-IndexOfRightBounds));
        return FoundString;
    }
    return NULL;
}