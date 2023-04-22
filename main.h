#ifndef MAIN_H
#define MAIN_H
#include <signal.h>
#include <stdio.h>
#include <sys/wait.h>
#include <errno.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdarg.h>
#include <dirent.h>
typedef struct srch
{
        char *str;
        int val;
}SRCH;
void rem_nwln(char *str);
void handl_sgnl(int sig);
void free_signal_handler(int);
void execmd(char *arg, char *argv);
void alloc_mem(char **, char **, char ***);
void free_mem_sh(char **argv, int count, ...);
extern char **environ;
pid_t parent_pid;
SRCH *dir_ext(char *str);
int comnd_cnt;
#endif
