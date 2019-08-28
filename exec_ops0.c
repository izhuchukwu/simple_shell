#include "shell.h"
#include <string.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>

/**
  * exec_builtin - execute function for builtins
  * @tokens: STDIN tokenized
  * @bcase: which builtin to execute
  * Return: 0 if succesful 1 if it fails
  */
int exec_builtin(char **tokens, int bcase)
{
	int exit = 0;
	int i = 0;

	switch (bcase)
	{
	case 1:
	{
		if (tokens[1])
		{
			for (; tokens[1][i]; i++)
				if (!_isdigit(tokens[1][i]))
				{
					do_exit(2, "numeric arguments only\n", exit);
				}
			exit = _atoi(tokens[1]);
		}
		do_exit(2, "", exit);
		break;
	}
	case 2:
		return (cd_builtin(tokens));
	case 3:
		return (env_builtin());
	}
	return (0);
}

/**
 * get_full_command - get the command with the correct path prepended
 * @path: all of the possible paths
 * @command: the base command
 * Return: the correct path + command (leave command alone if already done)
 */
char *get_full_command(char *path, char *command)
{
	int i = 0, j = 0;
	char *res = NULL;
	char **tempsplit = NULL;

	/* if command has any / in it, then return command */
	tempsplit = _strtok(command, "/");
	if (tempsplit && tempsplit[0] && tempsplit[1])
	{
		free_double_array(tempsplit);
		return (command);
	}
	free_double_array(tempsplit);

	/* else, concat the path with the command and a slash */
	i = _strlen(path);
	j = _strlen(command);
	res = do_mem(sizeof(char) * (i + j + 1 + 1), NULL);
	_strcat(res, path);
	_strcat(res, "/");
	_strcat(res, command);
	return (res);
}

/**
  * exec_nb - execute function for non builtins
  * @tokens: STDIN tokenized
  * Return: the exit status of the program, 0 if successful
  */
int exec_nb(char **tokens)
{
	char **envVars = NULL;
	char *comm = NULL;
	char *path = NULL;
	pid_t cpid, wid;
	int status = 0, accessCode = 0;

	envVars = get_path();
	path = find_path(envVars, tokens[0]);
	if (!path)
	{
		/* if no path */
	}
	comm = get_full_command(path, tokens[0]);
	/* check if path exists */
	accessCode = access(comm, F_OK);
	if(accessCode)
	{
		/* not found */
		my_error(tokens[0], 2, NULL);
		return (2);
	}
	/* check if path is exucatable */
	accessCode = access(comm, X_OK);
	if(accessCode)
	{
		/* Permission denied */
		my_error(tokens[0], 126, NULL);
		return (126);
	}
	/* fork and exec */
	cpid = fork();
	/* Fork failed - exits with error message and exit code */
	if (cpid == -1)
		do_exit(2, "Fork failed", EXIT_FAILURE);
	if (!cpid)/* child */
	{
		execve(comm, tokens, (char * const *)get_env());
		perror("");
		do_exit(2, "Couldn't exec", EXIT_FAILURE);
	}
	else/* parent */
	{
		do {
			free_double_array(envVars);
			wid = waitpid(cpid, &status, WUNTRACED);
			if (wid == -1)
			{
				perror("waitpid");
				do_exit(STDERR_FILENO, "", EXIT_FAILURE);
			}
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
		do_mem(0, comm);
	}
	return (status);
}

/**
  * search_ops - search for ;, &&, || operators
  * @tokens: tokens from std input
  * Return: 0 if none, 1 if ';', 2 if '&&' 3 if '||'
  */
int search_ops(char **tokens)
{
	int i = 0;

	if (!tokens)
	{
		return (0);
	}
	for (i = 0; tokens[i]; i++)
	{
		/* check for ;, &&, || */
		if (tokens[i][0] == ';')
			return (1);
		if (tokens[i][0] == '&' && tokens[i][1] && tokens[i][1] == '&')
			return (2);
		if (tokens[i][0] == '|' && tokens[i][1] && tokens[i][1] == '|')
			return (3);
	}
	return (0);
}
