#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include "cShell.h"

void type_promt();
int read_command(char *command, char *parameters[]);
int buildin_command(char *command, char *parameters[]);
void parsing(char *parameters[], int par_cnt, struct command_info * info);

int main()
{
	char command[MAX_COMMAND_LEN];
	char *parameters[MAX_PAR_CNT];
	int status;
	int out_fd;
	while(TRUE){
		type_promt();
		int cnt = read_command(command, parameters);
		struct command_info info;
		parsing(parameters, cnt, &info);
		if(buildin_command(command, parameters))
			continue;
		if(fork() != 0){
			wait(NULL);
		}
		else{
			if(info.flag & OUT_REDIRECT){
				out_fd = open(info.out_file, O_WRONLY|O_CREAT|O_TRUNC, 0666);
				close(fileno(stdout)); 
				dup2(out_fd, fileno(stdout));
				close(out_fd);
			}
			if(info.flag & OUT_REDIRECT_APPEND){
				out_fd = open(info.out_file, O_WRONLY|O_APPEND|O_TRUNC, 0666);
				close(fileno(stdout));
				dup2(out_fd, fileno(stdout));
				close(out_fd);
			}
			execvp(command, parameters);
		}
	}
	return 0;
}
