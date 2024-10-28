#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "Iwa.h"
#include "Interpreter.h"
#include "ReadFile.h"
#include "ReadFileLines.h"
#include "Contains.h"
#include "PointerChecks.h"
#include "Replace.h"
#include "Structures.h"
#include "Enums.h"
#include "Dictionary.h"
#include "Output.h"
#include "Find.h"
#include "FindBetween.h"

void Parse_User_Arguments(int ArgumentsCount, char* Arguments[]){
    for (int Iteration = 1; Iteration < ArgumentsCount; Iteration++) {
        size_t ArgumentLength = strlen(Arguments[Iteration]) + 3;
        ArgumentBufferPointer = malloc(ArgumentLength * sizeof(char));
        String_Pointer_Check(ArgumentBufferPointer, "ArgumentBuffer");
        snprintf(ArgumentBufferPointer, ArgumentLength, "%s", Arguments[Iteration]);
        if (Iteration == 1){
            FileNamePointer = File_Name_Check(ArgumentBufferPointer, ArgumentLength,  WorkingDirectoryLength);
        }
        free(ArgumentBufferPointer);
    }
}

int main(int ArgumentsCount, char* Arguments[]) {
    if (getcwd(WorkingDirectory, sizeof(WorkingDirectory)) == NULL) {
        perror("Failed to obtain current working directory.");
        return EXIT_FAILURE;
    }
    WorkingDirectoryLength = strlen(WorkingDirectory);

    Parse_User_Arguments(ArgumentsCount, Arguments);
    if (FileNamePointer != NULL) {
        if (Contains(FileNamePointer, "\\")) {
            FileNamePointer = Replace(FileNamePointer, "\\", "/");
            FinalWorkingDirectory = Replace(WorkingDirectory, "\\", "/");
            size_t FinalFileNameLength = strlen(FinalWorkingDirectory) + strlen(FileNamePointer) + 2;
            char* FinalFileName = malloc(FinalFileNameLength + 1 * sizeof(char));
            String_Pointer_Check(FinalFileName, "Final File Name Allocation Fail");
            strcpy(FinalFileName, FinalWorkingDirectory);
            strcat(FinalFileName, FileNamePointer);
            Instructions = Parse_Source_Code(FinalFileName);
        }
        else {
            Instructions = Parse_Source_Code(FileNamePointer);
        }

    }

    InternalTypeMap = Create_Dictionary(50);
    Insert(InternalTypeMap, "String", STRING, (int*) STRING, TYPE);
    Insert(InternalTypeMap, "Int", STRING, (int*) INT, TYPE);
    Insert(InternalTypeMap, "Out", STRING, (int*) OUTPUT, TYPE);
    
    char* String = malloc(strlen("\"Fuck\"") + 1 *sizeof(char));
    strcpy(String, "\"Fuck\"");
    String[7] = '\0';
    
    char* Sliced = Find_Between(String, "\"");
    printf("%s", Sliced);

    if (Instructions != NULL) {
        Run_Interpreter(Instructions);
    }
    return 0;
}
