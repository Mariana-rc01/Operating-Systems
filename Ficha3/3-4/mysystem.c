#include "mysystem.h"


// recebe um comando por argumento
// returna -1 se o fork falhar
// caso contrario retorna o valor do comando executado
int mysystem (const char* command) {

	int res = -1;
	char* exec_args[20];
	int i = 0;
	char* in_Ptr = strdup(command);
	char* token;
	while ((token = strsep(&in_Ptr," ")) != NULL) {
		exec_args[i] = strdup(token);
		//printf("%s\n",exec_args[i]);
		i++;
	}
	exec_args[i] = NULL;

	int child_pid;
	if ((child_pid = fork()) == 0){
		int return_value = execvp(exec_args[0],exec_args);
		_exit(return_value);
	}
	else if (child_pid < 0){
		return res;
	}
	else{
		int status;
		wait(&status);
		if (WIFEXITED(status)){
			res = WEXITSTATUS(status);
		}
	}

	free(token);

	return res;
}

