#include "shell.h"
#include <stdlib.h>
#include <unistd.h>

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
	char *s = NULL;
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
			return (env[i][j + 1]);
		i++;
	}
	return (NULL);
}
