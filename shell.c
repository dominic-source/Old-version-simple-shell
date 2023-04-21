#include "main.h"

/**
 * rem_nwln - remove new line character
 * @str: pointer to string
 * Return: Nothing
 */
void rem_nwln(char *str)
{
	size_t i;

	for (i = 0; i < strlen(str); i++)
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
	*ptr_cpy = malloc(sizeof(char) * (strlen(*ptr) + 1));
	if (ptr_cpy == NULL)
		return;
	strcpy(*ptr_cpy, *ptr);
	/* count the strings and allocate memory for array*/
	token = strtok(*ptr, delim);
	for (cnt = 0; token != NULL; cnt++)
		token = strtok(NULL, delim);

	*argv = malloc(sizeof(char *) * (cnt + 1));
	if (*argv == NULL)
		exit(100);

	/* Allocate memory for each string and add it to array */
	token = strtok(*ptr_cpy, delim);
	for (j = 0; token != NULL; j++)
	{
		(*argv)[j] = malloc(sizeof(char) * (strlen(token) + 1));

		if ((*argv)[j] == NULL)
		{
			for (m = j; m > 0; m--)
				free((*argv)[m]);
			free(*argv);
		}
		strcpy((*argv)[j], token);
		token = strtok(NULL, delim);
	}
	(*argv)[j] = NULL;
}

/**
 * handl_sgnl - handles signal
 * @sig: the signal
 */
void handl_sgnl(int sig)
{
	pid_t my_pid = getpid();

	if (sig == SIGQUIT)
	{
		if (my_pid == parent_pid)
		_exit(0);
	}
}
