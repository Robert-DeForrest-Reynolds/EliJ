#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "Split.h"
#include "PointerChecks.h"

char** Split(char* String, char SplitCharacter) {
    int SplitCharacterIndexCount = 0;
    int StringSize = strlen(String);
    for (int Iteration = 0; Iteration < StringSize; Iteration++) {
        if (String[Iteration] == SplitCharacter) {
            SplitCharacterIndexCount++;
        }
    }

    char** SplitBuffer = malloc((SplitCharacterIndexCount + 2) * sizeof(char*));
    String_List_Pointer_Check(SplitBuffer, "SplitBuffer");
    if (SplitCharacterIndexCount == 0){
        SplitBuffer = malloc(2 * sizeof(char*));
        SplitBuffer[0] = malloc((StringSize + 1) * sizeof(char));
        String_Pointer_Check(SplitBuffer[0], "SplitBuffer");
        strcpy(SplitBuffer[0], String);
        SplitBuffer[1] = NULL;
        return SplitBuffer;
    } else {
        SplitBuffer = malloc((SplitCharacterIndexCount + 2) * sizeof(char*));
    }

    int SegmentStart = 0;
    int SegmentIndex = 0;
    for (int Iteration = 0; Iteration <= StringSize; Iteration++) {
        if (String[Iteration] == SplitCharacter || String[Iteration] == '\0') {
            int SegmentLength = Iteration - SegmentStart;

            SplitBuffer[SegmentIndex] = malloc((SegmentLength + 1) * sizeof(char));
            String_Pointer_Check(SplitBuffer[Iteration], "SplitBuffer Segment");

            strncpy(SplitBuffer[SegmentIndex], &String[SegmentStart], SegmentLength);
            SplitBuffer[SegmentIndex][SegmentLength] = '\0';

            SegmentIndex++;
            SegmentStart = Iteration + 1;
        }
    }
    
    SplitBuffer[SegmentIndex] = NULL;
    return SplitBuffer;
}