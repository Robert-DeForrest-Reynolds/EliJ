#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "PointerChecks.h"

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