#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Count.h"
#include "PointerChecks.h"

char* Remove(char* String, char* RemoveCharacter){
    #if DEBUG
    printf("Removing \"%s\" from %s\n", RemoveCharacter, String);
    #endif
    int StringLength = strlen(String);
    int RemoveCharacterLength = strlen(RemoveCharacter);
    
    int RemovalAmount = Count(String, " ");
    
    int ProcessedStringLength = StringLength - RemovalAmount;
    char* ProcessedString = malloc((ProcessedStringLength + 1) * sizeof(char));
    String_Pointer_Check(ProcessedString, "ProcessedString during Remove() fail to allocate");
    ProcessedString[ProcessedStringLength] = '\0';
    
    int ProcessedCharactersAmount = 0;
    for (int Index = 0; Index < StringLength; Index++){
        if (strncmp(String+Index, RemoveCharacter, RemoveCharacterLength) == 1){
            ProcessedString[ProcessedCharactersAmount] = String[Index];
            ProcessedCharactersAmount++;
        }
    }

    return ProcessedString;
}


