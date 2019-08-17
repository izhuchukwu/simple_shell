#include "shell.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * do_mem - malloc, free, or free all with a static record
 * @size: the size to malloc if non-0
 * @ptr: the pointer to free if non-NULL
 * return: the malloc'd pointer if malloc, otherwise the result of free
 */
void *do_mem(size_t size, void *ptr)
{
	static list_t *all;
	void *ret = NULL;
	int i = 0, len = 0;

	if (size)
	{
		ret = malloc(size);
		add_node_end(&all, ret);
		return (ret);
	}
	else if (ptr)
	{
		len = list_len(all);
		for (i = 0; i < len; i++)
		{
			if(get_node_at_index(all, i)->ptr == ptr)
			{
				delete_node_at_index(&all, i);
			}
		}
		free(ptr);
		return (NULL);
	}
	else
	{
		/* If neither size nor ptr, then nuke everything. */
		free_list_full(all);
		return (NULL);
	}
	return (NULL);
}

/**
 * do_exit - custom exit with error message, code, and automatic memory cleanup
 * @fd: the file descriptor to write the message
 * @msg: the message to print
 * @code: the numerical exit code
 */
void do_exit(int fd, char *msg, int code)
{
	int msglen = 0;

	if (*msg)
	{
		/* print message */
		while (msg[msglen])
			msglen++;
		write(fd, msg, msglen);
	}

	/* nuke extra memory */
	do_mem(0,NULL);

	/* exit with code */
	exit(code);
}
