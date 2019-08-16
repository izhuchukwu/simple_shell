#include <stdio.h>
#include <unistd.h>

char *_getline2()
{
    char *line;
    ssize_t lread;

    /* mallocs word and checks if it fails */
    while (!(word = malloc(1024)))
        return (NULL);

    /* reads std input and checks if it fails */
    while ((lread = read(STDIN_FILENO, line, 1024)) == -1)
        return (NULL)

    return (line);
}

ssize_t _getline(char **lineptr, size_t *n, int stream)
{
    ssize_t lread;

    /* reads std input and checks if it fails */
    lread = read(stream, *lineptr, *n))

    return (lread);
}
int main(void)
    {
        char *buff;
        ssize_t lwrite, lgetline, buffsize = 1024;

        buff = _getline2();
        /* write and check if it fails */
        while ((lwrite = write(STDOUT_FILENO, buff, 1024)) == -1)
            return (-1);
        free(buff);
        /* malloc space for buff and checks if it fails */
        while (!(buff = malloc(buffsize))
            return (-1);
        /* call getline and write output until it fails */
        while ((lgetline = _getline(buff, buffsize, STDIN_FILENO)) != -1)
            write(STDOUT_FILENO, buff, lgetline);
        free (buff);
        return (0);
    }