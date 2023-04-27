#include "main.h"

/**
 * _strcat - concatenate strings
 *Return: pointer to a char
 *@dest: destination of the string
 *@src: src of string
 */
char *_strcat(char *dest, char *src)
{
	int len_dest = 0;
	int len_src = 0;
	int j, k, m;

	if (src == NULL)
		return (NULL);
	if (dest == NULL)
		return (NULL);
	m = 0;
	while (*(src + m) != '\0')
	{
		len_src++;
		m++;
	}
	m = 0;
	while (*(dest + m) != '\0')
	{
		len_dest++;
		m++;
	}
	j = len_dest;
	k = 0;
	while (j < (len_dest + len_src))
	{
		*(dest + j) = *(src + k);
		j++;
		k++;
	}
	*(dest + (len_dest + len_src)) = '\0';
	return (dest);
}


/**
 * _strlen - print the line of a string
 * Return: length of string
 * @s: the string argument
 */
size_t _strlen(char *s)
{
	int i = 0;
	int length = 0;
	char *str = s;

	if (s == NULL)
		return (-1);

	while (i > -1)
	{
		if (*(str + i) != '\0')
		{
			length++;
			i++;
		}
		else
			return (length);
	}
	return (0);
}

/**
 * _strcmp - compares two string
 * Return: an integer is always returned
 * @s1: pointer to a char, argument 1
 * @s2: pointer to a char, argument 2
 */
size_t _strcmp(char *s1, char *s2)
{
	int i = 0;

	if (s1 == NULL || s2 == NULL)
		return (-1);

	while (i > -1 && *(s1 + i) != '\0' && *(s2 + i) != '\0')
	{
		if (*(s1 + i) < *(s2 + i) || *(s1 + i) > *(s2 + i))
		{
			return (*(s1 + i) - *(s2 + i));
		}
		else
		{
			i++;
		}
	}
	if (*(s1 + i) == '\0')
		return (0 - *(s2 + i));
	if (*(s2 + i) == '\0')
		return (*(s1 + i) - 0);
	return (0);
}


/**
 * _strncmp - compares two string
 * Return: an integer is always returned
 * @s1: pointer to a char, argument 1
 * @s2: pointer to a char, argument 2
 * @n: number of strings to compare
 */
size_t _strncmp(char *s1, char *s2, int n)
{
	int i = 0;

	if (s1 == NULL || s2 == NULL || n <= 0)
		return (-1);

	while (i > -1 && *(s1 + i) != '\0' && *(s2 + i) != '\0' && i < n)
	{
		if (*(s1 + i) < *(s2 + i) || *(s1 + i) > *(s2 + i))
		{
			return (*(s1 + i) - *(s2 + i));
		}
		else
		{
			i++;
		}
	}
	return (0);
}


/**
 * _strcpy - copy string from src to destination
 * Return: a pointer to a char
 * @dest: this is the destination of the char
 * @src: this is the source
 */
char *_strcpy(char *dest, char *src)
{
	int i = 0;

	if (dest == NULL || src == NULL)
		return (NULL);
	while (i > -1)
	{
		if (src[i] != '\0')
		{
			*(dest + i) = *(src + i);
			i++;
		}
		else
		{
			*(dest + i) = *(src + i);
			return (dest);
		}
	}
	return (dest);
}
