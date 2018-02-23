#include "tomcrypt.h"
#include <stdio.h>
#include <stdlib.h>

char *get_file(char *path) {
    FILE *file;
    int length;
    char *contents;

    file = fopen(path, "r+");
    fseek(file, 0, SEEK_END);
    length = ftell(file);
    fseek(file, 0, SEEK_SET);

    contents = malloc(length + 1);
    fread(contents, 1, length, file);
    fclose(file);
    return contents;
}

int main() {
    char *input;
    int length;

    char output[1000];
    length = 1000;
    for (int i = 0; i < length; ++i) {
        output[i] = 0;
    }

    input = get_file("../random.txt");

    register_hash(&sha256_desc);
    hash_memory(find_hash("sha256"), (const unsigned char *) input, strlen(input), (unsigned char *) output,
                (unsigned long *) &length);

    printf("%d%c", length, 10);
    printf("%s%c",output,10);
    printf("-----------%c",10);

    printf("%02x%c", output[0], 10);
    printf("%02x%c", output[1], 10);
    printf("%02x%c", output[2], 10);
    printf("%02x%c", output[4], 10);

};