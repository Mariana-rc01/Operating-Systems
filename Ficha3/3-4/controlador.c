#include <stdio.h>
#include "mysystem.h"

void controller(int N, char** commands) {
	int child_pid, acc = 0;
	for (int i = 0; i < N; i++){
		if ((child_pid = fork()) == 0){
			int return_value = 1, acc = 0;
			while (return_value != 0){
				return_value = mysystem(commands[i]);
				acc++;
			}
			_exit(acc);
		}
	}


	for (int i = 0; i < N; i++){
		int status;
		wait(&status);
		if (WIFEXITED(status)){
			printf("Número: %d\n", WEXITSTATUS(status));
		}
	}
}

int main(int argc, char* argv[]) {

    char *commands[argc-1];
    int N = 0;
	for(int i=1; i < argc; i++){
		commands[N] = strdup(argv[i]);
		printf("command[%d] = %s\n", N, commands[N]);
        N++;
	}

    controller(N, commands);

	return 0;
}