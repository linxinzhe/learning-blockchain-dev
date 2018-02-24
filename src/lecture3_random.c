#include <stdio.h>
#include <fcntl.h>
#include <zconf.h>

int main() {
    int a;
    char b[100];

    a = open("/dev/urandom", O_RDONLY);   // read random raw bytes from linux
    printf("%d%c", a, 10);

    read(a, b, 20);

    return 0;
}