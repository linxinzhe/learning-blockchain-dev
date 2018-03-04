#define TFM_DESC

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "tfm.h"
#include "tomcrypt.h"

char *get_sha256(char *buffer, int size)
{
    hash_state resource;
    char *digest;

    digest = malloc(32);
    sha256_init(&resource);
    sha256_process(&resource, buffer, size);
    sha256_done(&resource, digest);

    return digest;
}

char *get_merkle_root(char *old, int size)
{
    char *new, output[32], input[64];
    int index;

    printf("activation (%d)%c", size, 10);

    if (size == 1) {

        return old;
    }

    if (size % 2) {

        new = malloc(32 * (size + 1));
        memcpy(new, old, size * 32);
        memcpy(new + size * 32, old + (size - 1) * 32, 32);
        free(old);

        return get_merkle_root(new, size + 1);
    }

    new = malloc(32 * size / 2);

    for (index = 0; index < size; index += 2) {

        memcpy(input, old + index * 32, 64);
        memcpy(new + (index / 2) * 32, get_sha256(input, 64), 32);
    }

    free(old);

    return get_merkle_root(new, size / 2);
}

void print_digest(char *digest)
{
    int index;

    for (index = 0; index < 32; index++)
        printf("%02hhx", digest[index]);

    printf("%c", 10);
}

void main()
{
    ltc_mp = tfm_desc;
    register_prng(&sprng_desc);
    register_hash(&sha256_desc);

    char *collection, *digest;

    collection = malloc(160);
    memcpy(collection, get_sha256("a", 1), 32);
    memcpy(collection + 32, get_sha256("b", 1), 32);
    memcpy(collection + 64, get_sha256("c", 1), 32);
    memcpy(collection + 96, get_sha256("d", 1), 32);
    memcpy(collection + 128, get_sha256("e", 1), 32);

    print_digest(get_merkle_root(collection, 5));
}