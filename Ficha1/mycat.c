// Operating systems capa de dinossauros

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

int main (int agrc, char const *argv[]){
    char* c = malloc(sizeof(char)*128);
    int bytes_read;
    while ((bytes_read = read(0 /* STDIN_FILENO */, &c, sizeof(c))) > 0){
        int bytes_written = write(1 /* STDOUT_FILENO */, &c, bytes_read);
        printf("DEBUG write: %d bytes\n", bytes_written);
    }
    return 0;
}