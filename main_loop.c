#include "shell.h"

/**
 * main_loop - reads STDIN, tokenizes it and executes command
 */
void main_loop(void)
{
	char *buff = NULL, **tokens = NULL, *delim = " \n";
	ssize_t lgetline = 0, buffsize = 1024;
	int i = 0;

	while (1)
	{
		/* isatty should be checked here (if true, print prompt) */
		write(STDOUT_FILENO, "$ ", 2);
		buff = do_mem(buffsize, NULL);

		/* read command, getline and check if it fails */
		while ((lgetline = _getline(&buff, buffsize, STDIN_FILENO)) < 0)
		{
			do_mem(0, buff);
			do_exit(2, "", -1);
		}
		/* exit if ctrl- d */
		if (lgetline == 0)
			do_exit(2, "",100);
		/* check for exit command */
		if ((_strcmp(buff, "exit\n")) == 0)
			do_exit(2, "", 100);

		/* tokenize STDIN */
		tokens = _strtok(buff, delim);

		//execute(tokens, 0);
		
		for (i = 0; tokens && tokens[i]; i++)
		{
			write(STDOUT_FILENO, tokens[i], _strlen(tokens[i]));
			write(STDOUT_FILENO, " ", 1);
		}
		
	}
	/* clean memory */
	do_mem(0, buff);
}
