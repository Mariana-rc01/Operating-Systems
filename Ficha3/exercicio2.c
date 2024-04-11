#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>


int main(int argc, char* argv[]){

    int pid;
    if (pid = fork() == 0) {
        // 1ª forma
        int return_value = execl("/bin/ls","ls","-l",NULL);
        _exit(return_value);

        // 2ª forma
        //int return_value = execlp("/ls","ls","-l",NULL);

        // 3ª forma
        /*char* exec_args[] = {
            "/bin/ls",
            "-l",
            NULL
        };
        int return_value = execv(exec_args[0],exec_args);*/
    }


    int status = 0;
    wait(&status);
    if (WIFEXITED(status)){
        // o printf nao aparece porque o programa sai daqui
        printf("Return value: %d\n",WEXITSTATUS(status));
    }

    return 0;
}
