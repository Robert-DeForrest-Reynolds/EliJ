#include <stdio.h>
#include <string.h>


FILE *SourceFilePointer;
char ReadBuffer[2560];


void Read_Source_File(char *Argument){
    printf("Reading Source File: %s\n", Argument);
    SourceFilePointer = fopen(Argument, "r");
    if (SourceFilePointer != NULL)
    {
        while (fgets(ReadBuffer, sizeof(ReadBuffer), SourceFilePointer))
        {
            printf("%s", ReadBuffer);
        }
        printf("\n\n");
    } else {
        printf("There was a problem opening your source file.");
    }
    fclose(SourceFilePointer);
}


void Print_Arguments(int ArgumentCount, char *Arguments[]){
    printf("Passed arguments:\n");
    char PassedArguments[256] = "";
    for (int i = 0; i < ArgumentCount; i++){
        if (strcmp(Arguments[i], "./Main") != 0)
        {
            char FormattedString[256] = "";
            strcat(FormattedString, Arguments[i]);
            strcat(FormattedString, " ");
            strcat(PassedArguments, FormattedString);
        }
    }
    printf("%s\n\n", PassedArguments);
}


void Analyze_Arguments(int ArgumentCount, char *Arguments[]){
    if (ArgumentCount >= 2){
        Read_Source_File(Arguments[1]);
    } else {
        printf("You did not give a source file.\n");
    }
}


int main(int ArgumentCount, char *Arguments[]){
    printf("Smile away, we're alive today.\n");
    Print_Arguments(ArgumentCount, Arguments);
    Analyze_Arguments(ArgumentCount, Arguments);
    return 0;
}