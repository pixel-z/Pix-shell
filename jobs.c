#include "header.h"

ll JOBS(char **com)
{
    ll num=1, ret=0;
    for (ll i = 0; i < 1024; i++)
    {
        if (bg_jobs[i]==-1)
        continue; // bg job is already finished

        char stat[1024],bg_name[1024];
        char *status_path= malloc(1024 * sizeof(char));
        sprintf(status_path,"/proc/%lld/status",bg_jobs[i]);

        FILE *fp = fopen(status_path, "r");
        if (fp==NULL){
            perror("JOBS error");
            ret=1;
        }
        else
        {
            char line[1024];
            ll c=1;
            while (fgets(line, sizeof(line), fp)!=NULL)
            {
                if (c==1)
                {
                    char **tokens=filter_token(line);
                    strcpy(bg_name,tokens[1]);
                    ll flag=2;
                    while(tokens[flag]!=NULL)
                    {
                        strcat(bg_name,tokens[flag]);
                    }
                }
                
                if (c==3)
                {
                    char **tokens=filter_token(line);
                    if (tokens[1][0]=='T')
                        strcpy(stat,"Stopped");
                    else
                        strcpy(stat,"Running");

                    break;
                }
                c++;
            }
        }

        printf("[%lld] %s %s [%lld]\n",num,stat,bg_name,bg_jobs[i]);
        num++;

        free(status_path);
    }
    return ret;
}