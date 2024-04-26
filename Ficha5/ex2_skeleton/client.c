#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include "defs.h"
#include <string.h>

/*
typedef struct msg{
    int needle; // nº que queremos procurar
    int pid; // pid do processo (identificador)
    int occurrences; // resultado
} Msg;
*/

char* concat1(const char *s1, int num) {
    int len = snprintf(NULL, 0, "%s%d", s1, num);

    char *result = (char*)malloc(len + 1);

    snprintf(result, len + 1, "%s%d", s1, num);

    return result;
}

int main (int argc, char* argv[]){

	if (argc < 2) {
		printf("Missing argument.\n");
		_exit(1);
	}

	Msg msg = {atoi(argv[1]),getpid(),0};

	char* nome = concat1("fifo_",getpid());
	
	if (mkfifo(nome, 0666) < 0){
        perror("mkfifo client");
		return -1;
    }

	int fifo_server = open(SERVER,O_WRONLY);
	if(write(fifo_server,&msg, sizeof(Msg)) == -1){
		perror("write");
		return -1;
	}
	close(fifo_server);

	int fifo_c = open(nome, O_RDONLY);

	int read_bytes;
	Msg msg1;
    while ((read_bytes = read(fifo_c, &msg1, sizeof(Msg))) > 0){
		printf("%d\n",msg1.occurrences);
    }

	close(fifo_c);
	
	return 0;
}

