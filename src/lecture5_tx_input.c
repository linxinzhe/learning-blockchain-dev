#define TFM_DESC

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <zconf.h>
#include "tfm_desc.c"


//ECC：BTC public private key generation
// a=open("/dev/urandom")
// b=read(a,128)  // get random bytes
// c=get_private(b) // private key，can generate the following
// d=get_public(c)  // public key
// e=get_address(d) // address

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

unsigned char *get_private(unsigned int *length) {
    prng_state random;
    ecc_key key;
    unsigned char *buffer;

    buffer = malloc(*length = 1000);
    ecc_make_key(&random, find_prng("sprng"), 32, &key);
    ecc_export(buffer, length, PK_PRIVATE, &key);

    return buffer;
}

unsigned char *get_public(unsigned *length, unsigned char *private) {
    ecc_key key;
    unsigned char *buffer;
    ecc_import(private, *length, &key);
    buffer = malloc(*length = 1000);
    ecc_export(buffer, length, PK_PUBLIC, &key);

    return buffer;
}

unsigned char *get_input() {
    // A index B public C signature transaction

    int length;
    int *x;
    unsigned char *y;

    char *public, *private, *complete;

    private = get_private(&length);
    public = get_public(&length, private);

    int total = 48 + length;
    complete = malloc(total);

    x = malloc(4);  //A
    *x = 48 + length;
    memcpy(complete, x, 4);

    x = malloc(4); //index
    *x = 0;
    memcpy(complete + 4, x, 4);

    x = malloc(4);  //B
    *x = length;
    memcpy(complete + 8, x, 4);

    y = malloc(length); //public
    memcpy(y, public, length);
    memcpy(complete + 12, y, length);

    x = malloc(4);  //C,c=0.signature not exist
    *x = 0;
    memcpy(complete + 12 + length, x, 4);

    y = malloc(32); //transaction
    *y = 0;
    memcpy(complete + 16 + length, y, 32);

    write(1, complete, total);

    return complete;
}

int main() {
    prng_state random;
    ecc_key key;
    ltc_mp = tfm_desc;

    register_prng(&sprng_desc);
    register_hash(&sha256_desc);

    unsigned char *input;
    input = get_input();


};