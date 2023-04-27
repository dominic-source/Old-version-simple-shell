#include "main.h"

/**
 * _compare - compare strings and print string if necessary
 * @ag: the string to compare
 * Return: 1 if true, 0 if false
 */
int _compare(char **ag)
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
		_setenv(ag[1], ag[2]);
		return (0);
	}
	else if ((_strcmp("unsetenv", ag[0]) == 0) && ag[1] != NULL && ag[2] == NULL)
	{
		_unsetenv(ag[1]);
		return (0);
	}
	else if ((_strcmp("cd", ag[0]) == 0))
	{
		_cd(ag[1]);
		return (0);
	}
	return (-1);
}


/**
 * _setenv - set environment variable
 * @name: name of variable
 * @value: value of variable
 */
void _setenv(char *name, char *value)
{
	size_t i, j, k, length = _strlen(name) + _strlen(value) + 2;

	/* Set variable if it exit */
	for (i = 0; my_environ[i] != NULL; i++)
	{
		if (_strncmp(my_environ[i], name, _strlen(name)) == 0)
		{
			my_environ[i] = realloc(my_environ[i], sizeof(char) * length);
			if (my_environ[i] == NULL)
			{
				perror("Unable to reallocate appropriate memory!\n");
				return;
			}
			for (j = 0; j < _strlen(name); j++)
				my_environ[i][j] = name[j];
			my_environ[i][j] = '=';
			for (k = 0; k < _strlen(value); k++)
				my_environ[i][++j] = value[k];
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
	for (j = 0; j < _strlen(name); j++)
		my_environ[env_count][j] = name[j];
	my_environ[env_count][j] = '=';
	for (k = 0; k < _strlen(value); k++)
		my_environ[env_count][++j] = value[k];
	my_environ[env_count][++j] = '\0';
	my_environ[env_count + 1] = NULL;
	env_count++;
	if (errno == -1)
		perror("Error: unable to set variable!\n");
}


/**
 * _unsetenv - unset environment variable
 * @name: name of variable
 */
void _unsetenv(char *name)
{
	int i, j;

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
 * @str: The file directory you want to enter
 *
 */
void _cd(char *str)
{
	char *pwd = "PWD";
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
			str = NULL;
			str = prev_dir;
		}
		else
		{
			switch_dir = 1;
			str = NULL;
			if (*hn_dir)
				str = hn_dir;
			else
				str = prev_dir;
		}
		f = chdir(str);
	}
	else
	{
		f = chdir(str);
		if (f == 0)
			dir(str);
	}
	_setenv(pwd, str);
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

