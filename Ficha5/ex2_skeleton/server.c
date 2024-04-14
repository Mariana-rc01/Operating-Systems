#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include "defs.h"
#include "vector.h"

//FIFO criado pelo servidor
//Cliente pode receber um sigpipe (concorrência!)
char* concat1(const char *s1, int num) {
    int len = snprintf(NULL, 0, "%s%d", s1, num);

    char *result = (char*)malloc(len + 1);

    snprintf(result, len + 1, "%s%d", s1, num);

    return result;
}

int main (int argc, char * argv[]){

	init_vector();
	print_vector();

	if (mkfifo(SERVER, 0644) < 0){
        perror("mkfifo");
    }

	int fifo_fd = open(SERVER, O_RDONLY);
	int fifo_write = open(SERVER, O_WRONLY);

    int read_bytes = 0;
	Msg msg;
    while ((read_bytes = read(fifo_fd, &msg, sizeof(Msg))) > 0){
        
		char* client = concat1("fifo_",msg.pid);
		
		if (mkfifo(client, 0644) < 0){
        	perror("mkfifo");
    	}

		printf("%d\n",msg.pid);
		printf("%d\n",msg.needle);

		int fifo_c = open(client, O_WRONLY);
		msg.occurrences = count_needle(msg.needle);
		printf("%d\n",msg.occurrences);
		write(fifo_c, &msg, sizeof(Msg));

		close(fifo_c);
    }


    close(fifo_fd);
	
	return 0;
}
