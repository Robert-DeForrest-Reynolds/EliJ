#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void String_Pointer_Check(char* Pointer, const char* PointerName){
    if (Pointer == NULL) {
        puts(PointerName);
        exit(EXIT_FAILURE);
    }
}

void String_List_Pointer_Check(char** Pointer, const char* PointerName){
    if (Pointer == NULL) {
        puts(PointerName);
        exit(EXIT_FAILURE);
    }
}

char* ArgumentBufferPointer;
char* FileNamePointer;


char** Split(char* String, char SplitCharacter) {
    int SplitCharacterIndexCount = 0;
    int StringSize = strlen(String);

    for (int Iteration = 0; Iteration < StringSize; Iteration++) {
        if (String[Iteration] == SplitCharacter) {
            SplitCharacterIndexCount++;
        }
    }

    char** SplitBuffer = malloc((SplitCharacterIndexCount + 1) * sizeof(char*));
    int SegmentStart = 0;
    int SegmentIndex = 0;
    if (SplitCharacterIndexCount > 0){
        String_List_Pointer_Check(SplitBuffer, "SplitBuffer");
        for (int Iteration = 0; Iteration <= StringSize; Iteration++) {
            if (String[Iteration] == SplitCharacter || String[Iteration] == '\0') {
                int SegmentLength = Iteration - SegmentStart;

                SplitBuffer[SegmentIndex] = malloc((SegmentLength + 1) * sizeof(char));
                String_Pointer_Check(SplitBuffer[SegmentIndex], "SplitBuffer Segment");

                strncpy(SplitBuffer[SegmentIndex], &String[SegmentStart], SegmentLength);
                SplitBuffer[SegmentIndex][SegmentLength] = '\0';

                SegmentIndex++;
                SegmentStart = Iteration + 1;
            }
        }
    }
    SplitBuffer[SegmentIndex] = NULL;
    return SplitBuffer;
}

void Parse_User_Arguments(int ArgumentsCount, char* Arguments[]){
    for (int Iteration = 0; Iteration < ArgumentsCount; Iteration++) {
        size_t ArgumentLength = strlen(Arguments[Iteration]) + 3;
        if (ArgumentLength > 256) { return; } // Abort program if an argument is greater 256, this needs to handled more gracefully
        snprintf(ArgumentBufferPointer, ArgumentLength, "%s \n", Arguments[Iteration]);
        fwrite(ArgumentBufferPointer, sizeof(char), strlen(ArgumentBufferPointer), stdout);
        char SplitChar = '.';
        char** CharSplit = Split(ArgumentBufferPointer, SplitChar);
        if (CharSplit[0] != NULL){
            printf("Splitting: %s", ArgumentBufferPointer);
            for (int Iteration = 0; CharSplit[Iteration] != NULL; Iteration++) {
                printf("%s\n", CharSplit[Iteration]);
            }
        }
        free(CharSplit);
    }
    free(ArgumentBufferPointer);
}

int main(int ArgumentsCount, char* Arguments[]) {
    ArgumentBufferPointer = malloc(256 * sizeof(char));
    FileNamePointer = malloc(256 * sizeof(char));
    String_Pointer_Check(ArgumentBufferPointer, "ArgumentBuffer");
    Parse_User_Arguments(ArgumentsCount, Arguments);
    free(FileNamePointer);
    return 0;
}
