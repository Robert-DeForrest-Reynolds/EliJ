#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "Structures.h"
#include "PointerChecks.h"

char* Input(char* Prefix){
    printf("Calling input function\n");
    char UserInput[1024];
    printf("%s", Prefix);
    if (fgets(UserInput, sizeof(UserInput), stdin) == NULL) {
        printf("User Input Exceeded Limit");
    }
    int UserInputLength = strlen(UserInput);
    char* ReturnString = malloc((UserInputLength + 1) * sizeof(char));
    String_Pointer_Check(ReturnString, "Input Return String Allocation Fail");
    ReturnString[UserInputLength] = '\0';
    strcpy(ReturnString, UserInput);
    printf("%s\n", ReturnString);
    return ReturnString;
}