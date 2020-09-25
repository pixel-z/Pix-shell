#include "header.h"

pid_t foreground_pid;
ll flag=0;

// we could not do it normally as execvp skips the below code therefore we need to fork 
// Therefore child executes the command and parent(prompt) waits for its completion
void foreground(char **com)
{
    pid_t pid = fork();
    if (pid < 0)
    {
        perror("Forking Error");
        exit(EXIT_FAILURE);
    }
    else if (pid==0)
    {
        // Changing group id of child from parent to make both of them run in foregrnd
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
    }
}

void background(char **com, ll len)
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
        foreground(com);
    else
        background(com,len);
}