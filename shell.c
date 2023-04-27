#include "main.h"

/**
 * rem_nwln - remove new line character
 * @str: pointer to string
 * Return: Nothing
 */
void rem_nwln(char *str)
{
	size_t i;

	for (i = 0; i < _strlen(str); i++)
	{
		if (str[i] == '\n')
			str[i] = '\0';
	}
}

/**
 * alloc_mem - allocate memory
 * @ptr: the string to split
 * @ptr_cpy: the copy string to split
 * @argv: pointer to array of arrays
 */
void alloc_mem(char **ptr, char **ptr_cpy, char ***argv)
{
	char *token;
	char *delim = " ";
	int m, cnt, j = 0;

	rem_nwln(*ptr);
	/* Allocate memory for a copy of the string */
	*ptr_cpy = malloc(sizeof(char) * (_strlen(*ptr) + 1));
	if (ptr_cpy == NULL)
		return;
	_strcpy(*ptr_cpy, *ptr);
	/* count the strings and allocate memory for array*/
	token = _strtok(*ptr, delim);
	for (cnt = 0; token != NULL; cnt++)
		token = _strtok(NULL, delim);

	*argv = malloc(sizeof(char *) * (cnt + 1));
	if (*argv == NULL)
		exit(100);

	/* Allocate memory for each string and add it to array */
	token = _strtok(*ptr_cpy, delim);
	for (j = 0; token != NULL; j++)
	{
		(*argv)[j] = malloc(sizeof(char) * (_strlen(token) + 1));

		if ((*argv)[j] == NULL)
		{
			for (m = j; m > 0; m--)
				free((*argv)[m]);
			free(*argv);
		}
		_strcpy((*argv)[j], token);
		token = _strtok(NULL, delim);
	}
	(*argv)[j] = NULL;
}

/**
 * handl_sgnl - handles signal
 * @sig: the signal
 */
void handl_sgnl(int sig)
{
	if (sig == SIGINT)
	{
		free_mem_sh(my_environ, 0);
		if (*for_free != NULL)
			free(*for_free);
		write(STDOUT_FILENO, "\n", 1);
		exit(EXIT_SUCCESS);
	}
}

/**
 * m_dprintf - single used for function to write to stderr
 * @arg: executable
 * @argv: first shell argument
 */
void m_dprintf(char *arg, char *argv)
{
	write(STDERR_FILENO, arg, sizeof(char) * _strlen(arg));
	write(STDERR_FILENO, ": ", 2);
	print_number(comnd_cnt);
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, argv, sizeof(char) * _strlen(argv));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, "not found\n", 10);
}

/**
 * print_number - print number
 * @m: an integer
 */
void print_number(int m)
{
	unsigned int n;
	char s;

	n = m;
	if (m < 0)
	{
		s = '-';
		write(STDERR_FILENO, &s, 1);
		n = -m;
	}

	if (n / 10 != 0)
		print_number(n / 10);

	s = (n % 10) + '0';
	write(STDERR_FILENO, &s, 1);
}
