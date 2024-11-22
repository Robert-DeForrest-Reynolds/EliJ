#include <string.h>

int Count(char* String, char* Query){
    int StringLength = strlen(String);
    int QueryLength = strlen(Query);
    int Count = 0;
    for (int Index = 0; Index < StringLength; Index++){
        if (strncmp(String+Index, Query, QueryLength) == 0) Count++;
    }
    return Count;
}