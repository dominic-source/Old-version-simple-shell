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
#include <fcntl.h>
typedef struct srch
{
        char *str;
        int val;
}SRCH;
extern char **environ;
char **my_environ;
SRCH *dir_ext(char *str);
char **create_env_var(void);
char **for_free;

char *_strcat(char *dest, char *src);
char *_strcpy(char *dest, char *src);
size_t _strlen(char *s);
size_t _strcmp(char *s1, char *s2);
size_t _strncmp(char *s1, char *s2, int n);
void print_number(int m);

int _compare(char **argv);
void rem_nwln(char *str);
void handl_sgnl(int sig);
void free_signal_handler(int);
void execmd(char *arg, char *argv);
void sigint_handler(int sig);
void _setenv(char *name, char *value);
void _unsetenv(char *name);
void _cd(char *);
void alloc_mem(char **, char **, char ***);
void free_mem_sh(char **argv, int count, ...);
void dir(char *str);
void m_dprintf(char *arg, char *argv);

pid_t parent_pid;
int comnd_cnt;
int env_count;
int switch_dir;
char ext_sts[12];
char prev_dir[1024];
char hn_dir[1024];
#endif
