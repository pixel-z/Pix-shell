#include "header.h"

void CTRLC(int sig)
{
    return;
}
// for int main loop to do nothing
void CTRLZ0(int sig)
{
    return;
}

// to stop running foreground
// void CTRLZ(int sig)
// {
//     if (fore_pid>0)
//     {
//         kill(fore_pid,SIGTSTP);
//         bg_jobs[bg_cnt]=fore_pid;
//         bg_cnt++;
//         printf("\n\033[1;31mStopped: [%lld]\033[0m\n",fore_pid);
//         fore_pid=-1;
//     }
//     return;
// }