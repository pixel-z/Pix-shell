#include "header.h"

ll OVERKILL()
{
    for (ll i = 0; i < 1024; i++)
    {
        if (bg_jobs[i]!=-1)
        {
            kill(bg_jobs[i], SIGKILL);
            bg_jobs[i]=-1;
        }
    }
    return 0;
}