#include "shell.h"

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
