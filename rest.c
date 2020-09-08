#include "header.h"

ll REST(char**com, ll bg)
{
    ll len=0;

    while (com[len]!=NULL)
        len++;
    if (strcmp(com[len-1],"&")==0)
    {
        bg=1;
        com[len-1]=NULL;
        len--;
    }

    pid_t pid=fork();

    if (pid<0)
    {
        perror("Error");
        exit(EXIT_FAILURE);
    }
    if (pid==0)
    {
        ll ret = execvp(com[0],com);
        if (ret<0)
        {
            perror("Command not found");
            exit(EXIT_FAILURE);
        }
    }

    if (bg==0)
    {
        ll status;
        pid_t wpid = waitpid(pid,&status,WUNTRACED);
        
    
    }


}