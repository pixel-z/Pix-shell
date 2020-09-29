#include "header.h"

ll FG(char **com)
{
    ll len = 0, i=0;
    while (com[len]!=NULL) 
        len++;
    if (len!=2)
    {
        fprintf(stderr,"Incorrect arguments\n");
        return -1;
    }

    ll jobnum = atoi(com[1]), c=1;
    for ( i = 0; i < 1024; i++)
    {
        if (bg_jobs[i]==-1)
            continue;
        if (c==jobnum)
        {
            // bg_jobs[i] which is to be brought in foreground
        }
        c++;
    }

    if (c!=jobnum)
    {
        fprintf(stderr,"Error: job no invalid\n");
        return -1;
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
        return -1;
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
    return -1;
}