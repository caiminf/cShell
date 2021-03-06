#ifndef CSHELL_H_
#define CSHELL_H_

#define TRUE 1
#define MAX_COMMAND_LEN 100
#define MAX_PAR_CNT 15
#define MAX_HOSTNAME_LEN 10
#define MAX_PATH_LEN 100

#define OUT_REDIRECT 1
#define OUT_REDIRECT_APPEND 2
#define IN_REDIRECT 4
#define IS_PIPED 8

struct command_info{
	int flag;
	char *out_file;
	char *in_file;
	char *command2;
	char **parameters2;
};

#endif
