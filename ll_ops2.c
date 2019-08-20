#include "shell.h"

char **arrayify(list_s *head)
{
	char **ret = NULL;
	char *tmp = NULL;
	int len = 0, i = 0;

	len = list_len(head);
	ret = do_mem(sizeof(char *) * (len + 1), NULL);
	for (i = 0; i < len; i++)
	{
		tmp = do_mem(sizeof(char) * (_strlen(get_node_at_index(head, i)->ptr) + 1), NULL);
		tmp = _strcat(tmp, get_node_at_index(head, i)->ptr);
		ret[i] = tmp;
	}
	ret[i] = NULL;
	return (ret);
}

list_s *listify(char **arr)
{
	list_s *ret = NULL;
	char *tmp = NULL;
	int i = 0;

	while (arr[i])
	{
		tmp = do_mem(sizeof(char) * (_strlen(arr[i]) + 1), NULL);
		tmp = _strcat(tmp, arr[i]);
		add_node_end(&ret, tmp);
		i++;
	}
	return (ret);
}
