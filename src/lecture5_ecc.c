#define TFM_DESC

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <zconf.h>
#include "tfm_desc.c"

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
    length = 1000;

    prng_state random;
    ecc_key key;
    ltc_mp = tfm_desc;

    output = (char *) malloc(1000);
    length = 1000;

    input = get_file("../essay.txt");

    register_prng(&sprng_desc);

    unsigned char *buffer;
    buffer = malloc(1000);

    ecc_make_key(&random, find_prng("sprng"), 32, &key);
    ecc_export(buffer, (unsigned long *) &length, PK_PUBLIC, &key);

    printf("%d%c", length, 10);
    printf("%s%c", buffer, 10);
};