#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "Iwa.h"
#include "ReadFile.h"
#include "Contains.h"
#include "PointerChecks.h"
#include "Replace.h"

void File_Name_Check(int ArgumentIndex, int ArgumentLength){
    bool IsFileName = Contains(ArgumentBufferPointer, ".");
    if (ArgumentIndex == 1 && IsFileName == true){
        FileNamePointer = malloc((strlen(WorkingDirectory) + ArgumentLength) * sizeof(char));
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

    if (Contains(FileNamePointer, "\\")){
        FileNamePointer = Replace(FileNamePointer, "\\", "/");
        puts(FileNamePointer);
        FinalWorkingDirectory = Replace(WorkingDirectory, "\\", "/");
    }
    else{
        FinalWorkingDirectory = NULL;
    }

    if (FinalWorkingDirectory != NULL){
        size_t FinalFileNameLength = strlen(FinalWorkingDirectory) + strlen(FileNamePointer) + 2;
        char* FinalFileName = malloc(FinalFileNameLength + 1 * sizeof(char));
        strcpy(FinalFileName, FinalWorkingDirectory);
        strcat(FinalFileName, FileNamePointer);
        SourceCode = Read_File(FinalFileName);
    } else {
        SourceCode = Read_File(FileNamePointer);
    }

    if (SourceCode) {
        puts(SourceCode);
        free(SourceCode);
    }

    free(FileNamePointer);
    return 0;
}
