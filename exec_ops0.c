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

	switch (bcase)
	{
	case 1:
		if (tokens[1])
			exit = atoi(tokens[1]);
		do_exit(2, "", exit);
		return (exit);
	case 2:
		return (cd_builtin(tokens));
	case 3:
		return (env_builtin(tokens));
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
	pid_t cpid, wid;
	int status;

	envVars = get_path();
	comm = get_full_command(find_path(envVars, tokens[0]), tokens[0]);

	/* fork and exec */
	cpid = fork();
	if (cpid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE); /* return 0? */
	}
	if (!cpid)
	{
		/* child */
		execve(comm, tokens, (char * const *)get_env());
		perror("");
		do_exit(2, "Couldn't exec", 1);
	}
	else
	{
		/* parent */
		do {
			free_double_array(envVars);
			wid = waitpid(cpid, &status, WUNTRACED);
			if (wid == -1)
			{
				perror("waitpid");
				exit(EXIT_FAILURE);/* return 0? */
			}
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}
	return (status);
}

/**
  * search_ops - search for ;, &&, || operators
  * @token: token from std input
  * Return: 0 if none, 1 if ';', 2 if '&&' 3 if '||'
  */
int search_ops(char **tokens)
{
	int i = 0;

	if (!tokens)
		return (0);
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
