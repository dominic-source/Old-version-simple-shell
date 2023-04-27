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
	return (-1);
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
	int j = 0;

	/* If called with NULL argument, continue from last token found*/
	if (str == NULL)
	{
		if (last_token == NULL)
		{
			return (NULL);
		}
		str = last_token;
	}
	/* skip leading delimiters */
	while (str[j] != '\0' && compare_string_and_char(delim, str[j]) == 0)
	{
		j++;
	}
	if (str[j] == '\0')
	{
		last_token =  NULL;
		return (NULL);
	}
	token = str;
	/*  Find the end of the token */
	while (str[j] != '\0' && compare_string_and_char(delim, str[j]) != 0)
		j++;
	if (str[j] != '\0')
	{
		str[j] = '\0';
		last_token = &str[j + 1];
	}
	else
		last_token  = NULL;
	return (token);
}
