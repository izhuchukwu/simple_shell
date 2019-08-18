#include "shell.h"
#include <stdio.h>
#include <stdlib.h>

/**
  * main - simple shell
  * Return: 0 if succesful
  */
int main(void)
{
	char *buff = NULL, **tokens = NULL, *delim = " ";
	ssize_t lgetline = 0, buffsize = 1024;
	int i = 0;

	while (1)
	{
		/* write prompt */
		/* isatty should be checked here (if true, print prompt) */
		write(STDOUT_FILENO, "$ ", 2);
		buff = do_mem(buffsize, NULL);

		/* read command, getline and write output until it fails */
		while ((lgetline = _getline(&buff, buffsize, STDIN_FILENO)) < 0)
		{
			do_mem(0, buff);
			do_exit(2, "", -1);
		}

		/* check for exit command */
		if ((_strcmp(buff, "exit\n")) == 0)
			do_exit(2, "", 100);
		tokens = _strtok(buff, delim);
		for (i = 0; tokens[i]; i++)
		{
			write(STDOUT_FILENO, tokens[i], _strlen(tokens[i]));
			write(STDOUT_FILENO, " ", 1);
		}
	}
	do_mem(0, buff);
	return (0);
}
