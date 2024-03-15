#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <sys/wait.h>
#include <stdio.h>

int main(){

    int status;
    pid_t child_pid;

    printf("pid do pai: %d\n", getpid());
    printf("parent pid do pai: %d\n", getppid()); //parent pid

    if(child_pid = fork() == 0){
        //processo filho
        printf("pid do filho: %d\n", getpid());
        printf("parent pid do filho: %d\n", getppid()); //parent pid
        _exit(0);
    }

    pid_t wait_pid = wait(&status);

    if (WIFEXITED(status)){
        // saiu bem, usou o exit(0)
        printf("wait status of pid [%d]: %d\n", wait_pid, WEXITSTATUS(status));
        // o número que aparece no WEXITSTATUS(status) é o valor que demos no exit(x), sendo x um número inteiro, nao sendo
        // necessário ser 0
    }
    else {
        printf("execution error\n");
    }


    return 0;
}