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
ssize_t _getline(char *lineptr, int stream)
{
        static int input[4096];
	static int filled;
	int newline_index = -1, i = 0, tmp = 2;
	ssize_t ret = 0;

	/* if the buffer is empty, fill it */
	if (!filled)
	{
		read(stream, input, 4096);
		filled = 4096;
	}


	/* if the buffer contains \n or EOF */
	newline_index = has_newline(input);
	if (newline_index != -1)
	{
		for(i = 0; i <= newline_index; i++)
		{
			lineptr[i] = input[i];
		}
		ret = newline_index + 1;

		/* Shift any remaining chars to the left */
		shiftbuffer(input, newline_index, filled);
		filled = filled - ret;

		return (ret);
	}
	/* if the buffer doesn't contain \n or EOF */
	else
	{
		/* if the buffer is full then read until \n or EOF */
		if (filled == 4096)
		{
			/* should always fill buffer with \n or EOF at end*/
			while(tmp != -1 && tmp != '\n')
				tmp = read(stream, &tmp, 1);
			input[4095] = tmp;
			return (_getline(lineptr, stream));
		}
		/* if the buffer isn't full, then fill it and try again. */
		else
		{
			read(stream, input + filled, 4096 - filled);
			return (_getline(lineptr, stream));
		}

	}

	return (-1);
}
