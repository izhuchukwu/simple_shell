#include "shell.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

/**
 * _getline2 - reads 1024 characters from stdin
 * Return: the string read in
 */
char *_getline2()
{
	char *line = NULL, *word = NULL;
	ssize_t lread;

	/* mallocs word and checks if it fails */
	while (!(word = do_mem(1024, NULL)))
		return (NULL);

	/* reads std input and checks if it fails */
	while ((lread = read(STDIN_FILENO, line, 1024)) == -1)
		return (NULL);

	return (line);
}

/**
 * _getline - reads a number of chars from stdin
 * @lineptr: the buffer to put the data in
 * @n: the number of bytes to read
 * @stream: the stream to read from
 * Return: the number of bytes read
 */
ssize_t _getline(char **lineptr, size_t n, int stream)
{
	ssize_t lread;

	/* reads std input and checks if it fails */
	lread = read(stream, *lineptr, n);

	return (lread);
}
