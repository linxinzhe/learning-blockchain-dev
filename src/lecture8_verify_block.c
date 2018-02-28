#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int count(void *cursor) {
    int count;
    void *Y;
    count = 0;

    while (cursor != 0) {
        count++;
        Y = cursor + 4;
        cursor = (void *) *Y;
    }
}

void *build_pair(void *left, void *right) {
    void *pair;
    pair = malloc(8);
    memcpy(pair, &left, 4);
    memcpy(pair + 4, &right, 4);
    return pair;
}

int scan(char *source) {
    int *size;
    size = (int *) source;
    return *size;
}

char measure(char *source) {
    int *length;
    length = (int *) (source - 4);
    return *length;
}

char *build(char *source, int length) {
    char *destination;
    destination = malloc(length + 4) + 4;
    memcpy(destination, source, length);
    memcpy(destination - 4, &length, 4);

    return destination;
}

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
    char *limit;
    void *list;
    limit = cursor + length;
    list = 0;
    list = build_pair(build(cursor, 104), list);
    cursor += 104;

    while (cursor < limit) {
        char *x = build(cursor, scan(cursor));
        printf("valid pointer:%d%c", x, 10);
        list = build_pair(x, list);
        cursor += scan(cursor);
    }
    return list;
}

uint64_t get_output_amount(unsigned char *output) {
    int *B;
    uint64_t amount;

    B = (int *) (output + 4);

    memcpy(&amount, output + 8 + *B, 8);
    return amount;
}

int verify(char *transaction) {
    // A B C input output
    int *A, *B, *C;
    char *cursor;
    int count;

    A = (int *) transaction;
    B = (int *) (transaction + 4);
    C = (int *) (transaction + 8);

    uint64_t input_total, output_total;
    cursor = transaction + 12;
    count = *B;

    while (count--) {
        cursor += scan(cursor);
    }

    count = *C;

    while (count--) {
        output_total += get_output_amount(cursor);
        cursor += scan(cursor);
    }

    printf("number of outputs: %d%c", *C, 10);
    printf("volumn of outputs: %d%c", output_total, 10);


    return 0;
}

int main(int count, char **arguments) {
    char *block, *data;
    long length;
    void *list;
    char *a;

    block = get_file(arguments[1], &length);
    list = slice(block, length);

    while ((int) list != 0) {
        data = (unsigned char *) *(int *) list;
        printf("value: %d%c", (int) data, 10);
        list = (void *) *(int *) (list + 4);
        printf("list: %d%c", (int) list, 10);
    }


}