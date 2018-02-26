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

unsigned char *get_output(unsigned int *total) {
    // A,B,address,amount
    unsigned char *private, *public, *complete, *y;
    unsigned int length, *x, z;

    private = get_private(&length);
    public = get_public(&length, private);

    complete = malloc(*total = 16 + length);

    x = malloc(4); //A
    memset(x, 0, 4);
    *x = 16 + length;
    memcpy(complete, x, 4);

    x = malloc(4);  //B
    memset(x, 0, 4);
    *x = length;
    memcpy(complete + 4, x, 4);

    y = malloc(length);  //address
    memset(y, 0, length);
    memcpy(y, public, length);
    memcpy(complete + 8, y, length);

    y = malloc(8);  //amount
    memset(y, 0, 8);
    z = 1000;
    memcpy(y, &z, 4);  //  int32 fit in y low 4 byte address
    memset(y + 4, 0, 4); // high 4 byte set 0
    memcpy(complete + 8 + length, y, 8);

    return complete;
}

unsigned char *get_input(unsigned int *total) {
    // A index B public C signature transaction

    int length;
    int *x;
    unsigned char *y;

    char *public, *private, *complete;

    private = get_private(&length);
    public = get_public(&length, private);


    complete = malloc(*total = 48 + length);

    x = malloc(4);  //A
    memset(x, 0, 4);
    *x = 48 + length;
    memcpy(complete, x, 4);

    x = malloc(4); //index
    memset(x, 0, 4);
    *x = 0;
    memcpy(complete + 4, x, 4);

    x = malloc(4);  //B
    memset(x, 0, 4);
    *x = length;
    for (int i = 1; i < 4; ++i) {
        x[i] = 0;
    }
    memcpy(complete + 8, x, 4);

    y = malloc(length); //public
    memset(y, 0, length);
    memcpy(y, public, length);
    memcpy(complete + 12, y, length);

    x = malloc(4);  //C,c=0.signature not exist
    memset(x, 0, 4);
    *x = 0;
    memcpy(complete + 12 + length, x, 4);

    y = malloc(32); //transaction
    memset(y, 0, 32);
    *y = 0;
    memcpy(complete + 16 + length, y, 32);

    return complete;
}

unsigned char *get_transaction(unsigned int *total) {
    // A B C input output
    // B: number of input
    // C: number of output


    unsigned char *input, *output, *complete, *y;
    unsigned int length_input, length_output, *x;

    input = get_input(&length_input);
    output = get_output(&length_output);

    complete = malloc(*total = 12 + length_input + length_output);

    x = malloc(4);  //A
    memset(x, 0, 4);
    *x = 12 + length_input + length_output;
    memcpy(complete, x, 4);

    x = malloc(4);  //B
    memset(x, 0, 4);
    *x = 1;  // one input
    memcpy(complete + 4, x, 4);

    x = malloc(4);  //C
    memset(x, 0, 4);
    *x = 1;    // one input
    memcpy(complete + 8, x, 4);

    y = malloc(length_input);
    memset(y, 0, length_input);
    memcpy(y, input, length_input);
    memcpy(complete + 12, y, length_input);

    y = malloc(length_output);
    memset(y, 0, length_output);
    memcpy(y, output, length_output);
    memcpy(complete + 12 + length_input, y, length_output);

    return complete;
}

unsigned char *get_head(unsigned char *root) {
    //current nonce previous target time
    unsigned char *complete, *y;
    unsigned int *x;
    complete = malloc(104);

    y = malloc(32); //current
    memset(y, 0, 32);
    memcpy(y, root, 32);
    memcpy(complete, y, 32);

    x = malloc(4); //nonce
    memset(x, 0, 4);
    *x = 0;
    memcpy(complete + 32, x, 4);

    y = malloc(32);
    memset(y, 0, 32);
    memcpy(complete + 36, y, 32);

    y = malloc(32); //target, bigger then easier
    memset(y, 255, 32); //255, easiest
    memcpy(complete + 68, y, 32);

    x = malloc(4); // time
    memset(x, 0, 4);
    *x = time(0);
    memcpy(complete + 100, x, 4);

    return complete;
}

int main() {
    char *head, *input, *output, *transaction, *root;
    int length_input, length_output, length_transaction, length_root;

    prng_state random;
    ecc_key key;
    ltc_mp = tfm_desc;

    register_prng(&sprng_desc);
    register_hash(&sha256_desc);

    transaction = get_transaction(&length_transaction);

    root = malloc(length_root = 32);
    hash_memory(find_hash("sha256"), transaction, length_transaction, root, &length_root);

    head = get_head(root);
    write(1, head, 104);
};