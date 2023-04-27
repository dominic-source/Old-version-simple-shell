#include "main.h"

/**
 * compare_string_and_char - to compare string and char
 * @str: input string
 * @c: input char
 *
 * Return: and integer
 */

int compare_string_and_char(const char *str, char c)
{
	int i = 0;

	while (str[i] != '\0')
	{
		if (str[i] == c)
		{
			return (0);
		}
		else
			return (-1);
	}
}

/**
 * _strtok - converts string to token
 * @str: input string
 * @delim: the delimiter
 *
 * Return: pointer to next token
 */

char *_strtok(char *str, const char *delim)
{
	static char *last_token;
	char *token;
	int j = 0, i = 0, n;

	/* If called with NULL argument, continue from last token found*/
	if (str == NULL)
	{
		if (last_token == NULL)
		{
			return (NULL);
		}
		str = last_token;
	}

	/* Find the start of the next token */
	while (str[j] != '\0' && compare_string_and_char(delim, str[j]) != 0)
	{
		j++;
	}
	token = malloc(sizeof(char) * j);

	for (i = 0; i < j; i++)
	{
		token[i] = str[i];
		str[i] = '\0';
	}
	token[j] = '\0';

	if (str[j] == '\0')
	{
		last_token =  NULL;
		return (token);
	}
	str = &str[j + 1];
	last_token = str;
	return (token);
}
