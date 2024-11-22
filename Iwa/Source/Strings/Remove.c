#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Count.h"

char* Remove(char* String, char* RemoveCharacter){
    int StringLength = strlen(String);
    int RemoveCharacterLength = strlen(RemoveCharacter);
    int RemovalAmount = Count(String, " ");
    int ProcessedStringLength = StringLength - RemovalAmount;
    int ProcessedCharactersAmount = 0;
    char* ProcessedString = malloc((ProcessedStringLength + 1) * sizeof(char));
    for (int Index = 0; Index < StringLength; Index++){
        if (strncmp(String+Index, RemoveCharacter, RemoveCharacterLength) == 1){
            ProcessedString[ProcessedCharactersAmount] = String[Index];
            ProcessedCharactersAmount++;
        }
    }
    ProcessedString[ProcessedStringLength] = '\0';
    printf("Removed Amount: %d\n", RemovalAmount);
    printf("Processed String: %s\n", ProcessedString);
    return NULL;
}