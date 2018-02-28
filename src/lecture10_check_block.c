#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int scan(char *source) {
    int *size;
    size = (int *) source;
    return *size;
}

int check_input(char *substance, int length) {
    // A index B public C signature transaction
    int *A, *B, *C;

    if (length < 4) {
        return 0;
    }

    A = (int *) substance;
    if (length < 12) {
        return 0;
    }

    B = (int *) (substance + 8);
    if (length < 16 + *B) {
        return 0;
    }

    C = (int *) (substance + 12 + *B);

    if (*A != length) {
        return 0;
    }
    if (*B + *C + 48 != length) {
        return 0;
    }

    return 1;
}

int check_output(char *substance, int length) {
    int *A, *B;

    if (length < 8) {
        return 0;
    }

    A = (int *) substance;
    B = (int *) (substance + 4);

    if (*A != length) {
        return 0;
    }

    if (*B + 8 + 8 != length) {
        return 0;
    }
    return 1;
}

int check_transaction(char *substance, int length) {
    // A B C Input Output
    int *A, *B, *C;
    int count, cursor, jump;

    if (length < 12) {
        return 0;
    }

    A = (int *) substance;
    B = (int *) substance + 4;
    C = (int *) substance + 8;

    if (*A != length) {
        return 0;
    }

    // check every input
    cursor = 12;
    for (count = *B; count > 0; count--) {
        if (length < cursor + 4) {
            return 0;
        }
        jump = scan(substance + cursor);

        if (length < cursor + jump) {
            return 0;
        }

        if (!check_input(substance + cursor, jump)) {
            return 0;
        }
        cursor += jump;
    }

    // check every output
    for (count = *C; count > 0; count--) {
        if (length < cursor + 4) {
            return 0;
        }
        jump = scan(substance + cursor);

        if (length < cursor + jump) {
            return 0;
        }

        if (!check_output(substance + cursor, jump)) {
            return 0;
        }

        cursor += jump;
    }

    return 0;
}

