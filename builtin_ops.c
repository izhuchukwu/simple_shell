#include "shell.h"

/**
 * cd_builtin - executes cd function, changes directory
 * @tokens: command input into prompt tokenized
 */
void cd_builtin(char **tokens)
{
	char *HOME = NULL, *lastdir = NULL;

	(void)HOME;
	lastdir = do_mem(100, NULL);
	if (_strcmp(tokens[1], "-") == 0)
	{
		/* go to previous directory */
		chdir(lastdir);
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
