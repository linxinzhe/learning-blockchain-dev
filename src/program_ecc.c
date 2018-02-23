#define TFM_DESC

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
    length = 1000;
    char output[length];

    prng_state random;
    ecc_key key;

    ltc_mp = tfm_desc;

    input = get_file("../random.txt");

    register_prng(&sprng_desc);
    register_hash(&sha256_desc);

    char buffer[length];

    ecc_make_key(&random, find_prng("sprng"), 32, &key);
    ecc_export(buffer, &length, PK_PUBLIC, &key);

    printf("%d%c", length, 10);
    printf("%s%c", buffer, 10);

};