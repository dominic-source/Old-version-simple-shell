#include "main.h"

/**
 * _getline - stores input characters as a string
 * @lineptr: pointer to the bigining of the line
 * @n: number of bytes to be read
 * @stream: the source of input
 *
 * Return: The number of characters read
 */
ssize_t _getline(char **lineptr, size_t *n, int stream)
{
	char *buffer, *temp;
	size_t buf_size = 128, position = 0;
	int rd;

	if (alloc_getline(lineptr, &buffer, buf_size, n) == -1)
		return (-1);
	for_free2 = &buffer;
	while (1)
	{
		rd = read(stream, &buffer[position], 1);
		if (rd == -1 || rd == 0)
		{
			free(buffer);
			return (-1);
		}
		if (buffer[position] == '\n')
			break;
		position++;
		if (position >= buf_size)
		{
			buf_size += 128;
			temp = realloc(buffer, buf_size);
			if (realloc_free(&temp, &buffer) == -1)
				return (-1);
			buffer = temp;
		}
	}
	buffer[position] = '\0';
	if ((position + 1) > *n)
	{
		*lineptr = realloc(*lineptr, sizeof(char) * (position + 1));
		if (realloc_free(lineptr, &buffer) == -1)
			return (-1);
		*n = position + 1;
	}
	_memcpy(*lineptr, buffer, position);
	free(buffer);
	return (position);
}

/**
 * _memcpy - copy memory
 * @lineptr: destination
 * @buffer: source
 * @position: position of string pointer
 */
void _memcpy(char *lineptr, char *buffer, int position)
{
	int i;

	for (i = 0; i < (position + 1); i++)
		lineptr[i] = buffer[i];
}

/**
 * alloc_getline - allocate memory for getline
 * @lineptr: memory to write to
 * @buf: memory to write from
 * @buf_s: size of buffer
 * @n: length
 * Return: -1 or 0
 */
ssize_t alloc_getline(char **lineptr, char **buf, size_t buf_s, size_t *n)
{

	if (lineptr == NULL || n == NULL)
		return (-1);
	/* Allocate memory for buffer */
	*buf = malloc(sizeof(char) * buf_s);
	if (*buf == NULL)
		return (-1);
	*lineptr = malloc(sizeof(char) * buf_s);
	if (*lineptr == NULL)
		return (-1);
	return (0);
}

/**
 * realloc_free - reallocate for getline
 * @lineptr: test before freeing
 * @buffer: buffer to free
 * Return: -1 or 0
 */
ssize_t realloc_free(char **lineptr, char **buffer)
{
	if (*lineptr == NULL)
	{
		free(*buffer);
		return (-1);
	}
	return (0);
}


/**
 * _fgetc - a replica of fgetc function
 * @fp: source of input
 *
 * Return: the character read as an unsigned char cast
 */
int _fgetc(FILE *fp)
{
	char c;
	ssize_t num_read;

	if (fp == NULL)
	{
		return (EOF);
	}

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
