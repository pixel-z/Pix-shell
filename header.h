#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <limits.h>
#include <time.h>
#include <fcntl.h>
#include <grp.h>
#include <pwd.h>
#include <inttypes.h>
#include <math.h>
#include <signal.h>
#include <sys/select.h>

typedef long long ll;
char newroot[1024];
ll no_commands=0; // no of commands divided by ';'
char hist[22][1024]; // it starts from hist[1]
ll hist_cnt=0;
ll bg_jobs[1024];
char bg_jobs_name[1000][800];
ll bg_cnt;

char **semicolon_tokenize();
char *actual_path(char *rel_path);
char *relative_path(char *check);
void prompt();
char **filter_token(char *str);

#endif