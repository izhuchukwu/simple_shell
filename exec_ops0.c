#include "shell.h"

/**
  * exec_nb - execute function for builtins
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
	int i;

	envVars = get_path(environ);

	/* fork and exec */

	/* print stdin minus command */
	for (i = 1 ; tokens[i]; i++)
	{
		if (i != 1)
			write(STDOUT_FILENO, " ", 1);
		write(STDOUT_FILENO, tokens[i], _strlen(tokens[i]));
	}
	return (1);
}

/**
  * execute - main execute function
  * @tokens: STDIN tokenized
  * Return: int if succesful
  */
int execute(char **tokens)
{
	int checkBuiltIn = 0, i, len, worked = 0, shift = 0;
	static char **builtins;
	char **copyTokens;

	for (i = 0; tokens[i]; i++)
		;
	copyTokens = do_mem(sizeof(char*) * i, NULL);
	for (i = 0; tokens[i]; i++)
	{
		for (len = 0; tokens[i][len]; len++)
			;
		copyTokens = do_mem(len, NULL);
	}
	copyTokens = tokens;
	builtins = do_mem((sizeof(char *)), NULL);
	builtins[0] = NULL;

	/* check if its a builtin */
	for(i = 0; builtins[i]; i++)
		if (_strcmp(builtins[i], tokens[0]) == 0)
			checkBuiltIn = 1;

	if (checkBuiltIn)
		worked = exec_builtin(tokens);
	else
		worked = exec_nb(tokens);
	/* check for ;, &&, || */
	for (; copyTokens && copyTokens[0] && copyTokens[0][0]; copyTokens++)
	{
		if (copyTokens[0][0] == ';')
			shift = 1;
		if (copyTokens[0][0] == '&' && copyTokens[0][1] == '&' && worked)
			shift = 2;
		if (copyTokens[0][0] == '|' && copyTokens[0][1] == '|' && !worked)
			shift = 2;
		if (shift)
		{
			copyTokens[0] + shift;
			execute(copyTokens);
		}
	}
	return (0);
}

