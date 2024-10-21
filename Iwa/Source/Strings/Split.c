#include <string.h>
#include <stdlib.h>
#include "PointerChecks.h"
#include "Structures.h"

StringList* Split(char* String, char SplitCharacter) {
    int SplitCharacterIndexCount = 0;
    int StringSize = strlen(String);
    for (int Iteration = 0; Iteration < StringSize; Iteration++) {
        if (String[Iteration] == SplitCharacter) {
            SplitCharacterIndexCount++;
        }
    }

    StringList* SplitBuffer = (StringList*) malloc(sizeof(StringList));
    SplitBuffer->List = malloc((SplitCharacterIndexCount + 2) * sizeof(char*));
    StringList_Pointer_Check(SplitBuffer, "SplitBuffer");
    if (SplitCharacterIndexCount == 0){
        SplitBuffer = malloc(2 * sizeof(char*));
        SplitBuffer->List[0] = malloc((StringSize + 1) * sizeof(char));
        String_Pointer_Check(SplitBuffer->List[0], "SplitBuffer");
        strcpy(SplitBuffer->List[0], String);
        SplitBuffer->List[1] = NULL;
        return SplitBuffer;
    }

    int SegmentStart = 0;
    int SegmentIndex = 0;
    for (int Iteration = 0; Iteration <= StringSize; Iteration++) {
        if (String[Iteration] == SplitCharacter || String[Iteration] == '\0') {
            int SegmentLength = Iteration - SegmentStart;

            SplitBuffer->List[SegmentIndex] = malloc((SegmentLength + 1) * sizeof(char));
            String_Pointer_Check(SplitBuffer->List[Iteration], "SplitBuffer Segment");

            strncpy(SplitBuffer->List[SegmentIndex], &String[SegmentStart], SegmentLength);
            SplitBuffer->List[SegmentIndex][SegmentLength] = '\0';

            SegmentIndex++;
            SegmentStart = Iteration + 1;
        }
    }
    
    SplitBuffer->List[SegmentIndex] = NULL;
    return SplitBuffer;
}