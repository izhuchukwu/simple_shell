#include "shell.h"
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>

char *get_env_val(char **, char*);

/**
 * get_path - get the path in a double char pointer
 * @env: the environment to get it from
 * Return: the double char pointer of the path
 */
char **get_path(char **env)
{
	return (_strtok(get_env_val(env, "PATH"), ":"));
}

/**
 * get_env_val - get the value of an env variable
 * @env: the environment to get the variable out of
 * @name: the name of the variable to get the value of
 * Return: the string pointer to where the value part of the variable starts
 */
char *get_env_val(char **env, char *name)
{
	int i = 0, j = 0;

	while (env[i])
	{
		j = 0;
		while (env[i][j] && name[j])
		{
			if (env[i][j] != name[j])
				break;
			j++;
		}
		/* j only counts until null byte if name matches */
		if (name[j] == '\0' && env[i][j] == '=')
			return ((env[i]) + j + 1);
		i++;
	}
	return (NULL);
}

/**
  * find_path - finds if a command exists in a path and returns the path
  * @path: paths to search
  * @command: command to search for
  * Return: path where command is
  */
char *find_path(char **path, char *command)
{
	/* pointer for directory entry  & opendir returns a pointer of DIR type*/
	struct dirent *de = NULL;
	DIR *dr = NULL;
	int i = 0;

	if (!command)
		return (NULL);
	for (i = 0; path[i]; i++)
	{
		dr = opendir(path[i]);
		/* opendir returns NULL if couldn't open directory */
		if (!dr)
		{
			write(STDOUT_FILENO, "Could not open directory\n", 25);
			closedir(dr);
			return (NULL);
		}
		while ((de = readdir(dr)) != NULL)
		{
			if (_strcmp((*de).d_name, command) == 0)
			{
				closedir(dr);
				return (path[i]);
			}
		}
		closedir(dr);
	}
	return (NULL);
}

/**
 * get_env - get the current environment as a malloc'd, NULL terminating char**
 * Return: the environment as a char**
 */
char **get_envir(void)
{
	return (do_env(NULL, NULL));
}
