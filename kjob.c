#include "header.h"

ll KJOB(char **com)
{
    ll len=0;
    while(com[len]!=NULL)
        len++;

    if (len != 3)
    {
        perror("kjob: Incorrect no. of argument");
        return 1;
    }

    ll i=0;
    while (com[1][i]!='\0')
    {
        if (com[1][i]<'0' || com[1][i]>'9')
        {
            perror("kjob: Incorrect jobnumber");
            return 1;
        }
        i++;
    }
    i=0;
    while (com[2][i]!='\0')
    {
        if (com[2][i]<'0' && com[2][i]>'9')
        {
            perror("kjob: Incorrect signal no.");
            return 1;
        }
        i++;
    }
    ll jobnum = atoi(com[1]), signum = atoi(com[2]);

    ll c=1;
    for (i = 0; i < 1024; i++)
    {
        if (bg_jobs[i]==-1)
            continue;
        
        if (c==jobnum)
        {
            if (kill(bg_jobs[i],signum)==-1)
            {
                perror("kill() error");
                return 1;
            }
            break;
        }
        c++;
    }
    if (c!=jobnum)
    {
        printf("Invalid job number\n");
        return 1;
    }

    return 0;
}