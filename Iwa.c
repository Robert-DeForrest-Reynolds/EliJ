#include <stdio.h>
#include <string.h>

int Addition(int a, int b)
{
    return a+b;
}

int Subtraction(int a, int b)
{
    return a-b;
}

int main(){
    FILE *SourceFile;
    SourceFile = fopen("Test.file", "r");

    char buffer[500];
    char SourceFileContents[50000000];
    char* Addition_Reference = "Addition";
    char* Subtraction_Reference = "Subtraction";

    while (fgets(buffer, 255, SourceFile) != NULL){
        printf("%s", buffer);
        strcat(SourceFileContents, buffer);
        // if (fgets(SourceFile) == *Addition_Reference) {
        //     printf("Found a function named Addition\n");
        // }
        // if (fgets(SourceFile) == *Subtraction_Reference) {
        //     printf("Found a function named Subtraction\n");
        // }
    }

    printf("%s", SourceFileContents);

    return 0;
}