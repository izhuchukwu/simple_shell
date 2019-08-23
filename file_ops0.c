#include "shell.h"
#include <fcntl.h>
#include <stdlib.h>

/**
  * read_textfile - 
  *
  *
  *
  */

char *read_textfile(char *filename)
{
	char *buff;
	int of;
	ssize_t lRead;

	if (!filename)
		return (NULL);
	/* allocate memory for content of file */
	buff = do_mem(4096, NULL);
	if (!buff)
		return (NULL);
	
	/* open file */
	of = open(filename, O_RDONLY);
	if (of == -1)
	{
		/* should I use free here ?? */
		free(buff);
		return (NULL);
	}

	/* read file up to the size of the buffer 4096 */
	lRead = read(of, buff, 4096);
	if (lRead < 1)
	{
		/* should I use free here ?? */
		free(buff);
		close(of);
		return (NULL);
	}

	/* check if close fails? */
	close(of);

	return (buff);
}
