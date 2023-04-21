#include "main.h"

/* main - ads /bin to anexisting input command
 *
 * Return: always 0
 */

int dir_ext(char *str)
{
	DIR *dir;
	char *fn, *fname, *nfname;
	char req_dir[100] = "/bin/";
	struct dirent* entity;
	
	dir = opendir(req_dir);
	if (dir == NULL)
	{
		return 1;
	}

	entity = readdir(dir);
	printf("fn = %s\n", fn);
	while (entity != NULL)
	{
		fname = entity->d_name;
		/*printf("%s\n", entity->d_name);*/
		if (strcmp(fname, str) == 0)
		{
			printf("function found\n");
			str = (char *)malloc(100);
			str = strcat(req_dir, fname);
			printf("New function: %s\n", nfname);
			break;
		}
		else
		{
			return (-1);
		}		
		entity = readdir(dir);
	}
	closedir(dir);

	return 0;
}
