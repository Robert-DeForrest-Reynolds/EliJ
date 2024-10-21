#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "PointerChecks.h"
#include "Structures.h"

StringList* Read_File_Lines(char* FileName, int LineBufferSize){
    if (LineBufferSize <= 0) { LineBufferSize = 1024; }

    printf("Trying to read source file %s\n", FileName);
    FILE* FilePointer = fopen(FileName, "r");
    File_Pointer_Check(FilePointer, "Read File Pointer Allocation Fail");

    int LineCount = 0;
    char* LineBuffer = malloc(LineBufferSize * sizeof(char));

    fseek(FilePointer, 0, SEEK_END);
    long FileSize = ftell(FilePointer);
    rewind(FilePointer);

    while (fgets(LineBuffer, LineBufferSize, FilePointer)){
        LineCount += 1;
    }

    StringList* Contents = (StringList*) malloc(sizeof(StringList));
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