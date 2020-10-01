#include "header.h"
#include "echo.c"
#include "pwd.c"
#include "cd.c"
#include "ls.c"
#include "history.c"
#include "pinfo.c"
#include "rest.c"
#include "nightswatch.c"
#include "jobs.c"
#include "overkill.c"
#include "kjob.c"
#include "env.c"
#include "redirection.c"
#include "piping.c"
#include "fgbg.c"

// each command (command[i]/token) is tokenized with delim ' ' or '\n' or '\t'
char** filter_token(char *str)
{
    char *token;
    char **output=malloc(100000*sizeof(char *));

    token=strtok(str," \n\t\r\a");

    ll j=0;
    while (token!=NULL)
    {
        output[j++]=token;
        token=strtok(NULL," \n\t\r\a");
    }
    output[j]='\0';
    return output;
}

ll execute(char **com, char *input_str)
{
    ll len = 0, redirect=0, pipe=0;
    while (com[len]!=NULL)
    {
        if (strcmp(com[len],">")==0 || strcmp(com[len],"<")==0 || strcmp(com[len],">>")==0)
            redirect=1;
        if (strcmp(com[len],"|")==0)
            pipe=1;
        len++;
    }

    if (com[0]==NULL)
        return -1;
    else if (pipe==1)
        return PIPING(input_str);
    else if (redirect==1)
        return REDIRECT(com);
    else if (strcmp(com[0],"fg")==0)    
        return FG(com);
    else if (strcmp(com[0],"bg")==0)    
        return BG(com);
    else if (strcmp(com[0],"setenv")==0)
        return SENV(com);
    else if (strcmp(com[0],"unsetenv")==0)
        return UNSENV(com);
    else if (strcmp(com[0],"kjob")==0)
        return KJOB(com);
    else if (strcmp(com[0],"overkill")==0)
        return OVERKILL();
    else if (strcmp(com[0],"jobs")==0)
        return JOBS(com);
    else if (strcmp(com[0],"quit")==0 || strcmp(com[0],"exit")==0)
    {
        hist_exit();   
        OVERKILL();
        printf("\n\033[1;33mC U Later :D\033[0m\n");
        exit(0);
    }
    else if (strcmp(com[0],"nightswatch")==0)
        return NIGHTSWATCH(com);
    else if (strcmp(com[0],"echo")==0)
        return ECHO(com);
    else if (strcmp(com[0],"pwd")==0)
        return PWD();
    else if (strcmp(com[0],"cd")==0)
        return CD(com);
    else if (strcmp(com[0],"ls")==0)
        return LS(com);
    else if (strcmp(com[0],"pinfo")==0)
        return PINFO(com);
    else if (strcmp(com[0],"history")==0)
        return HISTORY(com);
    else 
        return REST(com);
}