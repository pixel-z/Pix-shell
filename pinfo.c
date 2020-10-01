#include "header.h"

ll PINFO(char **com)
{
    ll pid;
    if (com[1] == NULL) 
        pid = getpid();
    else
        pid = atoi(com[1]);

    char *status_path = malloc(1024*sizeof(char));
    sprintf(status_path,"/proc/%lld/status",pid);

    FILE *fp = fopen(status_path,"r");
    if (fp==NULL)
    {
        fprintf(stderr,"Process with given pid %lld not found\n",pid);
        free(status_path);
        return 1;
    }

    char status[2048], memory[2048], path[2048];
    ll c=1;
    char line[1024];
    while (fgets(line,sizeof(line),fp)!=NULL)
    {
        if (c==3)
        {
            char **tokens=filter_token(line);
            strcpy(status,tokens[1]);
        }
        if (c==18)
        {
            char **tokens=filter_token(line);

            if(tokens[2]== NULL)
            strcpy(memory,tokens[1]);
            else
            sprintf(memory,"%s %s",tokens[1],tokens[2]); // token[2] = kB
        }
        c++;
    }
    printf("pid -- %lld\nProcess Status -- %s\nVirtual memory -- %s\n",pid,status,memory);

    char exe_path[2048], exec[2048];
    sprintf(exe_path,"/proc/%lld/exe",pid);

    ll ret = readlink(exe_path, exec, 1024);

    if (ret < 0)
    {
        perror("readlink failed");
        fclose(fp);
        free(status_path);
        return 1;
    }
    else
    {
        exec[ret]='\0';
        char *rel_exec = relative_path(exec);
        printf("Executable path -- %s\n",rel_exec);

        fclose(fp);
        free(status_path);
        return 0;
    }
}  