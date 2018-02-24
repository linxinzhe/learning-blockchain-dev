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

char *get_random() {
    FILE *file;
    char *buffer;
    buffer = malloc(100);
    int flag;
    file = fopen("/dev/urandom", "r");
    flag = fread(buffer, 1, 100, file);
    printf("fread:%d%c", flag, 10);
    return buffer;
}

int main() {
    char *input;
    int length;
    length = 1000;

    char *output;
    output = (char *) malloc(1000);

    input = get_file("../random.txt");

    register_hash(&sha256_desc);
    hash_memory(find_hash("sha256"), (const unsigned char *) input, strlen(input), output,
                (unsigned long *) &length);

    printf("%d%c", length, 10);
    printf("%s%c", output, 10);
    printf("-----------%c", 10);

    printf("%02x%c", output[0], 10);
    printf("%02x%c", output[1], 10);
    printf("%02x%c", output[2], 10);
    printf("%02x%c", output[3], 10);

};