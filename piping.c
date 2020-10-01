#include "header.h"

ll check_redir(char *command)
{
    char **tokens = filter_token(command);
    ll num=0;
    while (tokens[num] != NULL)
    {
        if (strcmp(tokens[num],">")==0 || strcmp(tokens[num],"<")==0 || strcmp(tokens[num],">>")==0)
            return 1;
        num++;
    }
    return 0;
}

// input_str is first tokenized by ';' and then send here
ll PIPING(char *input_str)
{
    ll num=0, in=0;
    char **tokens=malloc(1024*sizeof(char *));
    char *command;
    
    command = strtok(input_str,"|");
    while (command != NULL)
    {
        tokens[num++] = command;
        command = strtok(NULL,"|");
    }
    tokens[num] = NULL;

    ll ret=0;
    int pp[2]; pipe(pp);
    for (ll i = 0; i < num; i++)
    {
        char **com = filter_token(tokens[i]);
        int fd[2];
        if(pipe(fd)==-1)
        {
            perror("pipe");
            return 1;
        }
        
        pid_t pid = fork();
        if (pid == -1)
        {
            perror("Forking error");
            return 1;
        }

        else if (pid == 0)
        {
            dup2(in,0);

            if (i!=num-1)
                dup2(fd[1],1);
            
            close(fd[0]);
            close(pp[0]);

            if (check_redir(tokens[i])==1)
                ret=REDIRECT(filter_token(tokens[i]));
            else
                ret=execute(com,NULL); // NULL because 2nd parameter is for piping, command cannot contain pipe therefore NULL 

            write(pp[1],&ret,sizeof(ret));
            close(pp[1]);
            exit(1); // exits child process
        }
        else 
        {
            wait(NULL);
            close(fd[1]);
            close(pp[1]);
            read(pp[0],&ret,sizeof(ret));
            in=fd[0];
            close(pp[0]);
        }

    }
    free(tokens);
    return ret;
}