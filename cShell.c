#include <sys/types.h>
#include <unistd.h>
#include "cShell.h"

void type_promt();
int read_command(char *command, char *parameters[]);
int buildin_command(char *command, char *parameters[]);

int main()
{
	char command[MAX_COMMAND_LEN];
	char *parameters[MAX_PAR_CNT];
	int status;
	pid_t childPid;
	while(TRUE){
		type_promt();
		int cnt = read_command(command, parameters);
		if(buildin_command(command, parameters))
			continue;
		if((childPid = fork()) != 0){
			waitpid(childPid, &status, 0);
		}
		else{
			execvp(command, parameters);
		}
	}
	return 0;
}
