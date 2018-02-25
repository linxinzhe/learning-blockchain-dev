#define TFM_DESC

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tfm_desc.c"

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

int main() {
    unsigned char *private,*public,*buffer;
    unsigned int length_private,length_public,length_buffer;

    ltc_mp = tfm_desc;
    register_prng(&sprng_desc);
    register_hash(&sha256_desc);

    private = get_private(&length_private);
    length_public = length_private;
    public = get_public(&length_public, private);

    buffer = malloc(1000);
    memset(buffer,0,1000);
    base64_encode(public, length_public, buffer, &length_buffer);
    printf("%s%c", buffer, 10);

    memset(buffer,0,1000);
    base64_encode(private, length_private, buffer, &length_buffer);
    printf("%s%c%c", buffer, 10, 10);


};