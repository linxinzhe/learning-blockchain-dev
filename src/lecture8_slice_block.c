#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *get_file(char *path, unsigned int *length) {
    FILE *file;
    char *contents;

    file = fopen(path, "r+");
    fseek(file, 0, SEEK_END);
    *length = ftell(file);
    fseek(file, 0, SEEK_SET);

    contents = malloc(*length);
    fread(contents, 1, *length, file);

    fclose(file);

    return contents;
}

unsigned int slice(unsigned char *cursor, unsigned int length) {
    unsigned char *limit, *transaction;
    unsigned int *X;
    void *list, *link;
    limit = cursor + length;
    cursor += 104;

    while (cursor < limit) {
        X = (unsigned int *) cursor;
        transaction = malloc(*X + 4) + 4;
        memcpy(transaction, cursor, *X);
        memcpy(transaction - 4, X, 4);
        cursor += *X;

        link = malloc(8);
        memcpy(link, transaction, 4);
        memcpy(link + 4, list, 4);

        list = link;
    }
}

int main(int count, char **arguments) {
    unsigned char *block;
    unsigned int length;
    block = get_file(arguments[1], &length);
    printf("%d%c", slice(block, length), 10);
}