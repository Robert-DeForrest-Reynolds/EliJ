#include <stdio.h>

unsigned int Hash(const char* Key, int TableSize) {
    if (Key == NULL) { return 0; }
    unsigned int HashValue = 5381;
    int CharacterASCII;
    while ((CharacterASCII = *Key++)) {
        HashValue = ((HashValue << 5) + HashValue) + CharacterASCII;
    }
    return HashValue % TableSize;
}