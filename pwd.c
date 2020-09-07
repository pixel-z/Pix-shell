#include "header.h"

ll PWD()
{
    char str[1202];
    getcwd(str,sizeof(str));
    printf("%s\n",str);
    return 0;
}
