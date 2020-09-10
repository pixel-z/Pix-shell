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
        fprintf(stderr,"Could not open /proc/interrupts\n");
        return -1;
    }

    fgets(one,sizeof(one),fp0);
    printf("%s",one);

    ll sec = atoi(com[2]);

    while(1)
    {
        FILE *fp = fopen("/proc/interrupts","r");
       
        char line[1024];
        ll len=0;

        // for (ll i = 0; i < 2; i++)
        // {
        //     fgets(line,sizeof(line),fp);
        //     if(i==1)
        //     {
        //         strcpy(two,line);
        //         two[strlen(line)]='\0';
        //     }
        // }

        // every comp may have different line which contains i8042
        // so we need to all lines
        for (ll i = 0; ; i++)
        {
            if (fgets(line,sizeof(line),fp)==NULL)
            {
                printf("Error in reading file\n");
                return -1;
            }
            
            char c[6];
            ll j=0;

            // last char is \n of line
            for (ll i = strlen(line)-6; i < strlen(line)-1; i++)
                c[j++]=line[i];

            if (strcmp(c,"i8042")==0)
                break;
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

        // Ref from select() examples on man page
        fd_set rfds;
        struct timeval tv;
        int retval;

        /* Watch stdin (fd 0) to see when it has input. */
        FD_ZERO(&rfds);
        FD_SET(0, &rfds);

        /* 0 timeout */
        tv.tv_sec = 0;      // seconds
        tv.tv_usec = 0;     // microseconds

        retval = select(1,&rfds,NULL,NULL,&tv);
        if (retval == -1)
            perror("select()");

        else if (retval != 0)
        {
            // fgetc reads input stream char by char, here if 1st char is q then it exits
            // E.g: `qw` also exits as `q`, but displays weirdly.
            char c = fgetc(stdin); 
            if (c=='q')
                return 0;                
        }        

        sleep(sec);
    }
    

    return 0;
}