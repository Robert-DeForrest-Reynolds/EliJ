#include <stdio.h>
#include "Headers/Executor.h"
#include <string.h>

void Load_Program(char* program_name)
{
    printf("\nLoading program: %s\n", program_name);

    char source_code_character;
    char source_code_line[256] = "";

    FILE *source_file = fopen(program_name, "r");

    if (source_file == NULL)
    {
        printf("Error: Could not open file: %s\n", program_name);
        return;
    }

    while (1)
    {   
        source_code_character = fgetc(source_file);
        strncat(source_code_line, &source_code_character, sizeof(source_code_character));
        if (source_code_character == '\n')
        {
            Executor(source_code_line);
            strcpy(source_code_line, "");
        }
        if (source_code_character == EOF)
        {
            break;
        }
    }

    return;
}