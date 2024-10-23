#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Structures.h"
#include "Contains.h"
#include "PointerChecks.h"

void File_Name_Check(char* FileNamePointer, char* PotentialFileName, int ArgumentLength, int WorkingDirectoryLength){
    bool IsFileName = Contains(PotentialFileName, ".");
    if (IsFileName == true){
        FileNamePointer = malloc((WorkingDirectoryLength + ArgumentLength) * sizeof(char));
        String_Pointer_Check(FileNamePointer, "File Name Pointer Allocation Fail");
        strcpy(FileNamePointer, PotentialFileName);
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