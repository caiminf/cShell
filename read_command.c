#include <string.h>
#include "cShell.h"

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

