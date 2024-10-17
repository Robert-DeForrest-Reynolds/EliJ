#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "PointerChecks.h"
#include "Split.h"

char* ArgumentBufferPointer;
char* FileNamePointer;

void Parse_User_Arguments(int ArgumentsCount, char* Arguments[]){
    for (int Iteration = 0; Iteration < ArgumentsCount; Iteration++) {
        size_t ArgumentLength = strlen(Arguments[Iteration]) + 3;
        if (ArgumentLength > 256) { return; } // Abort program if an argument is greater 256, this needs to handled more gracefully
        snprintf(ArgumentBufferPointer, ArgumentLength, "%s \n", Arguments[Iteration]);
        fwrite(ArgumentBufferPointer, sizeof(char), strlen(ArgumentBufferPointer), stdout);
        char SplitChar = '.';
        char** CharSplit = Split(ArgumentBufferPointer, SplitChar);
        if (CharSplit[0] != (NULL)){
            printf("Splitting: %s", ArgumentBufferPointer);
            for (int Iteration = 0; CharSplit[Iteration] != NULL; Iteration++) {
                printf("%s\n", CharSplit[Iteration]);
            }
        }
        free(CharSplit);
    }
    free(ArgumentBufferPointer);
}

int main(int ArgumentsCount, char* Arguments[]) {
    ArgumentBufferPointer = malloc(256 * sizeof(char));
    FileNamePointer = malloc(256 * sizeof(char));
    String_Pointer_Check(ArgumentBufferPointer, "ArgumentBuffer");
    Parse_User_Arguments(ArgumentsCount, Arguments);
    free(FileNamePointer);
    return 0;
}
