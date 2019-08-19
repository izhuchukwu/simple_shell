#include "shell.h"

/**
  * exec_builtin - execute function for builtins
  * @tokens: STDIN tokenized
  * Return: 1 if succesful 0 if it fails
  */
int exec_builtin(char **tokens)
{
	int i;

	for (i = 1 ; tokens[i]; i++)
	{
		if (i != 1)
			write(STDOUT_FILENO, " ", 1);
		write(STDOUT_FILENO, tokens[i], _strlen(tokens[i]));
	}
	return (1);

}

/**
  * exec_nb - execute function for non builtins
  * @tokens: STDIN tokenized
  * Return: 1 if succesful 0 if it fails
  */
int exec_nb(char **tokens)
{
	extern char **environ;
	char **envVars;
	int i, checkOps = 0;

	envVars = get_path(environ);

	/* fork and exec */

	/* print stdin minus command */
	for (i = 1 ; tokens && tokens[0] && tokens[i]; i++)
	{
		checkOps = search_ops(tokens[i]);
		if (checkOps)
			break;
		if (i != 1)
			write(STDOUT_FILENO, " ", 1);
		write(STDOUT_FILENO, tokens[i], _strlen(tokens[i]));
	}
	return (1);
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
	int checkBuiltIn = 0, i, len, count, works = 0, op = 0;
	static char **builtins;

	builtins = do_mem(sizeof(char *), NULL);
	builtins[0] = NULL;

	/* check if its a builtin */
	for (i = 0; builtins[i]; i++)
		if (_strcmp(builtins[i], tokens[0]) == 0)
			checkBuiltIn = 1;

	if (checkBuiltIn && tokens)
		works = exec_builtin(tokens);
	else if (tokens)
		works = exec_nb(tokens);
	/* check for ;, &&, || */
	for (i = 0, count = 0; tokens && tokens[i]; i++)
	{
		op = search_ops(tokens[i]);
		if (op)
			count++;
		if (((op == 1) || (op == 2 && works) || (op == 3 && !works)) && count > ops)
		{
			i++;
			ops += 1;
			execute(tokens + i, ops);
		}
	}
	return (0);
}

