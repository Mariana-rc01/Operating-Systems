// Operating systems capa de dinossauros

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024

int main (int agrc, char const *argv[]){
    char* c = malloc(sizeof(char)*128);
    int bytes_read;
    while ((bytes_read = read(0 /* STDIN_FILENO */, &c, sizeof(c))) > 0){
        int bytes_written = write(1 /* STDOUT_FILENO */, &c, bytes_read);
        printf("DEBUG write: %d bytes\n", bytes_written);
    }
    return 0;
}

// Versão do professor:
ssize_t mycat(){
    char *buffer = (char*)malloc(sizeof(char) * BUFFER_SIZE);

    ssize_t write_bytes = 0;
    ssize_t read_bytes = 0;
    ssize_t bytes = 0;

    while((bytes = read(0, buffer, BUFFER_SIZE)) > 0){
        read_bytes += bytes;
        write_bytes += write(1, buffer, bytes);
    }

    free(buffer);

    if((write_bytes - read_bytes) == 0) return 0;

    return -1;
}