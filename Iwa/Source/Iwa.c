#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "PointerChecks.h"
#include "Split.h"
#include "Contains.h"

char* ArgumentBufferPointer;
char* FileNamePointer;

void File_Name_Check(int Iteration, int ArgumentLength){
    if (Iteration == 1 && Contains(ArgumentBufferPointer, ".")){
        FileNamePointer = malloc(ArgumentLength * sizeof(char));
        strcpy(FileNamePointer, ArgumentBufferPointer);
    }
}

void Parse_User_Arguments(int ArgumentsCount, char* Arguments[]){
    ArgumentBufferPointer = malloc(256 * sizeof(char));
    String_Pointer_Check(ArgumentBufferPointer, "ArgumentBuffer");
    for (int Iteration = 1; Iteration < ArgumentsCount; Iteration++) {
        size_t ArgumentLength = strlen(Arguments[Iteration]) + 3;
        if (ArgumentLength > 256) { return; } // Abort program if an argument is greater 256, this needs to handled more gracefully
        snprintf(ArgumentBufferPointer, ArgumentLength, "%s \n", Arguments[Iteration]);
        fwrite(ArgumentBufferPointer, sizeof(char), strlen(ArgumentBufferPointer), stdout);
        File_Name_Check(Iteration, ArgumentLength);
    }
    free(ArgumentBufferPointer);
}

int main(int ArgumentsCount, char* Arguments[]) {
    Parse_User_Arguments(ArgumentsCount, Arguments);
    if (FileNamePointer){
        puts("\nObtained a file name:");
        puts(FileNamePointer);
    }
    return 0;
}
