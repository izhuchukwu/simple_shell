#ifndef SHELL_H
#define SHELL_H

#include <stddef.h>
#include <unistd.h>

extern char **environ;

/**
 * struct list_p - singly linked list
 * @ptr: a malloced address
 * @next: points to the next node
 *
 * Description: singly linked list node structure
 * for Holberton shell project
 */
typedef struct list_p
{
	void *ptr;
	struct list_p *next;
} list_t;


/* Below find the linked list functions for use with do_mem*/

size_t __list_len(list_t *h);

list_t *__add_node(list_t **head, void *ptr);

list_t *__add_node_end(list_t **head, void *ptr);

void __free_list(list_t *head);

void __free_list_full(list_t *head);

list_t *__get_node_at_index(list_t *head, unsigned int index);

list_t *__insert_node_at_index(list_t **head, unsigned int idx, void *ptr);

int __delete_node_at_index(list_t **head, unsigned int index);

/* Above find the linked list functions for use with do_mem*/

/**
 * struct list_p2 - singly linked list
 * @ptr: a malloced string
 * @next: points to the next node
 *
 * Description: singly linked list node structure
 * for Holberton shell project
 */
typedef struct list_p2
{
	char *ptr;
	struct list_p2 *next;
} list_s;


/* Below find the linked list functions */

size_t list_len(list_s *h);

list_s *add_node(list_s **head, char *ptr);

list_s *add_node_end(list_s **head, char *ptr);

void free_list(list_s *head);

void free_list_full(list_s *head);

list_s *get_node_at_index(list_s *head, unsigned int index);

list_s *insert_node_at_index(list_s **head, unsigned int idx, char *ptr);

int delete_node_at_index(list_s **head, unsigned int index);

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

char *find_path(char **path, char *command);

/* execute functions */

int execute(char **tokens, int ops);

int exec_nb(char **tokens);

int exec_builtin(char **tokens);

#endif /*SHELL_H*/
