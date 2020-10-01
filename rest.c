#include "header.h"

// we could not do it normally as execvp skips the below code therefore we need to fork 
// Therefore child executes the command and parent(prompt) waits for its completion
ll foreground(char **com)
{
    pid_t pid = fork();
    if (pid < 0)
    {
        perror("Forking Error");
        exit(EXIT_FAILURE);
    }
    else if (pid==0)
    {
        if (execvp(com[0], com) < 0)
        {
            perror("Command invalid");
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        fore_pid = pid;
        signal(SIGTSTP,CTRLZ);
        int status;
        waitpid(pid, &status, WUNTRACED);
        return status;
    }
}

ll background(char **com, ll len)
{
    pid_t pid = fork();
    
    //****
    bg_jobs[bg_cnt] = pid;
    char temp[1024];
    for (ll i = 0; i < len; i++)
    {
        strcat(temp, com[i]);
        strcat(temp, " ");
    }
    bg_cnt++;
    //*****

    // Changing group id of child from parent to make both of them run in foregrnd
    setpgid(0, 0);
    if (pid < -1)
    {
        perror("Forking Error");
        exit(EXIT_FAILURE);
    }
    else if (pid==0)
    {
        if (execvp(com[0], com) < 0)
        {
            perror("Command invalid");
            exit(EXIT_FAILURE);
        }
    }
    return 0;
}

ll REST(char**com)
{
    ll len=0,bg=0;

    while (com[len]!=NULL)
        len++;
    if (strcmp(com[len-1],"&")==0)
    {
        bg=1;
        com[len-1]=NULL;
        len--;
    }

    // no background process
    if (bg==0)
        return foreground(com);
    else
        return background(com,len);
}