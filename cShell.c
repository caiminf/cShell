#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
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
	int out_fd, in_fd;
	pid_t child_id1, child_id2;
	while(TRUE){
		int pipe_id[2];
		type_promt();
		int cnt = read_command(command, parameters);
		struct command_info info;
		parsing(parameters, cnt, &info);
		if(buildin_command(command, parameters))
			continue;
		if(info.flag & IS_PIPED){
			pipe(pipe_id);
		}
		if((child_id1 = fork()) != 0){//shell
			if(info.flag & IS_PIPED){
				if((child_id2 = fork()) != 0){//shell
					close(pipe_id[0]);
					close(pipe_id[1]);
					waitpid(child_id2, NULL, 0);//wait command2
				}
				else{//command2
					close(pipe_id[1]);
					close(fileno(stdin));
					dup2(pipe_id[0], fileno(stdin));
					close(pipe_id[0]);
					execvp(info.command2, info.parameters2);
				}
			}
			waitpid(child_id1, NULL, 0);//wait command1
		}
		else{//command1
			if(info.flag & OUT_REDIRECT){
				out_fd = open(info.out_file, O_WRONLY|O_CREAT|O_TRUNC, 0666);
				close(fileno(stdout)); 
				dup2(out_fd, fileno(stdout));
				close(out_fd);
			}
			if(info.flag & OUT_REDIRECT_APPEND){
				out_fd = open(info.out_file, O_WRONLY|O_APPEND, 0666);
				close(fileno(stdout));
				dup2(out_fd, fileno(stdout));
				close(out_fd);
			}
			if(info.flag & IN_REDIRECT){
				in_fd = open(info.in_file, O_RDONLY, 0666);
				close(fileno(stdin));
				dup2(in_fd, fileno(stdin));
				close(in_fd);
			}
			if(info.flag & IS_PIPED){
				close(pipe_id[0]);
				close(fileno(stdout));
				dup2(pipe_id[1], fileno(stdout));
				close(pipe_id[1]);
			}
			execvp(command, parameters);
		}
	}
	return 0;
}
