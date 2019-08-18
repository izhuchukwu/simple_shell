#ifndef SHELL_H
#define SHELL_H

#include <stddef.h>
#include <unistd.h>

/**
 * struct list_s - singly linked list
 * @ptr: a malloced address
 * @next: points to the next node
 *
 * Description: singly linked list node structure
 * for Holberton shell project
 */
typedef struct list_s
{
	void *ptr;
	struct list_s *next;
} list_t;


/* Below find the linked list functions */

size_t list_len(list_t *h);

list_t *add_node(list_t **head, void *ptr);

list_t *add_node_end(list_t **head, void *ptr);

void free_list(list_t *head);

void free_list_full(list_t *head);

list_t *get_node_at_index(list_t *head, unsigned int index);

list_t *insert_node_at_index(list_t **head, unsigned int idx, void *ptr);

int delete_node_at_index(list_t **head, unsigned int index);

/* Above find the linked list functions */


/* Below find the string functions */

int _strcmp(char *, char *);

int _strlen(char *);

/* Above find the string functions */


void *do_mem(size_t size, void *ptr);

void do_exit(int fd, char *msg, int code);

ssize_t _getline(char **lineptr, size_t n, int stream);

char **_strtok(char *str, char *delim);

char **get_path(char **env);

char *get_env_val(char **env, char *name);

#endif /*SHELL_H*/
