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
    char *input, *output;
    int length;

    output = malloc(1000);
    length = 1000;
    input = get_file("../random.txt");

    register_hash(&sha256_desc);
    hash_memory(find_hash("sha256"), input, strlen(input), output, &length);

    printf("%d%c", length, 10);
//    printf("-----------");
    printf("%02x%c", output[0], 10);
    printf("%02x%c", output[1], 10);
    printf("%02x%c", output[2], 10);
    printf("%02x%c", output[4], 10);

};