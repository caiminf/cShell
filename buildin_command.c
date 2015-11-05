#include <sys/types.h>
#include <pwd.h>
#include <string.h>
#include <stdlib.h>
#include "cShell.h"

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

