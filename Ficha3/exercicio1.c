#include <unistd.h>
#include <stdio.h>

int main(int argc, char* argv[]){

    // 1ª forma
    //int return_value = execl("/bin/ls","ls","-l",NULL);

    // 2ª forma
    //int return_value = execlp("/ls","ls","-l",NULL);

    // 3ª forma
    char* exec_args[] = {
        "/bin/ls",
        "-l",
        NULL
    };
    int return_value = execv(exec_args[0],exec_args);


    // o printf nao aparece porque o programa sai daqui
    printf("Return value: %d\n",return_value);

    return 0;
}
