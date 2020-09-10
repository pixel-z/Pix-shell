#include "header.h"

void EXIT_STAT()
{
    int status;
    ll check = waitpid(-1,&status,WNOHANG);
    if (check >0)
    {
        if (WIFEXITED(status)==0)
        {
            for (ll i = 0; i < 1000; i++)
            {
                if (bg_jobs[i]==check)
                    bg_jobs[i]=-1;
            }
            printf("Process with pid %lld exited with status: %d\n",check,WEXITSTATUS(status));
        }
    }

    for (ll i = 0; i < 1000; i++)
    {
        if (kill(bg_jobs[i],0)==-1)
        {
            printf("%s with pid %lld exited successfully\n",bg_jobs_name[i],bg_jobs[i]);
            printf("%s\n",bg_jobs_name[i]);
        }
    }
}

