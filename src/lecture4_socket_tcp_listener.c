#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <memory.h>
// BASH: nc 127.0.0.1 6000
// c program run with args: port
int main(int count, char **arguments) {
    int s, error, length, opponent;
    struct sockaddr_in a;
    char buffer[1000];

    if (count != 2) {
        printf("error: there must be two arguments%c", 10);
        exit(3);
    }

    s = socket(2, 1, 0);  //second param - 1:tcp 2:udp
    if (s == -1) {
        exit(1);
    }

    // 0.0.0.0:8004
    a.sin_family = 2;
    a.sin_port = htons(atoi(arguments[1]));
    a.sin_addr.s_addr = inet_addr("0.0.0.0");

    error = bind(s, (struct sockaddr *) &a, sizeof(a));
    if (error == -1) {
        exit(1);
    }


    error = listen(s, 1024);
    if (error == -1) {
        exit(1);
    }
    opponent = accept(s, 0, 0);
    if (opponent == -1) {
        exit(1);
    }

    while (1) {
        memset(buffer, 0, 1000);
        length = recv(opponent, buffer, 1000, 0);
        if (length == -1 || length == 0) {
            break;
        }
        printf("%s", buffer);
    }
}

