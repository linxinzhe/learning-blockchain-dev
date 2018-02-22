#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main() {
    int s;
    struct sockaddr_in a;

    s = socket(2, 1, 0);  //second param - 1:tcp 2:udp
    if (s == -1) {
        exit(1);
    }

    // 127.0.0.1:6001
    a.sin_family = 2;
    a.sin_port = htons(6000);
    a.sin_addr.s_addr = inet_addr("127.0.0.1");

    int f = connect(s, (struct sockaddr *) &a, sizeof(a));
    if (f == -1) {
        exit(2);
    }

    send(s, "hello ", 6, 0);
    send(s, "my ", 3, 0);
    send(s, "name ", 5, 0);
    send(s, "is ", 3, 0);
    send(s, "linxinzhe", 9, 0);


}

