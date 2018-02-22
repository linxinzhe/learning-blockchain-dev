#include "tomcrypt.h"
#include <stdio.h>
#include <stdlib.h>

char *get_file(char *path){
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

int main(){
    printf("hello world");
};