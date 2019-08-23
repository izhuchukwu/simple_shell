#include "shell.h"

/**
  * get_builtins - list of builtin commands
  * Return - double pointer holding list of commands
  */
char **get_builtins()
{
	char **builtins;

	builtins = do_mem(sizeof(char *) * 3, NULL);

	builtins[0] = "exit";
	builtins[1] = "cd";
	builtins[2] = NULL;

	return (builtins);
}


/**
 * cd_builtin - executes cd function, changes directory
 * @tokens: command input into prompt tokenized
 */
void cd_builtin(char **tokens)
{
	char *HOME = NULL, *templd;
	static char *lastdir;

	(void)HOME;
	if (!lastdir)
		lastdir = do_mem(100, NULL);
	templd = do_mem(100, NULL);
	if (tokens[1] && _strcmp(tokens[1], "-") == 0)
	{
		/* go to previous directory */
		getcwd(templd, 100);
		chdir(lastdir);
		write(STDOUT_FILENO, lastdir, _strlen(lastdir));
		write(STDOUT_FILENO, "\n", 1);
		lastdir = templd;
	}
	else if (tokens[1])
	{
		/* change directory to tokens[1] */
		getcwd(lastdir, 100);
		chdir(tokens[1]);
	}
	else
	{
		/* change to home directory */
		getcwd(lastdir, 100);
		chdir(get_env_val(environ, "HOME"));
	}
}
