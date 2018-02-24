#include <unistd.h>

int main() {
    // Linux System Call: open, read, write,
    // Function Manual. In BASH: man 2 write
    write(1,"Hello",5); // 1 stands for stdout
    return 0;
}