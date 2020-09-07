#include "header.h"

ll CD(char **com)
{
    char *path = malloc(1024 * sizeof(char));

    if (com[1][0] == '~')
    {
        path = newroot;
        ll n = strlen(newroot), m=strlen(com[1]);
        for (ll i = 1; i < m; i++)
            path[n++] = com[1][i];

        path[n] = '\0';
    }
    else
    {
        path = com[1];
        path[strlen(com[1])]='\0';
    }

    if (chdir(path) == -1)
    {
        perror("CD error");
    }

    return 0;
}