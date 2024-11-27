// I want a marking error
// Example
/*

Error: Variable does not exist.
String Name = FirstName + LastName
              ^^^^^^^^^

Error: Variable does not exist.
String Name = FirstName + LastName
              ^

Error: "FirstName" does not exist.
String Name = FirstName + LastName

*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "PointerChecks.h"

char* Create_Error_Message(char* Statement, char* SpecificError, int ErrorIndex, int ErrorMarkerLength){
    int ErrorPrefixLength = 7;
    int StatementLength = strlen(Statement);
    int SpecificErrorLength = strlen(SpecificError);
    int ErrorMessageLength = 7 + SpecificErrorLength + 1 + StatementLength + 1 + (ErrorIndex - 1) + ErrorMarkerLength + 1;
    char* ErrorMessage = (char*) malloc((ErrorMessageLength + 1) * sizeof(char));
    String_Pointer_Check(ErrorMessage, "Failed to allocate for error message\n");
    ErrorMessage[ErrorMessageLength] = '\0';

    strcpy(ErrorMessage, "Error: ");

    strcpy(ErrorMessage + ErrorPrefixLength, SpecificError);
    ErrorMessage[ErrorPrefixLength + SpecificErrorLength] = '\n';

    strcpy(ErrorMessage + ErrorPrefixLength + SpecificErrorLength + 1, Statement);
    ErrorMessage[ErrorPrefixLength + SpecificErrorLength + 1 + StatementLength] = '\n';

    int MarkerIndex = ErrorPrefixLength  + SpecificErrorLength + 1 + StatementLength + 1;

    for (int Index = 0; Index < ErrorIndex; Index++){
        ErrorMessage[MarkerIndex + Index] = ' ';
    }

    for (int Index = 0; Index < ErrorMarkerLength; Index++){
        ErrorMessage[MarkerIndex + ErrorIndex + Index] = '^';
    }

    return ErrorMessage;
}