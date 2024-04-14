#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char* argv[]){
    printf("read_fifo before open\n");

    int fifo_fd = open("fifo", O_RDONLY);
    
    printf("read_fifo after open\n");
    
    char buffer[10];
    int read_bytes = 0;
    while ((read_bytes = read(fifo_fd, buffer, 10)) > 0){
        write(1, buffer, read_bytes);
    }

    close(fifo_fd);


    return 0;
}