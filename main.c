#include "main.h"
char ext_sts[12];

#define FREE_EXIT\
	do {\
		free_mem_sh(argv, 4, lineptr, lineptr_cpy, new_str, new_str->str);\
		exit(EXIT_SUCCESS);\
	} \
	while (0)
#define FREE_EXIT_B\
	do {\
		if (argv[1] != NULL)\
		{\
			strcpy(ext_sts, argv[1]);\
		} \
		free_mem_sh(argv, 2, lineptr, lineptr_cpy);\
		exit(ext_sts != NULL ? atoi(ext_sts) : EXIT_SUCCESS);\
	} \
	while (0)
#define WAIT_FREE\
	do {\
		wait(&status);\
		free_mem_sh(argv, 4, lineptr, lineptr_cpy, new_str, new_str->str); \
	} \
	while (0)
#define CREATE_CHILD\
	do {\
		child_pid = fork();\
		pathname = new_str->str;\
	} \
	while (0)
/**
 * main - run a shell
 * @ac: count
 * @argv: arguments
 * Return: 0 or -1
 */
int main(int ac, char **argv)
{
	char *arg = argv[0];
	char *lineptr = NULL;
	ssize_t line;
	size_t len = 0;
	int state = 1;

	parent_pid = getpid();
	if (ac != 1)
		perror("Usage: ./hsh");
	while (state)
	{
		/* start C shell */
		printf("($) ");
		++comnd_cnt;
		line = getline(&lineptr, &len, stdin);
		if (line == -1)
		{
			printf("\n");
			free(lineptr);
			exit(EXIT_SUCCESS);
		}
		if (lineptr != NULL)
			execmd(arg, lineptr);
		else
			free(lineptr);
		len = 0;

	}
	return (0);
}

/**
 * free_mem_sh - free memories
 * @count: last argument
 * @argv: arguments from command line
 */
void free_mem_sh(char **argv, int count, ...)
{
	char *ptr;
	va_list ap;
	int i;

	for (i = 0; argv[i] != NULL; i++)
		free(argv[i]);

	free(argv);
	va_start(ap, count);
	for (i = 0; i < count; i++)
	{
		ptr = va_arg(ap, char *);
		free(ptr);
	}
	va_end(ap);
}


/**
 * execmd - execute command
 * @lineptr: array of commands and argument
 * @arg: command line argument
 */
void execmd(char *arg, char *lineptr)
{
	char *lineptr_cpy, *pathname, **argv;
	SRCH *new_str;
	pid_t child_pid = 1;
	int ex, status;

	alloc_mem(&lineptr, &lineptr_cpy, &argv);
	if (argv == NULL)
		return;
	if (argv[0] != NULL)
		new_str = dir_ext(argv[0]);
	if (new_str == NULL)
	{
		if (strncmp("exit", argv[0], 4) == 0)
			FREE_EXIT_B;
		else
			dprintf(STDERR_FILENO, "%s: %i: %s: not found\n", arg, comnd_cnt, argv[0]);
	}
	else if (new_str->val == 0)
		CREATE_CHILD;
	if (child_pid == -1)
		FREE_EXIT;
	else if (child_pid == 0)
	{
		ex = execve(pathname, argv, environ);
		if (ex == -1)
		{
			dprintf(STDERR_FILENO, "%s: ", arg);
			perror("");
		}
		FREE_EXIT;
	}
	else
	{
		if (child_pid != 1)
			WAIT_FREE;
		else if (child_pid == 1)
			free_mem_sh(argv, 2, lineptr, lineptr_cpy);
	}
}

