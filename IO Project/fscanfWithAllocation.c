#include <stdio.h>
#include <stdlib.h>

void fscanfUnlimited(FILE *file, char **buffor, char terminate) {
    char c = 0;
    int size = 128;
    int currentSize = 0;

    *buffor = malloc(sizeof(char) * size);
    while ((c = (char)fgetc(file)) != terminate) {
        (*buffor)[currentSize] = c;
        currentSize += 1;
        if (currentSize == size) {
            size *= 2;
            realloc(*buffor, size);
        }
    }
    (*buffor)[currentSize] = '\0';
}