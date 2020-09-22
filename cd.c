#include "header.h"

ll CD(char **com)
{
    char cwd[1024];
    getcwd(cwd,sizeof(cwd));

    if (strcmp(com[1],"-") == 0)
    {
        printf("%s\n",lwd);
        
        if(chdir(actual_path(lwd))==-1)
            perror("lwd error");
        strcpy(lwd,relative_path(cwd));
        return 0;
    }

    char *path = actual_path(com[1]);
    if (chdir(path) == -1)
    {
        perror("CD error");
        return -1;
    }

    strcpy(lwd,relative_path(cwd));

    return 0;
}