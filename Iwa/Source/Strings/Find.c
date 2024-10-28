#include <stdio.h>
#include <string.h>

int Find(char* String, char* Query){
    int StringLength = strlen(String);
    int QueryLength = strlen(Query);

    //Single Character Query
    if (QueryLength == 1){
        for (int CharacterIndex = 0; CharacterIndex < StringLength; CharacterIndex++){
            if (String[CharacterIndex] == Query[0]){
                return CharacterIndex;
            }
        }
    }

    //Multi Character Sliding Window Find
    int LowerBound = 0;
    int UpperBound = QueryLength;
    for (int CharacterIndex = 0; CharacterIndex + UpperBound < StringLength; CharacterIndex++){
        if (strncmp((String + CharacterIndex), Query, QueryLength) == 0){
            return CharacterIndex;
        }
        LowerBound++;
    }
    return -1;
}