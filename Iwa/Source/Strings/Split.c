#include <string.h>
#include <stdlib.h>
#include "PointerChecks.h"
#include "Structures.h"

StringList* Split(char* String, char SplitCharacter) {
    if (String == NULL) { return NULL; }
    int SplitCharacterIndexCount = 0;
    int StringSize = strlen(String);
    StringList* SplitBuffer = (StringList*) malloc(sizeof(StringList));
    StringList_Pointer_Check(SplitBuffer, "SplitBuffer List Allocation Fail");
    

    for (int Iteration = 0; Iteration < StringSize; Iteration++) {
        if (String[Iteration] == SplitCharacter) {
            SplitCharacterIndexCount++;
        }
    }

    SplitBuffer->List = malloc((SplitCharacterIndexCount + 2) * sizeof(char*));
    CharList_Pointer_Check(SplitBuffer->List, "Split Buffer Inner List Allocation Fail");
    if (SplitCharacterIndexCount == 0){
        SplitBuffer->List[0] = malloc((StringSize + 1) * sizeof(char));
        String_Pointer_Check(SplitBuffer->List[0], "SplitBuffer Element Allocation Fail");
        strcpy(SplitBuffer->List[0], String);
        SplitBuffer->List[1] = NULL;
        SplitBuffer->ElementCount = 2;
        return SplitBuffer;
    }

    int SegmentStart = 0;
    int SegmentIndex = 0;
    for (int Iteration = 0; Iteration <= StringSize; Iteration++) {
        if (String[Iteration] == SplitCharacter || String[Iteration] == '\0') {
            int SegmentLength = Iteration - SegmentStart;

            SplitBuffer->List[SegmentIndex] = malloc((SegmentLength + 1) * sizeof(char));
            String_Pointer_Check(SplitBuffer->List[SegmentIndex], "SplitBuffer Segment Allocation Fail");

            strncpy(SplitBuffer->List[SegmentIndex], &String[SegmentStart], SegmentLength);
            SplitBuffer->List[SegmentIndex][SegmentLength] = '\0';

            SegmentIndex++;
            SegmentStart = Iteration + 1;
            SplitBuffer->ElementCount += 1;
        }
    }
    
    SplitBuffer->List[SegmentIndex] = NULL;
    return SplitBuffer;
}