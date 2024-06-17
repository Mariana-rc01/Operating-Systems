#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

// end of file -> ctrl + D
int main(int argc, char* argv[]){

    int pipe_fd[2];
    if(pipe(pipe_fd) < 0){
        perror("pipe");
        return 1;
    }

    if (fork() == 0){
        // leitura aberto
        close(pipe_fd[1]);
        dup2(pipe_fd[0],STDIN_FILENO);
        close(pipe_fd[0]);

        execlp("wc","wc",NULL);
        _exit(1);
    }

    close(pipe_fd[0]);

    int res = 0;
    char buffer[1024];

    while((res = read(0,buffer,1024)) > 0){
        write(pipe_fd[1],buffer,res);
    }

    close(pipe_fd[1]);

    wait(NULL);

    write(STDOUT_FILENO, "Fim\n", 4);
    return 0;
}
