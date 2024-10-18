#include <stdio.h>
#include <stdlib.h>
#include "PointerChecks.h"

char* Read_File(char* FileName){
    FILE* FilePointer = fopen(FileName, "r");
    File_Pointer_Check(FilePointer, "Read File Pointer Allocation Fail");

    fseek(FilePointer, 0, SEEK_END);
    long FileSize = ftell(FilePointer);
    rewind(FilePointer);

    char* Contents = malloc((FileSize + 1) * sizeof(char));
    String_Pointer_Check(Contents, "Read File Contents Pointer Allocation Fail");

    size_t BytesRead = fread(Contents, sizeof(char), FileSize, FilePointer);

    Contents[BytesRead] = '\0';

    fclose(FilePointer);
    return Contents;
}