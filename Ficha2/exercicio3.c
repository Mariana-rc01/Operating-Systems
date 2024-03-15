#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <sys/wait.h>
#include <stdio.h>

int main(){

    // primeiro faz um filho, depois ele termina, depois cria-se outro, etc usando for

    int status;
    int i = 0;
    pid_t child_pid;
    pid_t wait_pid;

    printf("pid do pai: %d\n", getpid());
    printf("parent pid do pai: %d\n", getppid()); //parent pid

    for (i = 1; i < 11; i++){
        if (child_pid = fork() == 0){
            printf("pid do filho: %d\n", getpid());
            printf("parent pid do filho: %d\n", getppid()); //parent pid
            printf("Ordem do filho: %d\n",i);
            _exit(i);
        }
        else {
            wait_pid = wait(&status);
            if (WIFEXITED(status)){
                printf("Código de saída: %d\n", WEXITSTATUS(status));
            }
            else {
                printf("Não esperou pelo filho\n");
            }
        }
    }
    
    return 0;
}