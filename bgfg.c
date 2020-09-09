#include "header.h"

// Gives msg to user if background process is exited
void handler(int signal)
{
    printf("\033[1;31m suspend\n");
}

ll BGFG(char**com, ll bg)
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
        perror("Forking Error");
        exit(EXIT_FAILURE);
    }
    else if (pid==0)
    {
        ll ret = execvp(com[0],com);
        if (ret<0)
        {
            perror("Command invalid");
            exit(EXIT_FAILURE);
        }
    }

    else
    {
        if (bg==0)
        {
            ll status;
            // pid_t wpid = waitpid(pid,&status,WUNTRACED);
            

        }
    }


}