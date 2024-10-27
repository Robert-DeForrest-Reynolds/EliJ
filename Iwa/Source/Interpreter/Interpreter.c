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
#include "Input.h"
#include "Split.h"

/*

Any* values are used to deal with user declared values.
The built-in functions are usable in the source code for the interpreter, as well as usable for the user.
Be very attentative when using built-in functions within the source-code, that isn't usable by the user, as there is a good chance there's a better way.

*/

Dictionary* Globals;


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

    while (fgets(LineBuffer, LineBufferSize, FilePointer)) {
        LineCount += 1;
    }

    StringList* Contents = (StringList*)malloc(sizeof(StringList));
    Contents->List = malloc((LineCount + 1) * sizeof(char*));
    StringList_Pointer_Check(Contents, "Read File Contents Pointer Allocation Fail");

    rewind(FilePointer);
    LineCount = 0;

    while (fgets(LineBuffer, LineBufferSize, FilePointer)) {
        if (strcmp(LineBuffer, "\n") == 0) { continue; }
        size_t LineLength = strlen(LineBuffer);
        if (LineLength > 0 && LineBuffer[LineLength - 1] == '\n') {
            LineBuffer[LineLength - 1] = '\0';
        }

        Contents->List[LineCount] = malloc((LineLength + 1) * sizeof(char));
        String_Pointer_Check(Contents->List[LineCount], "Read File Lines Inner String Allocation Fail");
        strcpy(Contents->List[LineCount], LineBuffer);

        LineCount += 1;
    }

    free(LineBuffer);
    fclose(FilePointer);

    Contents->List[LineCount] = NULL;
    Contents->ElementCount = LineCount;

    return Contents;
}


Pair* Variable_Declaration(char* Line){
    Pair* GlobalPair;
    return GlobalPair;
}


// Most of this will be cleaned up when the program closes, and doesn't need to be freed during runtime at all
void Functions_Setup(){ printf("\nExecuting Functions_Setup\n");
    Function* VariableDeclaration = malloc(sizeof(Function));
    VariableDeclaration->Function = Variable_Declaration;
    VariableDeclaration->FunctionName = "Variable_Declaration";

    Function* OutputFunction = malloc(sizeof(Function));
    OutputFunction->Function = Output;
    OutputFunction->FunctionName = "Output";

    Function* InputFunction = malloc(sizeof(Function));
    InputFunction->Function = Input;
    InputFunction->FunctionName = "Input";

    // Variable Types
    Insert(Globals, "String", STRING, VariableDeclaration, FUNCTION);
    Insert(Globals, "Int", STRING, VariableDeclaration, FUNCTION);
    Insert(Globals, "Float", STRING, VariableDeclaration, FUNCTION);
    Insert(Globals, "List", STRING, VariableDeclaration, FUNCTION);

    // Built-In Functions
    Insert(Globals, "Out", STRING, OutputFunction, FUNCTION);
    Insert(Globals, "Input", STRING, InputFunction, FUNCTION);
}


void Execute_Instruction(char* Instruction){ printf("\nExecuting Execute_Instruction\n");
    int InstructionLength = strlen(Instruction);
    char* KeyWordBuffer = malloc((InstructionLength + 1) * sizeof(char));
    StringList InstructionSet;
    bool InitialCharacterFound = false;
    int IndexOfFirstCharacter;
    for (int CharacterIndex = 0; CharacterIndex < InstructionLength; CharacterIndex++){
        if (Instruction[CharacterIndex] != ' ') {
            InitialCharacterFound = true;
            IndexOfFirstCharacter = CharacterIndex;
            break;
        }
    }
    for (int CharacterIndex = IndexOfFirstCharacter; CharacterIndex < InstructionLength; CharacterIndex++){

        if (InitialCharacterFound == true && Instruction[CharacterIndex] == ' ' | Instruction[CharacterIndex] == '('){
            strncpy(KeyWordBuffer, Instruction, CharacterIndex);
            KeyWordBuffer[CharacterIndex] = '\0';
            Any* InstructionKeyword = Find(Globals, (char *) KeyWordBuffer);
            if (InstructionKeyword != NULL){
                printf("Keyword found: %s\n", KeyWordBuffer);
                printf("Keyword Type: %s\n", TypesAsStrings[InstructionKeyword->ValueType]);
            }
            free(InstructionKeyword);
        }
    }
    free(KeyWordBuffer);
}


void Run_Interpreter(StringList* Instructions){
    printf("\nExecuting Run_Interpreter\n");
    
    Globals = Create_Dictionary(20);
    Functions_Setup();

    for (int LineIndex = 0; LineIndex < Instructions->ElementCount; LineIndex++){
        if (Instructions->List[LineIndex] != NULL){
            puts("\nExecuting instruction...\n");
            printf("Instruction: %s\n", Instructions->List[LineIndex]);
            Execute_Instruction(Instructions->List[LineIndex]);
            puts("Finished instruction");
        }
        // Any* Instruction = Find(Globals, Instructions->List[LineIndex]);
        // if ((char *) Instruction->Value != NULL){
        //     printf("We've found a valid instruction");
        // }
        // printf("%s", Instructions->List[LineIndex]);
        // if (strncmp(Instructions->List[LineIndex], "String", 6) == 0){
        //     Variable_Declaration(Instructions->List[LineIndex]);
        // }
    }
    free(Globals);
}