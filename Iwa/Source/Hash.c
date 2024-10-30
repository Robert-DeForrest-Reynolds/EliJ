#include <stdio.h>
#include <stdlib.h>

unsigned int Hash(const char* Key, int TableSize) {
    if (Key == NULL) { puts("Key is null when trying to hash."); exit(EXIT_FAILURE); }
    unsigned int HashValue = 5381;
    int CharacterASCII;
    while ((CharacterASCII = *Key++)) {
        HashValue = ((HashValue << 5) + HashValue) + CharacterASCII;
    }
    return HashValue % TableSize;
}