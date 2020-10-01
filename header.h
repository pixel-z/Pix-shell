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
#include <errno.h>

typedef long long ll;
char newroot[1024];
ll no_commands=0; // no of commands divided by ';'
char hist[22][1024]; // it starts from hist[1]
ll hist_cnt=0;
ll bg_jobs[1024]; //list of background jobs pid (-1 when bg terminated)
ll bg_cnt;
char lwd[1024]; //last working directory
ll fore_pid=-1;
ll err_code=-1; // -1=nothing, 0=success, >0=error 

char **semicolon_tokenize();
char **filter_token();
char *actual_path(char *rel_path);
char *relative_path(char *check);
void prompt();
char **filter_token(char *str);
void CTRLZ(int sig);
void CTRLC(int sig);

ll REDIRECT(char **com);
ll execute(char **com, char *input_str);

#endif