#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>


#define MAX_COMMANDS 10

// parse do argumento e execvp
// devolve o resultado do exec
int exec_command(char* arg){

	//Estamos a assumir numero maximo de argumentos
	char* exec_args[10];

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


int main(int argc, char** argv){
	
	int number_of_commands = 4;
	
	char* commands[] = {
		"grep -v ^# /etc/passwd",
		"cut -f7 -d:",
		"uniq",
		"wc -l"
	};

	int pipes[number_of_commands-1][2];
	int status[number_of_commands];

	for (int c = 0; c < number_of_commands; c++){
		if (c == 0){
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
		else if (c == number_of_commands -1){

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
					close(pipes[c-1][0]);
			}
		}
		else{
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

	for (int i = 0; i <number_of_commands; i++){
		wait(&status[i]);
	}

	return 0;
}

