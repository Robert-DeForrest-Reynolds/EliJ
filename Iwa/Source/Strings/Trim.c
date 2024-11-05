#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* Trim(char* Line){
    int LeftCharacter;
    int RightCharacter;
    int TrimmedLineLength;
    int LineLength = strlen(Line);
    for (int Index = 0; Index < LineLength; Index++){
        if (Line[Index] != ' '){
            LeftCharacter = Index;
            break;
        }
    }
    for (int Index = LineLength-1; Index >= 0; Index--){
        if (Line[Index] != ' '){
            RightCharacter = Index;
            break;
        }
    }
    if (RightCharacter == 0){
        RightCharacter = LineLength;
    }

    TrimmedLineLength = RightCharacter - LeftCharacter + 1;
    char* TrimmedLine = malloc((TrimmedLineLength + 1) * sizeof(char));
    TrimmedLine[TrimmedLineLength] = '\0';
    strncpy(TrimmedLine, Line+LeftCharacter, TrimmedLineLength);
    return TrimmedLine;
}