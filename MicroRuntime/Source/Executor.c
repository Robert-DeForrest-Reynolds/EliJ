#include <stdio.h>
#include <string.h>

void Executor(char* instruction)
{
    printf("\nExecuting instruction: %s", instruction);

    char opening_brace;

    if (strncmp(instruction, "Output", 6) == 0)
    {
        opening_brace = *(instruction+6);
        if (strcmp(opening_brace, "(") != 0) printf("Invalid Syntax");
        printf("%c", opening_brace);
    }

    printf("Instruction executed\n");
    return;
}