#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Structures.h"
#include "Contains.h"
#include "PointerChecks.h"
#include "Dictionary.h"
#include "Enums.h"
#include "Output.h"

/*
We parse the source code into a list of all of the lines, that will then be parsed, and executed line by line
*/

char* File_Name_Check(char* PotentialFileName, int ArgumentLength, int WorkingDirectoryLength){
    bool IsFileName = Contains(PotentialFileName, ".");
    char* FileNamePointer = (char *) malloc((WorkingDirectoryLength + ArgumentLength) * sizeof(char));
    if (IsFileName == true){
        String_Pointer_Check(FileNamePointer, "File Name Pointer Allocation Fail");
        strcpy(FileNamePointer, PotentialFileName);
    }
    return FileNamePointer;
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

void Declare_String (){

}

void Execute_Instructions(StringList* Instructions){
    Dictionary* BuiltIns = Create_Dictionary(10);
    Function* StringDeclarations = malloc(sizeof(Function));
    StringDeclarations->Function = Declare_String;
    StringDeclarations->FunctionName = "Declare_String";
    Insert(BuiltIns, "StringDeclaration", STRING, StringDeclarations, FUNCTION);
    Insert(BuiltIns, "You're a walrus", STRING, "I'm not a walrus\n", STRING);

    Any* FunctionValue = Find(BuiltIns, "StringDeclaration");
    Output(FunctionValue);

    Any* StringValue = Find(BuiltIns, "You're a walrus");
    Output(StringValue);


    // for (int LineIndex = 0; LineIndex < Instructions->ElementCount; LineIndex++){
    //     printf("%s", Instructions->List[LineIndex]);
    // }
}