#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

/**
  * main - simple shell
  * Return: 0 if succesful
  */
int main(int argc, char **argv, char **envp)
{
	char *filename = NULL;
	/*
	* argc the right amount of arguments */
	if (argc > 2)
		return (-1);

	/* check if argv[1] is a file */
	if (argv && argv[1])
		filename = argv[1];
	/* signal handler */
	signal(SIGINT, signal_handler);
	/* initialize the environment */
	do_env((char*)envp, NULL);

	/* read, tokenize, execute loop */
	main_loop(filename);

	/* clean up */

	return (0);
}
