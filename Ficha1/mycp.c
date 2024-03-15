#include <stdio.h>
#include <sys/types.h>
#include <sys/resource.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <linux/time.h>


int main (int agrc, char const *argv[]){
    struct timespec start, end;
    double time;
    clock_gettime(CLOCK_REALTIME,&start);

    int leitura = open(argv[1], O_RDWR, 0600);
    int escrita = open(argv[2], O_CREAT | O_TRUNC | O_RDWR, 0600);
    char* c = malloc(sizeof(char)*128);
    int bytes_read;
    while ((bytes_read = read(leitura, &c, sizeof(c))) > 0){
        int bytes_written = write(escrita , &c, bytes_read);
        printf("DEBUG write: %d bytes\n", bytes_written);
    }

    clock_gettime(CLOCK_REALTIME, &end);
    time = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
    printf("Demorou %f segundos a copiar o ficheiro\n", time);
    return 0;
}

// Versão do professor:
ssize_t mycp(char const* from_path, char const* to_path, int buffer_size){
    int from_fd = open(from_path, O_RDONLY);

    int to_fd = open(to_path, O_CREAT | O_TRUNC | O_WRONLY, 0644);

    char* buffer = malloc(sizeof(char)*buffer_size);

    ssize_t write_bytes = 0;
    ssize_t read_bytes = 0;
    ssize_t bytes = 0;
    int nsyscalls = 0;

    while((bytes = read(from_fd, &buffer, buffer_size)) > 0){
        read_bytes += bytes;
        write_bytes += write(to_fd, buffer, bytes);
        nsyscalls += 2;
    }

    free(buffer);

    if((write_bytes - read_bytes) == 0) return 0;

    return -1;
}