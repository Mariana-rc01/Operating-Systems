#include <stdio.h>
#include "mysystem.h"

void controller(int N, char** commands) {
	for (int i = 0; i < N; i++){
		int return_value = mysystem(commands[i]);
		_exit(return_value);
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