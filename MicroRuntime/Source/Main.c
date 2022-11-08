#include <stdio.h>
#include "Headers/Runtime.h"
#include "Headers/LoadProgram.h"

int main(int argc, char *argv[])
{
    Initialize_Runtime();
    printf("\nAmount of arguments passed: %i\n", argc);
    
    for (int i = 0; i < argc; i++){
        printf("Argument %i:%s\n", i, argv[i]);
    }

    if (argc > 1){
        Load_Program(argv[1]);
    }
    else{
        printf("\nNo program specified.\n");
    }

    return 0;
}