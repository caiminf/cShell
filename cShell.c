#include <sys/types.h>
#include <pwd.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#define TRUE 1
#define MAX_COMMAND_LEN 100
#define MAX_PAR_CNT 15

void type_promt();
int read_command(char *command, char *parameters[]);

int main()
{
	char command[MAX_COMMAND_LEN];
	char *parameters[MAX_PAR_CNT];
	int status;
	pid_t childPid;
	while(TRUE){
		type_promt();
		int cnt = read_command(command, parameters);
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
	char hname[10];
	gethostname(hname, 10);
	char abPath[30];
	getcwd(abPath, 30);
	int uPathLen = strlen(uPath);
	char path[30];
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
