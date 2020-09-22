#include "header.h"

// setenv <var> [value] 
// includes <var> in env variables with [value](if no value given then empty string)
ll SENV(char **com)
{
    ll len = 0;
    while (com[len]!=NULL)
        len++;

    if (len==2)
    {
        if (setenv(com[1],"",1)<0)
            fprintf(stderr,"setenv error");
    }
    else if (len==3)
    {
        if (setenv(com[1],com[2],1)<0)
            fprintf(stderr,"setenv error");
    }

    else
        fprintf(stderr,"Error: setenv <var> [value]\n");

    return 0;
}

// removes env variable from the env
ll UNSENV(char **com)
{
    ll len = 0;
    while (com[len]!=NULL)
        len++;
    if (len!=2)
    {
        fprintf(stderr,"unsetenv <var>\n");
        return -1;
    }
    if (unsetenv(com[1])<0)
        fprintf(stderr,"unsetenv error\n");

    return 0;
}