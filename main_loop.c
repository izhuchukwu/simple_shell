#include "shell.h"
#include <stdio.h>
#include <signal.h>

/**
 * signal_handler - writes new line plus prompt
 * @sig: signal
 */
void signal_handler(int sig)
{
	write(STDOUT_FILENO, "\n$ ", 3);
}
/**
 * handle_file - parses through list of commands in a file and executes
 * @filename: name of file with commands to parse through and execute
 */
void handle_file(char *filename)
{
	char *buff = NULL;
	char **tokens = NULL;
	char **ftokens = NULL;
	int i;

	/* read file and write commands to a buff */
	buff = do_mem(4096, NULL);
	buff = read_textfile(filename);

	/* separate commands in file */
	tokens = _strtok(buff, "\n");
	for (i = 0; tokens[i]; i++)
	{
		/* tokenize individual commands */
		ftokens = _strtok(tokens[i], " ");
		/* execute commands */
		execute(ftokens);
		free_double_array(ftokens);
	}
	do_mem(0, buff);
	free_double_array(tokens);
}

/**
 * main_loop - reads STDIN, tokenizes it and executes command
 *  @filename: if argv[1] exist takes in filename
 */
void main_loop(char *filename)
{
	char *buff = NULL, **tokens = NULL, *delim = " \n";
	static char *history;
	ssize_t lgetline = 0, buffsize = 4096;

	if (filename)
	{
		handle_file(filename);
	}
	else
	{
		while (1)
		{
			/* only print a prompt if isatty is true */
			if (isatty(STDIN_FILENO))
				write(STDOUT_FILENO, "$ ", 2);
			buff = do_mem(buffsize, NULL);

			/* read command, getline and check if it fails */
			while ((lgetline = _getline(buff, STDIN_FILENO)) < 0)
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

			execute(tokens);
			do_mem(0, buff);
			free_double_array(tokens);
		}
	}
}
