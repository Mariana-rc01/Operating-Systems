#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char* argv[]){
    printf("write_fifo before open\n");

    int fifo_fd = open("fifo", O_WRONLY);
    
    printf("write_fifo after open\n");

    char buffer[10];
    int read_bytes = 0;
    while ((read_bytes = read(0, buffer, 10)) > 0){
        write(fifo_fd,buffer, read_bytes);
    }

    // read from stdin
    // write for fifo

    close(fifo_fd);


    return 0;
}