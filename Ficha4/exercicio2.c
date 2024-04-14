#include <unistd.h>
#include <stdio.h>

/*int main(int argc, char* argv[]){

    int pipe_fd[2];
    pipe(pipe_fd);

    if (fork() == 0){
        close(pipe_fd[0]);
        for (int i = 0; i < 100000; i++){
            write(pipe_fd[1],&i,sizeof(int));
            printf("Write %d\n",i);
        }
        _exit(0);
    }
    
    close(pipe_fd[1]);
    for (int j = 0; j < 100000; j++){
        sleep(2);
        read(pipe_fd[0],&j,sizeof(int));
        printf("Read %d\n",j);
    }

    return 0;
}*/

int main(int argc, char* argv[]){

    int pipe_fd[2];
    pipe(pipe_fd);

    if (fork() == 0){
        close(pipe_fd[0]);
        for (int i = 0; i < 10; i++){
            write(pipe_fd[1],&i,sizeof(int));
            printf("Write %d\n",i);
        }
        close(pipe_fd[1]);
        _exit(0);
    }
    
    close(pipe_fd[1]);
    int j = 0;
    while(read(pipe_fd[0],&j,sizeof(int)) != 0){
        printf("Read %d\n",j);
    }

    return 0;
}