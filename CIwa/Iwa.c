#include <stdio.h>
#include <string.h>

#include <stdlib.h>

int Addition(int a, int b)
{
    return a+b;
}

int Subtraction(int a, int b)
{
    return a-b;
}

int main(){
    printf("Commencing CIwa...\n");
    
    FILE *SourceFilePointer;
    SourceFilePointer = fopen("CIwa/Test.file", "r");

    char single_line[256];

    while(!feof(SourceFilePointer)){
        printf("Found data\n");
        fgets(single_line, sizeof(single_line), SourceFilePointer);
        printf("%s\n", single_line);
    }

    printf("%s", single_line);
    fclose(SourceFilePointer);

    return 0;
}