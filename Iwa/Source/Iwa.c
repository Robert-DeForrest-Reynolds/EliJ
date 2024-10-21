#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "Iwa.h"
#include "ReadFile.h"
#include "ReadFileLines.h"
#include "Contains.h"
#include "PointerChecks.h"
#include "Replace.h"
#include "Structures.h"

void File_Name_Check(int ArgumentIndex, int ArgumentLength){
    bool IsFileName = Contains(ArgumentBufferPointer, ".");
    if (ArgumentIndex == 1 && IsFileName == true){
        FileNamePointer = malloc((strlen(WorkingDirectory) + ArgumentLength) * sizeof(char));
        String_Pointer_Check(FileNamePointer, "File Name Pointer Allocation Fail");
        strcpy(FileNamePointer, ArgumentBufferPointer);
    }
}

StringList* Parse_Source_Code(char* FileName){
    printf("Trying to read source file %s\n", FileName);
    FILE* FilePointer = fopen(FileName, "r");
    File_Pointer_Check(FilePointer, "Read File Pointer Allocation Fail");

    int LineBufferSize = 1024;

    int LineCount = 0;
    char* LineBuffer = malloc(LineBufferSize * sizeof(char));

    fseek(FilePointer, 0, SEEK_END);
    long FileSize = ftell(FilePointer);
    rewind(FilePointer);

    while (fgets(LineBuffer, LineBufferSize, FilePointer)){
        LineCount += 1;
    }

    StringList* Contents = (StringList* )malloc((LineCount + 1) * sizeof(char*));
    Contents->List = malloc((LineCount + 1) * sizeof(char*));
    StringList_Pointer_Check(Contents, "Read File Contents Pointer Allocation Fail");
    for (int LineIndex = 0; LineIndex < LineCount; LineIndex++){
        Contents->List[LineIndex] = malloc((LineBufferSize + 1) * sizeof(char));
        String_Pointer_Check(Contents->List[LineIndex], "Read File Lines Inner String Allocation Fail");
    }

    LineCount = 0;
    rewind(FilePointer);
    while (fgets(LineBuffer, LineBufferSize, FilePointer)){
        strcpy(Contents->List[LineCount], LineBuffer);
        LineCount += 1;
    }

    free(LineBuffer);
    fclose(FilePointer);

    Contents->List[LineCount] = NULL;
    Contents->ElementCount = LineCount;
    return Contents;
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
        size_t FinalFileNameLength = strlen(FinalWorkingDirectory) + strlen(FileNamePointer) + 2;
        char* FinalFileName = malloc(FinalFileNameLength + 1 * sizeof(char));
        strcpy(FinalFileName, FinalWorkingDirectory);
        strcat(FinalFileName, FileNamePointer);
        SourceCode = Parse_Source_Code(FinalFileName);
    } else {
        SourceCode = Parse_Source_Code(FileNamePointer);
    }

    Output(SourceCode, 0);
    for (int Iteration = 0; Iteration < SourceCode->ElementCount; Iteration++){
        printf("%s", SourceCode->List[Iteration]);
    }

    free(SourceCode);
    free(FileNamePointer);
    return 0;
}
