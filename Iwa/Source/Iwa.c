#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "Iwa.h"
#include "ReadFile.h"
#include "Contains.h"
#include "PointerChecks.h"

void File_Name_Check(int ArgumentIndex, int ArgumentLength){
    if (ArgumentIndex == 1 && Contains(ArgumentBufferPointer, ".")){
        FileNamePointer = malloc((sizeof(WorkingDirectory) + ArgumentLength) * sizeof(char));
        String_Pointer_Check(FileNamePointer, "File Name Pointer Allocation Fail");
        strcpy(FileNamePointer, ArgumentBufferPointer);
    }
}

void Parse_User_Arguments(int ArgumentsCount, char* Arguments[]){
    for (int Iteration = 1; Iteration < ArgumentsCount; Iteration++) {
        size_t ArgumentLength = strlen(Arguments[Iteration]) + 3;
        ArgumentBufferPointer = malloc(ArgumentLength * sizeof(char));
        String_Pointer_Check(ArgumentBufferPointer, "ArgumentBuffer");
        snprintf(ArgumentBufferPointer, ArgumentLength, "%s", Arguments[Iteration]);
        File_Name_Check(Iteration, ArgumentLength);
        free(ArgumentBufferPointer);
    }
}

int main(int ArgumentsCount, char* Arguments[]) {
    if (getcwd(WorkingDirectory, sizeof(WorkingDirectory)) == NULL) {
        perror("Failed to obtain current working directory.");
        return EXIT_FAILURE;
    }

    Parse_User_Arguments(ArgumentsCount, Arguments);
    
    size_t FinalFileNameLength = strlen(WorkingDirectory) + strlen(FileNamePointer) + 2;
    char* FinalFileName = malloc(FinalFileNameLength * sizeof(char));
    String_Pointer_Check(FinalFileName, "Final File Name Pointer Allocation Fail");
    strcpy(FinalFileName, WorkingDirectory);
    strcat(FinalFileName, FileNamePointer);

    char* SourceCode = Read_File(FinalFileName);
    if (SourceCode) {
        puts(SourceCode);
        free(SourceCode);
    } else {
        fprintf(stderr, "Failed to read the file: %s\n", FinalFileName);
    }

    free(FileNamePointer);
    return 0;
}
