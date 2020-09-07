#include "header.h"

ll ECHO(char **com)
{
    ll j=1;
    while (com[j]!=NULL)
    {
        printf("%s ",com[j++]);
    }
    printf("\n");
    
    return 0;
}