#include "string.h"

int Left_Trim_Index(char* Line){
    for (int Index = 0; Index < strlen(Line); Index++){
        if (Line[Index] != ' '){
            return Index;
        }
    }
    return -1;
}