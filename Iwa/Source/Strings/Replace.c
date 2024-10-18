#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Contains.h"
#include "PointerChecks.h"

char* Replace(char* Destination, char* Match, char* Replacement){
    int MatchCount = 0;
    int StringLength = strlen(Destination);
    int MatchLength = strlen(Match);
    int ReplacementLength = strlen(Replacement);

    for (int Iteration = 0; Iteration < StringLength; Iteration++){
        if (Contains(&Destination[Iteration], Match)){
            MatchCount += 1;
        }
    }

    size_t ReplacementSubtraction = (ReplacementLength * MatchCount) - (MatchLength * MatchCount);
    size_t ReplaceStringSize = (StringLength + ReplacementSubtraction + 1);
    char* ReplacedString = malloc(ReplaceStringSize * sizeof(char));

    int ReplacedIndex = 0;
    for (int Iteration = 0; Iteration < StringLength; Iteration++) {
        if (Destination[Iteration] == '\\' && Destination[Iteration+1] == '\\') { // The potential of someone leaving an unescaped escape 
            continue;                                                             // character at the end of an array could lead to failure here
        } else if (strncmp(&Destination[Iteration], Match, MatchLength) == 0) {
            strcpy(&ReplacedString[ReplacedIndex], Replacement);
            ReplacedIndex += ReplacementLength;
            Iteration += MatchLength - 1;
        } else {
            ReplacedString[ReplacedIndex++] = Destination[Iteration];
        }
    }

    ReplacedString[ReplacedIndex] = '\0';
    Destination = malloc(ReplaceStringSize + 1 * sizeof(char));
    String_Pointer_Check(Destination, "Replacement String Allocation Fail");
    strcpy(Destination, ReplacedString);
    free(ReplacedString);
    return Destination;
}