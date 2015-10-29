#include <sys/types.h>
#include <pwd.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define TRUE 1
#define MAX_COMMAND_LEN 100
#define MAX_PAR_CNT 15
#define MAX_HOSTNAME_LEN 10
#define MAX_PATH_LEN 100

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

void type_promt()
{
	uid_t uid = getuid();
	struct passwd *pwd = getpwuid(uid);
	char *uname = pwd -> pw_name;
	char *uPath = pwd -> pw_dir;
	char hname[MAX_HOSTNAME_LEN];
	char abPath[MAX_PATH_LEN];
	gethostname(hname, MAX_HOSTNAME_LEN);
	getcwd(abPath, MAX_PATH_LEN);
	int uPathLen = strlen(uPath);
	char path[MAX_PATH_LEN];
	if(strncmp(uPath, abPath, uPathLen) == 0){
		path[0] = '~';
		strcpy(path + 1, abPath + uPathLen);
	}
	else{
		strcpy(path, abPath);
	}
	int isRoot = (geteuid() == 0);
	printf("[cShell]%s@%s:%s%c ", uname, hname, path, (isRoot ? '#' : '$'));
	return;
}

int read_command(char *command, char *parameters[])
{
	int cnt, len, i;
	gets(command);
	cnt = 0;
	parameters[0] = command;
	len = strlen(command);
	for(i=0;i<len;i++){
		if(command[i] == ' '){
			command[i] = 0;
			parameters[++cnt] = command+i+1;
		}
		
	}
	parameters[++cnt] = NULL;
	return cnt;
}

int buildin_command(char *command, char *parameters[])
{
	if(strcmp(command, "exit") == 0 || strcmp(command, "quit") == 0){
		exit(0);
	}
	else if(strcmp(command, "cd") == 0){
		if(parameters[1][0] == '~'){
			uid_t uid = getuid();
			struct passwd *pwd = getpwuid(uid);
			char *uPath = pwd -> pw_dir;
			int uPathLen = strlen(uPath);
			int parLen = strlen(parameters[1]);
			char *path = malloc((uPathLen + parLen) * sizeof(char));
			strcpy(path, uPath);
			strcpy(path + uPathLen, parameters[1] + 1);
			chdir(path);
			free(path);
		}
		else{
			chdir(parameters[1]);
		}
		return 1;
	}
	return 0;
}
