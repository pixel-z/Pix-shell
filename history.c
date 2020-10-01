#include "header.h"

// ******* It is 1 based indexing while printing ********
// hist_cnt is restored by saving it in 1st line of history.txt

void load_hist()
{
    char *path = actual_path("~/history.txt");
    FILE *fp = fopen(path, "r");

    if (fp != NULL)
    {
        char line[1024];
        ll c=0;
        while(fgets(line, sizeof(line), fp) != NULL)
        {
            if (c==0)
            {
                hist_cnt=atoi(line);
                c++;
                continue;
            }
            strcpy(hist[c],line);
            hist[c][strlen(line)-1]='\0';
            c++;
            // printf("%s\n",line);
        }
        fclose(fp);
    }
    else 
        perror("history.txt");
    
    return;
}

// changing hist[] whenever a input is written
void history_add(char *input_str)
{
    if (strcmp(input_str,"\n") == 0 || strcmp(input_str,"\t")==0 || strcmp(input_str,"\0")==0)
        return;

    if(hist_cnt>=20)
    {
        for (ll i = 1; i <= hist_cnt-1; i++)
            strcpy(hist[i],hist[i+1]);
    }
    else
        hist_cnt++;

    strcpy(hist[hist_cnt],input_str);
    hist[hist_cnt][strlen(input_str)-1]='\0'; // it will be \n initially (while we enter in prompt)
    
    return;
}

// displays history with flags
ll HISTORY(char **com)
{
    // printf("%lld\n",hist_cnt);
    if (com[2]!=NULL)
    {
        printf("Incorrect no. of arguments\n");
        return 1;
    }
    
    if (com[1]==NULL)
    {
        ll j = (hist_cnt-9> 1) ? (hist_cnt-9) : 1;

        for (ll i = j; i <= hist_cnt; i++)
            printf("%lld %s\n",i-j+1,hist[i]);
        
        return 0;
    }
    ll num = atoi(com[1]);
    if (num>0 && num<=20)
    {
        if (num>hist_cnt)
        {
            fprintf(stderr,"Wrong argument\n");
            return 1;
        }
        for (ll i = hist_cnt-num+1; i <= hist_cnt; i++)
        {
            printf("%lld %s\n",i-hist_cnt+num,hist[i]);
        }
    }
    else
    {
        fprintf(stderr,"Error: No.should be < 20\n");
        return 1;
    }
    
    return 0;
}

void hist_exit()
{
    FILE *fp = fopen(actual_path("~/history.txt"),"w");

    fprintf(fp,"%lld\n",hist_cnt);
    for (ll i = 1; i <= hist_cnt; i++)
        fprintf(fp,"%s\n",hist[i]);

    fclose(fp);
}