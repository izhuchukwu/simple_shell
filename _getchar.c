#include <unistd.h>
#include <stdio.h>

int _getchar(void)
{
    char c;

    return (read(0, &c, 1) == 1 ? (unsigned char) c : EOF);
}