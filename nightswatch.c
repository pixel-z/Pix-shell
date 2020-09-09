#include "header.h"

// n should be given integer that is assumed
ll NIGHTSWATCH(char **com)
{
    ll len=0;
    while(com[len]!=NULL)
        len++;

    if (len!=4)
    {
        printf("Error: Give input as `nightswatch -n [seconds] [interrupt]`\n");
        return -1;
    }
    if (strcmp(com[1],"-n")!=0 || strcmp(com[3], "interrupt")!=0)
    {
        printf("Input error\n"); 
        return -1;
    }

    FILE *fp0 = fopen("/proc/interrupts","r");
    char one[1024];
    if (fp0==NULL)
    {
        fprintf(stderr,"Could not open /proc/interrupt\n");
        return -1;
    }

    fgets(one,sizeof(one),fp0);
    printf("%s",one);

    ll sec = atoi(com[2]);

    while(1)
    {
        FILE *fp = fopen("/proc/interrupts","r");
       
        char line[1024],two[1024];
        ll len=0;

        for (ll i = 0; i < 2; i++)
        {
            fgets(line,sizeof(line),fp);
            if(i==1)
            {
                strcpy(two,line);
                two[strlen(line)]='\0';
            }
        }
        for (ll i = 0; i < strlen(line); i++)
        {
            if (line[i]=='I')
            {
                line[i]='\0';
                break;
            }
        }
        printf("%s\n",line);

        
        
        sleep(sec);
    }
    

    return 0;
}