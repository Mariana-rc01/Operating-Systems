#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <sys/wait.h>
#include <stdio.h>

int main(){

    printf("pid: %d\n", getpid());
    printf("parent pid: %d\n", getppid()); //parent pid

    return 0;
}