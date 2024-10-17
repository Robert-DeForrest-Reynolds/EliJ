#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "Split.h"
#include "PointerChecks.h"

SplitResult* Split(char* String, char SplitCharacter) {
    int SplitCharacterIndexCount = 0;
    int StringSize = strlen(String);
    for (int Iteration = 0; Iteration < StringSize; Iteration++) {
        if (String[Iteration] == SplitCharacter) {
            SplitCharacterIndexCount++;
        }
    }

    SplitResult* SplitBuffer = malloc(sizeof(SplitResult));
    SplitResult_Pointer_Check(SplitBuffer, "SplitBuffer");
    if (SplitCharacterIndexCount == 0){
        SplitBuffer->Result = malloc(2 * sizeof(char*));
        SplitBuffer->Result[0] = malloc((StringSize + 1) * sizeof(char));
        String_Pointer_Check(SplitBuffer->Result[0], "SplitBuffer->Result");
        strcpy(SplitBuffer->Result[0], String);
        SplitBuffer->Result[1] = NULL;
        return SplitBuffer;
    } else {
        SplitBuffer->Result = malloc((SplitCharacterIndexCount + 2) * sizeof(char*));
    }

    int SegmentStart = 0;
    int SegmentIndex = 0;
    for (int Iteration = 0; Iteration <= StringSize; Iteration++) {
        if (String[Iteration] == SplitCharacter || String[Iteration] == '\0') {
            int SegmentLength = Iteration - SegmentStart;

            SplitBuffer->Result[SegmentIndex] = malloc((SegmentLength + 1) * sizeof(char));
            String_Pointer_Check(SplitBuffer->Result[Iteration], "SplitBuffer Segment");

            strncpy(SplitBuffer->Result[SegmentIndex], &String[SegmentStart], SegmentLength);
            SplitBuffer->Result[SegmentIndex][SegmentLength] = '\0';

            SegmentIndex++;
            SegmentStart = Iteration + 1;
        }
    }
    
    SplitBuffer->Result[SegmentIndex] = NULL;
    return SplitBuffer;
}