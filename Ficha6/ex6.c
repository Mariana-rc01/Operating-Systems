#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

/*
#comandos = c
#pipes = c - 1
*/
int main(int argc, char* argv[]){

    int pipe_fd[3][2];

    if(pipe(pipe_fd[0]) < 0){
        perror("pipe0");
        return 1;
    }

    // prepare grep
    // pipes: pipe_fd[0][1]
    if (fork() == 0){
        close(pipe_fd[0][0]);
        
        dup2(pipe_fd[0][1],STDOUT_FILENO);
        close(pipe_fd[0][1]);

        execlp("grep","grep","-v","^#","/etc/passwd", NULL);
        _exit(1);
    }

    close(pipe_fd[0][1]);

    if(pipe(pipe_fd[1]) < 0){
        perror("pipe1");
        return 1;
    }

    // prepare cut
    // pipes: pipe_fd[0][0], pipe_fd[1][1]
    if (fork() == 0){
        close(pipe_fd[1][0]);

        dup2(pipe_fd[1][1],STDOUT_FILENO);
        close(pipe_fd[1][1]);

        dup2(pipe_fd[0][0],STDIN_FILENO);
        close(pipe_fd[0][0]);

        execlp("cut","cut","-f7","-d:", NULL);
        _exit(2);
    }

    close(pipe_fd[0][0]);
    close(pipe_fd[1][1]);

    if(pipe(pipe_fd[2]) < 0){
        perror("pipe2");
        return 1;
    }

    // prepare uniq
    // pipes: pipe_fd[2][1], pipe_fd[1][0]
    if (fork() == 0){
        close(pipe_fd[2][0]);
        dup2(pipe_fd[2][1],STDOUT_FILENO);
        close(pipe_fd[2][1]);
        
        dup2(pipe_fd[1][0],STDIN_FILENO);
        close(pipe_fd[1][0]);

        execlp("uniq","uniq", NULL);
        _exit(3);
    }

    close(pipe_fd[1][0]);
    close(pipe_fd[2][1]);

    // prepare wc
    // pipes: pipe_fd[2][0]
    if (fork() == 0){
        
        dup2(pipe_fd[2][0],STDIN_FILENO);
        close(pipe_fd[2][0]);

        execlp("wc","wc","-l", NULL);
        _exit(4);
    }

    close(pipe_fd[2][0]);

    for (int i = 0; i < 4; i++){
        wait(NULL);
    }

    write(STDOUT_FILENO, "Fim\n", 4);
    return 0;
}

/*
Sendo C o nº de comandos
pipe_fd[C-1][2]

        1º         2º..N-1     N
Stdin: -------    C-1  ....    C-1   [0]
Stdout: C          C   ....    ----- [1]

podemos usar sprintf
*/