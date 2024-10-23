unsigned int Hash(const char* Key, int TableSize) {
    unsigned int HashValue = 0;
    while (*Key) {
        HashValue = (HashValue << 5) + *Key++;
    }
    return HashValue % TableSize;
}