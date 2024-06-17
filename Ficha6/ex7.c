#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>

#include <sys/time.h>

#define MAX_COMMANDS 10

int exec_command_flag_u(char* arg, int id, char* pathOutput) {

    char* exec_args[MAX_COMMANDS];

    char* string;
    int exec_ret = 0;
    int i = 0;

    char* command = strdup(arg);

    string = strtok(command, " ");

    while (string != NULL) {
        exec_args[i] = string;
        string = strtok(NULL, " ");
        i++;
    }

    exec_args[i] = NULL;

    char output_file[50];
    sprintf(output_file, "%s/output_%d.txt", pathOutput, id);

    int output_fd = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0666);
    if (output_fd == -1) {
        perror("Error opening output file");
        exit(EXIT_FAILURE);
    }

    if (dup2(output_fd, STDOUT_FILENO) == -1) {
        perror("Error redirecting stdout");
        exit(EXIT_FAILURE);
    }

    if (dup2(output_fd, STDERR_FILENO) == -1) {
        perror("Error redirecting stderr");
        exit(EXIT_FAILURE);
    }

    exec_ret = execvp(exec_args[0], exec_args);

    close(output_fd);

    return exec_ret;
}

char** splitString(char* string, char* delimiter, int* num_commands) {
    char** args = malloc(300 * sizeof(char*));
    if (args == NULL) {
        perror("Error allocating memory");
        exit(EXIT_FAILURE);
    }

    int i = 0;

    char* copy = strdup(string);
    if (copy == NULL) {
        perror("Error duplicating string");
        exit(EXIT_FAILURE);
    }

    char* token = strtok(copy, delimiter);

    while (token != NULL) {
        args[i] = strdup(token);
        if (args[i] == NULL) {
            perror("Error allocating memory");
            exit(EXIT_FAILURE);
        }

        i++;

        token = strtok(NULL, delimiter);
    }

    free(copy);

    *num_commands = i;

    return args;
}

int exec_command(char* arg){

    //Estamos a assumir numero maximo de argumentos
    char* exec_args[MAX_COMMANDS];

    char* string;
    int exec_ret = 0;
    int i=0;

    char* command = strdup(arg);

    string = strtok(command," ");
    
    while(string != NULL){
        exec_args[i] = string;
        string = strtok(NULL," ");
        i++;
    }

    exec_args[i] = NULL;
    
    exec_ret = execvp(exec_args[0],exec_args);
    
    return exec_ret;
}

int exec_pipeline(char* arg, int id,char* pathOutput){
    
    int number_of_commands = 0;

    char** commands = splitString(arg, "|", &number_of_commands);

    int pipes[number_of_commands-1][2];
    int status[number_of_commands];

    for (int c = 0; c < number_of_commands; c++){
        if (c == 0){ // 1º
            if (pipe(pipes[c]) != 0){
                perror("pipe");
                return 1;
            }

            switch(fork()){
                case -1:
                    perror("fork");
                    return -1;

                case 0:

                    close(pipes[c][0]);

                    dup2(pipes[c][1],1);

                    exec_command(commands[c]);

                    _exit(0);

                default:
                    close(pipes[c][1]);
            }

        
        }
        else if (c == number_of_commands - 1){ // último

            switch(fork()){
                case -1:
                    perror("fork");
                    return -1;

                case 0:

                    close(pipes[c][0]);

                    dup2(pipes[c][1],1);
                    close(pipes[c][1]);

                    dup2(pipes[c-1][0],0);
                    close(pipes[c-1][0]);

                    char output_file[50];
                    sprintf(output_file, "%s/output_%d.txt", pathOutput, id);
                    int output_fd = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0666);
                    if (output_fd == -1) {
                        perror("Error opening output file");
                        exit(EXIT_FAILURE);
                    }
                    // Redirecionar stdout e stderr para o arquivo
                    dup2(output_fd, STDOUT_FILENO);
                    dup2(output_fd, STDERR_FILENO);

                    exec_command(commands[c]);
                    _exit(0);

                default:
                    close(pipes[c-1][0]);
            }
        }
        else{ // intermédios
            if (pipe(pipes[c]) != 0){
                perror("pipe");
                return 1;
            }

            switch(fork()){
                case -1:
                    perror("fork");
                    return -1;

                case 0:

                    close(pipes[c][0]);

                    dup2(pipes[c][1],1);
                    close(pipes[c][1]);

                    dup2(pipes[c-1][0],0);
                    close(pipes[c-1][0]);

                    exec_command(commands[c]);
                    _exit(0);

                default:
                    close(pipes[c][1]);
                    close(pipes[c-1][0]);
            }
        }
    }

    for (int i = 0; i < number_of_commands; i++){
        wait(&status[i]);
    }

    return 0;
}


int main(int argc, char** argv){

    // Declare as variáveis time_start e time_end
    struct timeval time_start, time_end;

    // Obtenha o tempo inicial
    int start = gettimeofday(&time_start, NULL);

    // Execute sua tarefa aqui

    char commands[] = "grep -v ^# /etc/passwd | cut -f7 -d: | uniq |wc -l";
    char commands1[] = "ls -l";

    int valor = exec_pipeline(commands, 100, "tmp");

    int valor1 = exec_command_flag_u(commands1, 5, "tmp");

    // Obtenha o tempo final
    int end = gettimeofday(&time_end, NULL);

    printf("Tempo decorrido: %d %d ms\n", start,end);
    return 0;

}