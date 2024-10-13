#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int ArgumentsCount, char *Arguments[]) {
    for (int Iteration = 0; Iteration < ArgumentsCount; Iteration++) {
        size_t ArgumentLength = strlen(Arguments[Iteration]) + 3;

        char *String = malloc(ArgumentLength);
        if (String == NULL) {
            perror("Failed to allocate memory");
            return 1;
        }
        snprintf(String, ArgumentLength, "%s \n", Arguments[Iteration]);

        fwrite(String, sizeof(char), strlen(String), stdout);

        free(String);
    }
    return 0;
}
