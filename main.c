#include "main.h"

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
		line = getline(&lineptr, &len, stdin);
		if (line == -1)
		{
			printf("\n");
			free(lineptr);
			kill(0, SIGQUIT);
		}
		execmd(arg, lineptr);
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
}


/**
 * execmd - execute command
 * @lineptr: array of commands and argument
 * @arg: command line argument
 */
void execmd(char *arg, char *lineptr)
{
	char *lineptr_cpy, **argv;
	int ex, status;
	pid_t child_pid;

	signal(SIGQUIT, handl_sgnl);
	alloc_mem(&lineptr, &lineptr_cpy, &argv);
	if (dir_ext(argv[0]) == 0)
	child_pid = fork();
	else
		exit(EXIT_SUCCESS);
	if (child_pid == -1)
	{
		free_mem_sh(argv, 2, lineptr, lineptr_cpy);
		exit(EXIT_SUCCESS);
	}
	if (child_pid == 0)
	{
		if (strncmp("exit", argv[0], 4) == 0)
		{
			free_mem_sh(argv, 2, lineptr, lineptr_cpy);
			exit(EXIT_SUCCESS);
		}
		ex = execve(argv[0], argv, environ);
		if (ex == -1)
		{
			dprintf(STDERR_FILENO, "%s: ", arg);
			perror("");
			free_mem_sh(argv, 2, lineptr, lineptr_cpy);
			exit(EXIT_FAILURE);
		}
		free_mem_sh(argv, 2, lineptr, lineptr_cpy);
		exit(EXIT_SUCCESS);
	}
	else
	{
		wait(&status);
		if (strncmp("exit", argv[0], 4) == 0)
		{
			free_mem_sh(argv, 2, lineptr, lineptr_cpy);
			exit(EXIT_SUCCESS);
		}
		free_mem_sh(argv, 2, lineptr, lineptr_cpy);
	}
}
