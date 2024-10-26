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

    StringList* Contents = (StringList*) malloc(sizeof(StringList));
    StringList_Pointer_Check(Contents, "Read File Contents Pointer Allocation Fail");
    Contents->List = malloc(sizeof(char*) * (LineBufferSize));
    Contents->ElementCount = 0;

    char* LineBuffer = malloc(LineBufferSize * sizeof(char));
    if (LineBuffer == NULL) {
        free(Contents);
        fclose(FilePointer);
        perror("Line buffer allocation failed");
        return NULL;
    }

    while (fgets(LineBuffer, LineBufferSize, FilePointer)) {
        Contents->List[Contents->ElementCount] = malloc((strlen(LineBuffer) + 1) * sizeof(char));
        String_Pointer_Check(Contents->List[Contents->ElementCount], "Read File Lines Inner String Allocation Fail");
        strcpy(Contents->List[Contents->ElementCount], LineBuffer);
        Contents->ElementCount++;
        
        if (Contents->ElementCount % LineBufferSize == 0) {
            Contents->List = realloc(Contents->List, sizeof(char*) * (Contents->ElementCount + LineBufferSize));
            if (Contents->List == NULL) {
                free(LineBuffer);
                free(Contents);
                perror("Reallocation of contents list failed");
                return NULL;
            }
        }
    }

    free(LineBuffer);
    fclose(FilePointer);

    Contents->List[Contents->ElementCount] = NULL;

    return Contents;
}
