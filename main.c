#include "main.h"
#define FREE_EXIT\
	do {\
		free_mem_sh(argv, 4, lineptr, lineptr_cpy, new_str, new_str->str);\
		free_mem_sh(my_environ, 0);\
		exit(EXIT_SUCCESS);\
	} \
	while (0)
#define FREE_EXIT_B\
	do {\
		free_mem_sh(argv, 2, lineptr, lineptr_cpy);\
		free_mem_sh(my_environ, 0);\
		exit(ext_sts != NULL ? atoi(ext_sts) : EXIT_SUCCESS);\
	} \
	while (0)
#define WAIT_FREE\
	do {\
		wait(&status);\
		free_mem_sh(argv, 4, lineptr, lineptr_cpy, new_str, new_str->str);\
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
int main(int ac, char *argv[])
{
	char *arg = argv[0], *lineptr = NULL, **check_env, *start = "($) ";
	ssize_t line;
	size_t len = 0;
	int state = ac, interactive, fd;

	parent_pid = getpid();
	getcwd(prev_dir, 1024);
	switch_dir = 0;
	ext_sts[0] = '\0';
	check_env = create_env_var();
	interactive = isatty(STDIN_FILENO);
	fd = handle_sh(argv[1], arg);
	if (check_env == NULL)
		perror("Unable to create environment variable!\n");
	while (state && interactive && fd == 1 && argv[1] == NULL)
	{
		write(STDIN_FILENO, start, _strlen(start));
		++comnd_cnt;
		for_free = &lineptr;
		line = _getline(&lineptr, &len, STDIN_FILENO);
		if (line == -1)
		{
			write(STDOUT_FILENO, "\n", 1);
			if (check_env != NULL)
				free_mem_sh(check_env, 0);
			free(lineptr);
			exit(EXIT_SUCCESS);
		}
		if (_strlen(lineptr) > 1)
			execmd(arg, lineptr);
		else
			free(lineptr);
	}
	if (!interactive || fd > 1)
		non_interactive(&lineptr, &arg, fd);
	free_mem_sh(check_env, 0);
	return (0);
}

/**
 * non_interactive - handle non interactive mode
 * @lptr: storage of what was read
 * @arg: first argument
 * @fd: file descriptor
 */
void non_interactive(char **lptr, char **arg, int fd)
{
	ssize_t line;
	size_t len = 0;
	int dnt = 0;

	line = _getline(lptr, &len, fd != 1 ? fd : STDIN_FILENO);
	if (fd == 1)
		execmd(*arg, *lptr);
	while (line != -1 && fd != 1)
	{
		if (dnt != 0)
		{
			if (**lptr != '\0' && _strcmp(*lptr, " ") != 0 && _strcmp(*lptr, "\n"))
				execmd(*arg, *lptr);
		}
		line = _getline(lptr, &len, fd != 1 ? fd : STDIN_FILENO);
		dnt++;
	}
	close(fd);
}


/**
 * handle_sh - handles the opening of file only
 * @str: diretory to open
 * @arg: name of executable
 * Return: 1 or file descriptor
 */
int handle_sh(char *str, char *arg)
{
	int fd = 1;

	if (str != NULL)
		fd = open(str, O_RDONLY);
	if (fd == -1 && str != NULL)
	{
		m_dprintf(arg, "Can't open", str);
		return (1);
	}
	return (fd);
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
	int ex, status, cmp;

	alloc_mem(&lineptr, &lineptr_cpy, &argv);
	if (argv == NULL || arg == NULL)
		return;
	if (argv[0] != NULL)
		new_str = dir_ext(argv[0]);
	if (new_str == NULL)
	{
		cmp = _compare(argv, arg);
		if (cmp == 1)
			FREE_EXIT_B;
		else if (cmp != 0)
			m_dprintf(arg, argv[0], "not found");
	}
	else if (new_str->val == 0)
		CREATE_CHILD;
	if (child_pid == -1)
		FREE_EXIT;
	else if (child_pid == 0)
	{
		ex = execve(pathname, argv, my_environ);
		if (ex == -1)
		{
			write(STDERR_FILENO, arg, sizeof(char) * _strlen(arg));
			perror(":");
			_strcpy(ext_sts, "127");
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

/**
 * create_env_var - create environmental variable for the process
 * Return: pointer to the environmental variable or NULL
 */
char **create_env_var(void)
{
	char *h;
	int i, j, m, n;

	signal(SIGINT, handl_sgnl);
	env_count = 0;
	/* Allocate memory for the environmental variable */
	for (i = 0; environ[i] != NULL; i++)
		env_count++;
	my_environ = malloc(sizeof(char *) * (env_count + 1));
	if (my_environ == NULL)
		return (NULL);
	for (i = 0; environ[i] != NULL; i++)
	{
		h = environ[i];
		my_environ[i] = malloc(sizeof(char) * (_strlen(h) + 1));
		if (my_environ[i] == NULL)
		{
			for (j = i - 1; j <= 0; j--)
				free(my_environ[j]);
			free(my_environ);
			return (NULL);
		}
	}
	/* Initialize memory for the environment variable */
	for (m = 0; environ[m] != NULL; m++)
	{
		for (n = 0; environ[m][n] != '\0'; n++)
			my_environ[m][n] = environ[m][n];
		my_environ[m][n] =  '\0';
	}
	my_environ[m] = NULL;
	return (my_environ);
}
