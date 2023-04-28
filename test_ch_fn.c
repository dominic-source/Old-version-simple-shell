#include "main.h"

/**
 * main - adds /bin to an existing input command
 * @str: str
 * Return: 0 on success and -1 on failure
 */
SRCH *dir_ext(char *str)
{
	DIR *dir;
	char *fname, *req_dir = "/bin/";
	SRCH *new_str;
	struct dirent *entity;
	int length = 0;

	dir = opendir(req_dir);
	if (dir == NULL)
		return (NULL);
	entity = readdir(dir);
	if (entity == NULL)
		return (NULL);
	if (_strncmp(req_dir, str, 5) == 0)
		str = &str[5];
	while (entity != NULL)
	{
		fname = entity->d_name;
		if (_strcmp(fname, str) == 0)
		{
			new_str = malloc(sizeof(SRCH));
			if (new_str == NULL)
				return (NULL);
			length = _strlen(fname) + _strlen(req_dir) + 1;
			new_str->str = malloc(sizeof(char) * length);
			if (new_str->str == NULL)
			{
				free(new_str);
				return (NULL);
			}
			new_str->str[0] = '\0';
			new_str->str = _strcat(new_str->str, req_dir);
			new_str->str = _strcat(new_str->str, fname);
			new_str->val = 0;
			closedir(dir);
			return (new_str);
		}
		entity = readdir(dir);
	}
	closedir(dir);
	return (NULL);
}

/**
 * free_mem_sh - free memories
 * @count: argument
 * @argv: arguments from command line
 */
void free_mem_sh(char **argv, int count, ...)
{
	char *ptr;
	va_list ap;
	int i;

	for (i = 0; argv[i] != NULL; i++)
		free(argv[i]);

	free(argv);
	va_start(ap, count);
	for (i = 0; i < count; i++)
	{
		ptr = va_arg(ap, char *);
		free(ptr);
	}
	va_end(ap);
}

