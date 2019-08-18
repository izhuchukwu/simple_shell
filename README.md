# SIMPLE SHELL

## Description

Simple shell project for Holberton

## Installing

Compile:
```bash
gcc -Wall -Wextra -Werror -pedantic *.c -o hsh
```
## Usage



## File Structure

0. [my_shell.c](my_shell.c) - The main function for simple_shell
* ``int main(void)``

1. [env_ops0.c](env_ops0.c) - Environmental variable functions
* ``char *get_env_val(char **, char*)`` - Gets the value of an env variable
* ``char **get_path(char **env)`` - Gets the path in a double char pointer

2. [ll_ops0.c](ll_ops0.c) - Linked list functions
* ``size_t list_len(list_t *h)`` - Gets size of a list_t linked list
* ``list_t *(add_node(list_t **head, void *ptr)`` - Adds a new node at the beginning of a list_t linked list
* ``list_t *add_node_end(list_t **head, void *ptr)`` - Adds a new node at the end of a list_t linked list
* ``void free_list(list_t *head)`` - Frees list_t linked list

3. [ll_ops1.c](ll_ops1.c) - More linked list functions
* ``void free_list_full(list_t *head)`` - Frees list_t linked list and all contained pointers
* ``list_t *get_node_at_index(list_t *head, unsigned int index)`` - Returns the nth node of a linked list
* ``list_t *insert_node_at_index(list_t **head, unsigned int idx, void *ptr)`` - Inserts a new node at a given position
* ``int delete_node_at_index(list_t **head, unsigned int index)`` - Deletes a node at a given position

4. [str_ops0.c](str_ops0.c) - String functions
* ``int _strcmp(char *s1, char *s2)`` - Compares two strings
* ``int _strlen(char *s)`` - Gets the length of a string

5. [my_exit.c](my_exit.c) - Memory and exit functions
* ``void *do_mem(size_t size, void *ptr)`` - Malloc, free or free all with a static record
* ``void do_exit(int fd, char *msg, int code)`` - Custo exit with error message, code and automatic memory cleanup

6. [strtok_to_double_pointer.c](strtok_to_double_pointer.c) - strtok function that returns double pointer
* ``void _free(char **list, int count)`` - Frees a double char pointer in case of error
* ``char **_strtok(char *str, char *delim)`` - Splits a string into an array of strings based on delimiter

7. [_getline.c](_getline.c) - getline function
* ``char *_getline2()`` - Reads 1024 characters from stdin and returns the string read
* ``ssize_t _getline(char **lineptr, size_t n, int stream)`` - Reads a number of chars from stdin and returns size read


## Authors

* Jose Alvarez de Lugo
* William Dyrland-Marquis
