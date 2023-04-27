#include "main.h"

/**
 * _fgetc - a replica of fgetc function
 * @fp: source of input
 *
 * Return: the character read as an unsigned char cast
 */

int _fgetc(FILE *fp)
{
	if (fp == NULL)
	{
		return (EOF);
	}
	char c;
	ssize_t num_read;

	num_read = read(fileno(fp), &c, sizeof(char));
	if (num_read != 1)
	{
		if (num_read == 0)
		{
			return (EOF);
		}
		else
		{
			return (-1);
		}
	}
	return ((unsigned char)c);
}

/**
 * _getline - stores input characters as a string
 * @lineptr: pointer to the bigining of the line
 * @n: number of bytes to be read
 * @stream: the source of input
 *
 * Return: The number of characters read
 */

ssize_t _getline(char **lineptr, size_t *n, FILE *stream)
{
	ssize_t num_char_read = 0;
	int current_char = 0;
	*lineptr = (char *)malloc(100);
	if (lineptr == NULL || n == NULL)
	{
		return (-1);
	}

	if (*lineptr == NULL)
	{
		*n = 128;
		*lineptr = (char *)malloc(*n);
		if (*lineptr == NULL)
		{
			return (-1);
		}
	}

	while ((current_char = _fgetc(stream)) != EOF)
	{
		if (num_char_read >= (*n - 1))
		{
			*n *= 2;
			*lineptr = realloc(*lineptr, *n);
			if (*lineptr == NULL)
			{
				return (-1);
			}
		}
		(*lineptr)[num_char_read++] = current_char;

		if (current_char == '\n')
		{
			break;
		}
	}
	(*lineptr)[num_char_read] = '\0';

	return ((num_char_read == 0 && current_char == EOF) ? -1 : num_char_read);
}
