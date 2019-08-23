#include "shell.h"
#include <stdio.h>
/**
 * main_loop - reads STDIN, tokenizes it and executes command
 */
void main_loop(char *filename)
{
	char *buff = NULL, **tokens = NULL, **ftokens, *delim = " \n";
	static char *history;
	ssize_t lgetline = 0, buffsize = 1024;
	int i = 1, j;

	while (i)
	{
		if (filename)
		{
			/* read file and write commands to a buff */
			buff = do_mem(4096, NULL);
			buff = read_textfile(filename);
			i = 0;
			/* separate commands in file */
			tokens = _strtok(buff, "\n");
			for (j = 0; tokens[j]; j++)
			{
				/* tokenize individual commands */
				ftokens = _strtok(tokens[j], " ");
				/* execute commands */
				execute(ftokens, 0);
			}
		}
		else
		{
			/* only print a prompt if isatty is true */
			if (isatty(STDIN_FILENO))
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
				do_exit(2, "", 100);
			/* check for exit command */
			if ((_strcmp(buff, "exit\n")) == 0)
				do_exit(2, "", 100);
		
			/* tokenize STDIN */
			tokens = _strtok(buff, delim);

			execute(tokens, 0);
		}
	}
	/* clean memory */
	do_mem(0, buff);
}
