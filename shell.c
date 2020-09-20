#include "header.h"
#include "input.c"
#include "exit_stat.c"

char **semicolon_tokenize(char *input_str,ll len)
{
    char **tokens;
    char *command;
    tokens=malloc(len*sizeof(char *));
    command=strtok(input_str,";");

    while (command!=NULL)
    {
        tokens[no_commands++]=command;
        command=strtok(NULL,";");
    }
    tokens[no_commands]=NULL;
    return tokens;
}

char *actual_path(char *rel_path)
{
    char *actual=(char *)malloc(1024*sizeof(char));
    ll m=strlen(rel_path),n=strlen(newroot);

    if (rel_path[0] == '~')
    {
        strcpy(actual,newroot);

        for (ll i = 1; i < m; i++)
            actual[n++]=rel_path[i];

        actual[n]='\0';
    }
    else
    {
        strcpy(actual,rel_path);
        actual[m]='\0';
    }
    return actual;
}

// relative path of string wrt dir from where shell is invoked
char *relative_path(char *check)
{
    char *path;
    ll newroot_size=strlen(newroot), check_size=strlen(check);
    if (strcmp(check,newroot)==0)
        path="~";
    else if(check_size<=newroot_size)
        path=check;
    else
    {
        ll c=0;
        for (ll i = 0; i < newroot_size; i++)
        {
            if(check[i]!=newroot[i])
            {
                c=1;
                break;
            }
        }
        if(c==0)
        {
            path=(char *)malloc(check_size+1);
            path[0]='~';
            ll j=1;
            for (ll i = newroot_size; i < check_size; i++)
                path[j++]=check[i];

            path[j]='\0';
        }
        else
            path=check;        
    }
    return path;
}

void prompt()
{
    // getenv() searches for the environment variable with given string and returns pointer
    char *username=getenv("USER");
    char hostname[1201];
    gethostname(hostname,sizeof(hostname));

    char check[1202];   // check = absolute pwd, path is relative pwd
    getcwd(check,sizeof(check));

    // ANSI color code for coloured output
    printf("\033[1;30m<%s@%s:\033[1;34m%s\033[1;30m>\033[0m ",username,hostname,relative_path(check));
}

int main()
{
    bg_cnt=0;   // no active background processes

    for (ll i = 0; i < 1024; i++)
        bg_jobs[i]=-1;

    printf("\n** Welcome to PiX shell **\n\n");
    getcwd(newroot,sizeof(newroot));

    load_hist();
    while (1)
    {
        EXIT_STAT();
        prompt();
        no_commands=0;

        // getting input
        ssize_t len=0;
        char *input_str=NULL;
        getline(&input_str,&len,stdin);

        // adding command to history if applicable
        history_add(input_str,len); 

        // getting input & tokenize using ';' delim
        char **commands= semicolon_tokenize(input_str,len);

        // included in input.c
        for (ll i = 0; i < no_commands; i++)
        {
            char **com;
            com=filter_token(commands[i]);
            execute(com);
        }

        free(input_str);
        hist_exit();
    }

    return 0;
}