#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "Structures.h"
#include "PointerChecks.h"

// This eventually needs to be dynamic and read userinput char by char until eof

char* Input(char* Prefix){
    char UserInput[1024];
    printf("%s", Prefix);
    if (fgets(UserInput, sizeof(UserInput), stdin) == NULL) {
        printf("User Input Exceeded Limit");
    }
    int UserInputLength = strlen(UserInput);
    int ReturnStringLength = UserInputLength + 1; // 1 extra for " at beginning
    char* ReturnString = malloc((ReturnStringLength) + 1 * sizeof(char)); // 1 extra space for null terminator
    String_Pointer_Check(ReturnString, "Input Return String Allocation Fail");
    strcpy(ReturnString+1, UserInput);
    ReturnString[0] = '"';
    ReturnString[ReturnStringLength - 1] = '"';
    ReturnString[ReturnStringLength] = '\0';
    return ReturnString;
}