#include "header.h"

ll FG(char **com)
{
    ll len = 0, i=0;
    while (com[len]!=NULL) 
        len++;
    if (len!=2)
    {
        fprintf(stderr,"Incorrect arguments\n");
        return 1;
    }

    ll jobnum = atoi(com[1]), c=1;
    for ( i = 0; i < 1024; i++)
    {
        if (bg_jobs[i]==-1)
            continue;
        if (c==jobnum)
        {
            ll shell_pid = getpid();

            /* Ignore the signal */
            signal(SIGTTOU, SIG_IGN);
            signal(SIGTTIN, SIG_IGN);
            tcsetpgrp(0,bg_jobs[i]); // setting foreground grp pid to bg_jobs[i]

            kill(bg_jobs[i],SIGCONT); // continue if stopped
            int status;
            waitpid(bg_jobs[i], &status, WUNTRACED);

            tcsetpgrp(0, getpgrp()); // resetting to grp pid of shell

            /* Default signal handler */
            signal(SIGTTOU, SIG_DFL);
            signal(SIGTTIN, SIG_DFL);

            return 0;
        }
        c++;
    }

    if (c!=jobnum)
    {
        fprintf(stderr,"Error: job no invalid\n");
        return 1;
    }
    
    return 0;
}

ll BG(char **com)
{
    ll len = 0, i = 0;
    while (com[len]!=NULL) 
        len++;
    if (len!=2)
    {
        fprintf(stderr,"Incorrect arguments\n");
        return 1;
    }
    
    ll jobnum = atoi(com[1]), c=1;
    for ( i = 0; i < 1024; i++)
    {
        if (bg_jobs[i]==-1)
            continue;
        if (c==jobnum)
        {
            kill(bg_jobs[i],SIGCONT);
            return 0;
        }
        c++;        
    }
    
    fprintf(stderr,"Error: Invalid Job number\n");
    return 1;
}