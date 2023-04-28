#include "main.h"

/**
 * _compare - compare strings and print string if necessary
 * @ag: the string to compare
 * @arg: name of script
 * Return: 1 if true, 0 if false
 */
int _compare(char **ag, char *arg)
{
	int i;

	if ((_strcmp("exit", ag[0]) == 0))
	{
		if (ag[1] != NULL)
			_strcpy(ext_sts, ag[1]);
		return (1);
	}
	else if ((_strcmp("env", ag[0]) == 0))
	{
		for (i = 0; my_environ[i] != NULL; i++)
		{
			write(STDOUT_FILENO, my_environ[i], _strlen(my_environ[i]));
			write(STDOUT_FILENO, "\n", 1);
		}
		return (0);
	}
	else if ((_strcmp("setenv", ag[0]) == 0) &&  ag[1] != NULL && ag[2] != NULL)
	{
		_setenv(ag, arg);
		return (0);
	}
	else if ((_strcmp("unsetenv", ag[0]) == 0) && ag[1] != NULL && ag[2] == NULL)
	{
		_unsetenv(ag[1], arg);
		return (0);
	}
	else if ((_strcmp("cd", ag[0]) == 0))
	{
		_cd(ag, arg);
		return (0);
	}
	return (-1);
}


/**
 * _setenv - set environment variable
 * @argv: array of variable
 * @arg: name of executable
 */
void _setenv(char **argv, char *arg)
{
	size_t i, j, k, length = _strlen(argv[1]) + _strlen(argv[2]) + 2;

	if (argv[1] == NULL || argv[2] == NULL)
		m_dprintf(arg, argv[0], "not found");
	for (i = 0; my_environ[i] != NULL; i++)
	{
		if (_strncmp(my_environ[i], argv[1], _strlen(argv[1])) == 0)
		{
			my_environ[i] = realloc(my_environ[i], sizeof(char) * length);
			if (my_environ[i] == NULL)
			{
				perror("Unable to reallocate appropriate memory!\n");
				return;
			}
			for (j = 0; j < _strlen(argv[1]); j++)
				my_environ[i][j] = argv[1][j];
			my_environ[i][j] = '=';
			for (k = 0; k < _strlen(argv[2]); k++)
				my_environ[i][++j] = argv[2][k];
			my_environ[i][++j] = '\0';
			return;
		}
	}
	/* set variable if it does not exist */
	my_environ = realloc(my_environ, sizeof(char *) * (env_count + 2));
	if (my_environ == NULL)
		return;
	my_environ[env_count] = malloc(sizeof(char) * length);
	if (my_environ[env_count] == NULL)
		return;
	for (j = 0; j < _strlen(argv[1]); j++)
		my_environ[env_count][j] = argv[1][j];
	my_environ[env_count][j] = '=';
	for (k = 0; k < _strlen(argv[2]); k++)
		my_environ[env_count][++j] = argv[2][k];
	my_environ[env_count][++j] = '\0';
	my_environ[env_count + 1] = NULL;
	env_count++;
	if (errno == -1)
		perror("Error: unable to set variable!\n");
}


/**
 * _unsetenv - unset environment variable
 * @name: name of variable
 * @arg: name of executable
 */
void _unsetenv(char *name, char *arg)
{
	int i, j;

	if (name == NULL)
	{
		m_dprintf(arg, name, "not found");
		return;
	}
	for (i = 0; my_environ[i] != NULL; i++)
	{
		if (_strncmp(my_environ[i], name, _strlen(name)) == 0)
		{
			free(my_environ[i]);
			for (j = i; my_environ[j] != NULL; j++)
				my_environ[j] = my_environ[j + 1];
			--env_count;
		}
	}
	if (errno == -1)
		perror("Error: unable to remove variable!\n");
}



/**
 * _cd - change directory
 * @arg: argumens which includes directories
 * @ag: name of executable
 */
void _cd(char **arg, char *ag)
{
	char *str = arg[1], *pwd = "PWD", *ar[3];
	int f, i;

	if (str == NULL)
	{
		for (i = 0; my_environ[i] != NULL; i++)
			if (_strncmp("HOME=", my_environ[i], 5) == 0)
				str = &my_environ[i][5];
		f = chdir(str);
		if (f == 0)
			dir(str);
	}
	else if (_strcmp("-", str) == 0)
	{
		if (switch_dir == 1)
		{
			switch_dir = 0;
			str = prev_dir;
		}
		else
		{
			switch_dir = 1;
			if (*hn_dir)
				str = hn_dir;
			else
				str = prev_dir;
		}
		f = chdir(str);
	}
	else
	{
		if (chdir(str) == 0)
			dir(str);
	}
	ar[0] = arg[0];
	ar[1] = pwd;
	ar[2] = str;
	_setenv(ar, ag);
	if (f == -1)
		perror("Error: ");
}

/**
 * dir - manages directory
 * @str: directory
 */
void dir(char *str)
{
	int j;

	for (j = 0; hn_dir[j] != '\0'; j++)
		hn_dir[j] = '\0';
	for (j = 0; prev_dir[j] != '\0'; j++)
		hn_dir[j] = prev_dir[j];
	for (j = 0; prev_dir[j] != '\0'; j++)
		prev_dir[j] = '\0';
	for (j = 0; str[j] != '\0'; j++)
		prev_dir[j] = str[j];
}

