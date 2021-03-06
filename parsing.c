#include <string.h>
#include "cShell.h"

void command_info_init(struct command_info * info)
{
	info->flag = 0;
	info->out_file = NULL;
	info->in_file = NULL;
}

void parsing(char *parameters[], int par_cnt, struct command_info * info)
{
	int i;
	command_info_init(info);
	for(i=0;i<par_cnt;i++){
		if(strcmp(parameters[i], ">") == 0){
			info->flag |= OUT_REDIRECT;
			info->out_file = parameters[i+1];
			parameters[i] = NULL;
		}
		else if(strcmp(parameters[i], ">>") == 0){
			info->flag |= OUT_REDIRECT_APPEND;
			info->out_file = parameters[i+1];
			parameters[i] = NULL;
		}
		else if(strcmp(parameters[i], "<") == 0 || strcmp(parameters[i], "<<") == 0){
			info->flag |= IN_REDIRECT;
			info->in_file = parameters[i+1];
			parameters[i] = NULL;
		}
		else if(strcmp(parameters[i], "|") == 0){
			info->flag != IS_PIPED;
			info->command2 = parameters[i+1];
			parameters[i] = NULL;
			info->parameters2 = parameters + i + 1;
		}
	}
}
