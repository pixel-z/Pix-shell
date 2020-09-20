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

ll execute(char **com)
{
    ll len=0;
    while(com[len]!=NULL)
        len++;

    if (com[0]==NULL)
        return 0;
    else if (strcmp(com[0],"overkill")==0)
        return OVERKILL();
    else if (strcmp(com[0], "jobs")==0)
        return JOBS(com);
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