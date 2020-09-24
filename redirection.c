#include "header.h"

// In redirection there can be only 1 command, 1 input & 1 output file
// more than 1 command not possible 
// more than 1 in file or out file, only 1 considered other ignored 
ll REDIRECT(char **com)
{
    ll r1=0, r2=0, r3=0;

    ll idx1=-1, idx2=-1;
    ll i=0, mini=10000000000;
    while (com[i]!=NULL)
    {
        if (strcmp(com[i],"<")==0)
        {
            r1=1;
            idx1=i+1;
            if (i<mini)
                mini=i;
        }
        if (strcmp(com[i],">")==0 || strcmp(com[i],">>")==0)
        {
            if (strcmp(com[i],">")==0)
                r2=1,r3=0;
            else
                r2=0,r3=1;

            idx2=i+1;
            if (i<mini)
                mini=i;
        }
        i++;
    }
    com[mini]=NULL; // for execvp
    
    if ((idx1!=-1 && com[idx1]==NULL) || (idx2!=-1 && com[idx2]==NULL))
    {
        fprintf(stderr,"Redirection error\n");
        return -1;
    }

    char in[1024], out[1024];
    if (idx1!=-1 && com[idx1]!=NULL)
        strcpy(in,com[idx1]);
    if (idx2!=-1 && com[idx2]!=NULL)
        strcpy(out,com[idx2]);
    
    ll fd_stdin=dup(0),fd_stdout=dup(1); //fd of stdin and stdout
    ll fd_in,fd_out;
    if (r1==1)
    {
        struct stat check;
        if (stat(in,&check)<0)
        {
            fprintf(stderr,"Input file error\n");
            return -1;
        }
        fd_in=open(in,O_RDONLY,0644);
        dup2(fd_in,0);
    }
    if (r2==1)
    {
        fd_out=open(out,O_WRONLY | O_CREAT | O_TRUNC,0644);
        dup2(fd_out,1);
    }
    if (r3==1)
    {
        fd_out=open(out,O_WRONLY | O_CREAT | O_APPEND,0644);
        dup2(fd_out,1);
    }
    
    pid_t pid=fork();
    if (pid<0)
    {
        perror("fork error");
        return -1;
    }
    if (pid==0)
    {
        if (execvp(com[0], com) < 0)
        {
            fprintf(stderr,"Execvp: Command not found\n");
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        wait(NULL);
        dup2(fd_stdin,0);
        dup2(fd_stdout,1);
    }

    return 0;
}