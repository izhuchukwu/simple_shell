#include <stdlib.h>
#include <stdio.h>

char **_free(char **list, int count)
{
    for (; count >= 0; count--)
        free(list[count]);
    free(list);
    return (NULL);
}

char **_strtok(char *str, char *delim)
{
    int i, j, len, count = 0, check  = 0;
    char **list;

    for (i = 0, count = 0; str[i]; i++)
    {
        if (str[i] == delim[0] & check)
        {
            count++;
            check = 0;
        }
        else if (str[i] != delim[0])
            check = 1;
    }
    list = malloc(count);
    if (!list)
        return (NULL);


    for (i = 0, len = 0, count = 0; str[i] || len; i++)
    {
        if ((str[i] == delim[0] || !str[i]) && len)
        {
            list[count] = malloc(sizeof(char) * len);
            if (!list[count])
                return (_free(list, count));
            for (j = 0; len; len--, j++)
                list[count][j] = str[i - len];
            count++;
            if (!str[i])
                return (list);
        }
        else if (str[i] != delim[0])
        {
            len++;
        }
    }
    return (NULL);
}
int main()
{
    char str[] = "Geeks for Geeks";

    // Returns first token
    int i = 0;
    char **token = _strtok(str, " ");

    // Keep printing tokens while one of the
    // delimiters present in str[].
    while (token[i] != NULL)
    {
        printf("%s\n", token[i]);
        i++;
    }

    return 0;
}
