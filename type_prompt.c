#include <sys/types.h>
#include <pwd.h>
#include <stdio.h>
#include <string.h>
#include "cShell.h"

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

