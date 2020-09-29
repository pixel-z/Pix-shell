#include "header.h"

void EXIT_STAT()
{
    int stat;
    pid_t pid = waitpid(-1,&stat,WNOHANG);
    if (pid >0 && WIFEXITED(stat)==0)
    {
        for (ll i = 0; i < 1000; i++)
        {
            if (bg_jobs[i]==pid)
            {
                fprintf(stderr,"Process with pid %lld exited with exit status: %d\n",bg_jobs[i],WEXITSTATUS(stat));
                bg_jobs[i]=-1;
            }
        }
    }

    for (ll i = 0; i < 1000; i++)
    {
        ll ret = kill(bg_jobs[i],0); // this can be used to check for the existence of a process ID
        if (ret == -1)
        {
            fprintf(stderr,"Process with pid %lld exited normally\n",bg_jobs[i]);
            bg_jobs[i]=-1;
        }
    }
}

