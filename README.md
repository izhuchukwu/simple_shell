# SIMPLE SHELL

## Description

Project 0x16 - Simple Shell
Write a simple UNIX command interpreter.

## List of Allowed Functions and System Calls

[access](https://linux.die.net/man/2/access) (man 2 access)
[chdir](http://man7.org/linux/man-pages/man2/chdir.2.html) (man 2 chdir)
[close](http://man7.org/linux/man-pages/man2/close.2.html) (man 2 close)
[closedir](https://linux.die.net/man/3/closedir) (man 3 closedir)
[execve](http://man7.org/linux/man-pages/man2/execve.2.html) (man 2 excve)
[exit](http://man7.org/linux/man-pages/man3/exit.3.html) (man 3 exit)
[_exit](https://linux.die.net/man/2/_exit) (man 2 _exit)
[fflush](https://linux.die.net/man/3/fflush) (man 3 fflush)
[fork](http://man7.org/linux/man-pages/man2/fork.2.html) (man 2 fork)
[free](https://linux.die.net/man/3/free) (man 3 free)
[getcwd](http://man7.org/linux/man-pages/man3/getcwd.3.html) (man 3 getcwd)
[getline](https://linux.die.net/man/3/getline) (man 3 getline) - Bonus if not used
[isatty](http://man7.org/linux/man-pages/man3/isatty.3.html) (man 3 isatty)
[kill](http://man7.org/linux/man-pages/man2/kill.2.html) (man 2 kill)
[malloc](http://man7.org/linux/man-pages/man3/malloc.3.html)(man 3 malloc)
[open](http://man7.org/linux/man-pages/man2/open.2.html) (man 2 open)
[opendir](http://man7.org/linux/man-pages/man3/opendir.3.html) (man 3 opendir)
[perror](http://man7.org/linux/man-pages/man3/perror.3.html) (man 3 perror)
[read](http://man7.org/linux/man-pages/man2/read.2.html) (man 2 read)
[readdir](http://man7.org/linux/man-pages/man3/readdir.3.html) (man 3 readdir)
[signal](http://man7.org/linux/man-pages/man2/signal.2.html) (man 2 signal)
[stat](https://linux.die.net/man/2/stat) (__xstat)(man 2 stat)
[lstat](https://linux.die.net/man/2/lstat) (__lxstat)(man 2 lstat)
[fstat](https://linux.die.net/man/2/fstat) (__fxstat)(man 2 fstat)
[strtok](http://man7.org/linux/man-pages/man3/strtok.3.html) (man 3 strtok) - Bonus if not used
[wait](https://linux.die.net/man/2/wait) (man 2 wait)
[waitpid](https://linux.die.net/man/2/waitpid) (man 2 waitpid)
[wait3](https://linux.die.net/man/2/wait3) (man 2 wait3)
[wait4](http://man7.org/linux/man-pages/man2/wait4.2.html) (man 2 wait4)
[write](http://man7.org/linux/man-pages/man2/write.2.html) (man 2 write)

## Installing

Compile:
```bash
gcc -Wall -Wextra -Werror -pedantic *.c -o hsh
```
## Usage



## File Structure

0. [my_shell.c](my_shell.c) - The main function for simple_shell
* ``int main(int argc, char **argv, char **envp)``

1. [env_ops0.c](env_ops0.c) - Environmental variable functions
* ``char *get_env_val(char **, char*)`` - Gets the value of an env variable
* ``char **get_path(char **env)`` - Gets the path in a double char pointer
* ``char *find_path(char **path, char *command)`` - finds if a command exist in a path and returns the path
* ``char **get_env(void)`` - Get current environment as a malloc'd NULL

2. [env_ops1.c](env_ops1.c) - More environment variable functions
* ``char **do_env(char *add, char *delete)`` - Get the env, or add a variable, or delete a variable

3. [ll_ops0.c](ll_ops0.c) - Linked list functions
* ``size_s list_len(list_s *h)`` - Gets size of a list_s linked list
* ``list_s *(add_node(list_s **head, void *ptr)`` - Adds a new node at the beginning of a list_s linked list
* ``list_s *add_node_end(list_s **head, void *ptr)`` - Adds a new node at the end of a list_s linked list
* ``void free_list(list_s *head)`` - Frees list_s linked list

4. [ll_ops1.c](ll_ops1.c) - More linked list functions
* ``void free_list_full(list_s *head)`` - Frees list_s linked list and all contained pointers
* ``list_s *get_node_at_index(list_s *head, unsigned int index)`` - Returns the nth node of a linked list
* ``list_s *insert_node_at_index(list_s **head, unsigned int idx, void *ptr)`` - Inserts a new node at a given position
* ``int delete_node_at_index(list_s **head, unsigned int index)`` - Deletes a node at a given position

5. [ll_ops2.c](ll_ops2.c) - More linked list functions
* ``char **arrayify(list_s *head)`` - copy a char * linked list into a char **
* ``list_s listify(char **arr)`` - copy a char ** array into a malloc'd char * linked list 
* ``void free_double_array(char **list)`` - Free a double char pointer

6. [str_ops0.c](str_ops0.c) - String functions
* ``int _strcmp(char *s1, char *s2)`` - Compares two strings
* ``int _strlen(char *s)`` - Gets the length of a string
* ``int word_count(char *str, char *delim)`` - counts the number of words in a string separated by a delim
* ``char *_strcat(char *dest, char *src)`` - Concats two strings
* ``char *_strcpy(char *dest, char *src)`` - Copy src into dest

7. [str_ops1.c](str_ops1.c) - More string functions
* ``int _atoi(char *s)`` - Converts a string to an integer
* ``int sizeof_command(char **tokens, int place)`` - Gets the size a command separated by ;, &&, ||

8. [my_exit.c](my_exit.c) - Memory and exit functions
* ``void *do_mem(size_t size, void *ptr)`` - Malloc, free or free all with a static record
* ``void do_exit(int fd, char *msg, int code)`` - Custo exit with error message, code and automatic memory cleanup

9. [strtok_to_double_pointer.c](strtok_to_double_pointer.c) - strtok function that returns double pointer
* ``void _free(char **list, int count)`` - Frees a double char pointer in case of error
* ``char **_strtok(char *str, char *delim)`` - Splits a string into an array of strings based on delimiter

10. [_getline.c](_getline.c) - getline function
* ``char *_getline2()`` - Reads 1024 characters from stdin and returns the string read
* ``ssize_t _getline(char **lineptr, size_t n, int stream)`` - Reads a number of chars from stdin and returns size read

11. [builtin_ops.c](builtin_ops.c) - functions for builtin commands
* ``char **get_builtins()`` - Create list of builtin functions
* ``void cd_builtin(char **tokens)`` - Executes cd function, changes directory

12. [file_ops.c](file_ops.c) - Prep input file to execute list of commands
* ``char *read_textfile(char *filename)`` - read text file and return as string

## Authors

* Jose Alvarez de Lugo
* William Dyrland-Marquis
