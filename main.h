#ifndef MAIN_H
#define MAIN_H
#include <signal.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdarg.h>
#include <dirent.h>
void rem_nwln(char *str);
void handl_sgnl(int sig);
void execmd(char *arg, char *argv);
void alloc_mem(char **, char **, char ***);
void free_mem_sh(char **argv, int count, ...);
extern char **environ;
pid_t parent_pid;
int dir_ext(char *str);
#endif
