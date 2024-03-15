#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <sys/wait.h>
#include <stdio.h>

int main(){

    // cria 10 de uma vez e espera 10 vezes por todos
    int status;
    int i = 0;
    pid_t child_pid;
    pid_t wait_pid;
    int statuss[10] = {0};

    printf("pid do pai: %d\n", getpid());
    printf("parent pid do pai: %d\n", getppid()); //parent pid

    for (i = 0; i < 10; i++){
        if (child_pid = fork() == 0){
            printf("pid do filho: %d\n", getpid());
            printf("parent pid do filho: %d\n", getppid()); //parent pid
            printf("Ordem do filho: %d\n",i+1);
            _exit(i+1);
        }
    }

    for (i = 0; i < 10; i++){
        wait_pid = wait(&status);
        statuss[i] = WEXITSTATUS(status);
    }

    for (i = 0; i < 10; i++){
        if (WIFEXITED(status)){
            printf("Código de saída: %d\n", statuss[i]);
        }
        else {
            printf("Não esperou pelo filho\n");
        }
    }

    return 0;
}