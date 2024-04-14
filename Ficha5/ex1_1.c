#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>

int main(int argc, char* argv[]){

    if (mkfifo("fifo", 0644) < 0){
        perror("mkfifo");
    }

    return 0;
}
