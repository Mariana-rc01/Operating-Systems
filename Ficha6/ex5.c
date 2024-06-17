#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char* argv[]){


    int pipe_fd[2];
    if(pipe(pipe_fd) < 0){
        perror("pipe");
        return 1;
    }

    if (fork() == 0){
        close(pipe_fd[0]);
        dup2(pipe_fd[1],STDOUT_FILENO);
        close(pipe_fd[1]);

        execlp("ls","ls","/etc", NULL);
        _exit(1);
    }

    close(pipe_fd[1]);

    if (fork() == 0){
        dup2(pipe_fd[0],STDIN_FILENO);
        close(pipe_fd[0]);

        execlp("wc","wc","-l", NULL);
        _exit(1);
    }

    close(pipe_fd[0]);

    wait(NULL);
    wait(NULL);

    write(STDOUT_FILENO, "Fim\n", 4);
    return 0;
}
