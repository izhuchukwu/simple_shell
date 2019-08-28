#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>


/**
 * linum - get current line number and/or add to it
 * @add: if not zero, add this amt
 * Return: the line number
 */
int linum(int add)
{
	static int line;

	line = line + add;
	return (line);
}

/**
 * get_prog_name - gets the program name
 * @name: the name of the prog (first execution)
 * Return: the name of the program
 */
char *get_prog_name(char *name)
{
	static char *ret;

	if (!ret)
	{
		ret = name;
	}
	return (ret);
}

/**
 * my_error - custom error printing
 * @msg: the message to print
 */
void my_error(char *msg)
{
	char *name;
	char *line;

	name = get_prog_name(NULL);
	line = _itoa(linum(0));
	write(STDERR_FILENO, name, _strlen(name));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, line, _strlen(line));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, msg, _strlen(msg));
	write(STDERR_FILENO, "\n", 1);
}


/**
  * main - simple shell
  * @argc: Number of arguments
  * @argv: list of arguments
  * @envp: environment
  * Return: 0 if successful
  */
int main(int argc, char **argv, char **envp)
{
	char *filename = NULL;

	get_prog_name(argv[0]);

	/* argc the right amount of arguments */
	if (argc > 2)
		return (-1);

	/* check if argv[1] is a file */
	if (argv && argv[1])
		filename = argv[1];
	/* signal handler */
	signal(SIGINT, signal_handler);
	/* initialize the environment */
	do_env((char *)envp, NULL);

	/* initialize the linum */
	linum(1);

	/* read, tokenize, execute loop */
	main_loop(filename);

	/* clean up */

	return (0);
}
