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
		return (0);
	case 2:
		cd_builtin(tokens);
		return (0);
	}
	return (1);
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
		return (command);
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
int search_ops(char *token)
{
	/* check for ;, &&, || */
	if (token[0] == ';')
		return (1);
	if (!token[0] || !token[1])
		return (0);
	if (token[0] == '&' && token[1] == '&')
		return (2);
	if (token[0] == '|' && token[1] == '|')
		return (3);
	return (0);
}

/**
  * execute - main execute function
  * @tokens: STDIN tokenized
  * @ops: number of operation we are in
  * Return: int if succesful
  */
int execute(char **tokens, int ops)
{
	int checkBuiltIn = 0, i, count, works = 0, op = 0, commandSize = 0;
	char **builtins, **extokens;

	/* split tokens into separate commands if ;,&&,|| exist */
	commandSize = sizeof_command(tokens, ops);
	extokens = do_mem(sizeof(char *) * (commandSize + 1), NULL);
	for (i = 0; i < commandSize; i++)
	{
		extokens[i] = do_mem(_strlen(tokens[i]) + 1, NULL);

		_strcpy(extokens[i], tokens[i]);
	}
	extokens[i] = NULL;
	builtins = get_builtins();

	/* check if its a builtin */
	for (i = 0; builtins[i]; i++)
		if (_strcmp(builtins[i], tokens[0]) == 0)
			checkBuiltIn = i + 1;

	if (checkBuiltIn && tokens)
		works = exec_builtin(extokens, checkBuiltIn);
	else if (tokens)
		works = exec_nb(extokens);
	/* check for ;, &&, || */
	for (i = 0, count = 0; tokens && tokens[i]; i++)
	{
		op = search_ops(tokens[i]);
		if (op)
			count++;
		if (((op == 1) || (op == 2 && !works) || (op == 3 && works)) && count > ops)
		{
			i++;
			ops += 1;
			execute(tokens + i, ops);
		}
	}
	return (0);
}
