#include <stdlib.h>
#include <stdio.h>

char *_free(char **list, int count)
{
    for (; count >= 0; count--)
        free(list[count]);
    free(list);
    return (NULL);
}

char *_strtok(char *str, char *delim)
{
    int i;
    static char *staticStr;
    static int len;
    printf("inside strtok\n");
    if (str)
    {
    for (len = 0; str[len]; len++)
        printf("%d\n", len);

    if ((staticStr = malloc(sizeof(char *) * len + 1)) == NULL)
        return (NULL);

    for (i = 0; str[i] ; i++)
    {
        printf("here 1\n");
        if (str[i] == delim[0])
            staticStr[i] = '\0';
        staticStr[i] = str[i];
    }
    for (; *staticStr == '\0' && len; len--)
        staticStr++;
    }
    if (!str && staticStr)
    {
        for (; *staticStr == '\0'; len--)
            staticStr++;
        for (; !*staticStr && len; len--)
            staticStr++;
    }
    return (staticStr);
}
int main()
{
    char str[] = "Geeks-for-Geeks";

    // Returns first token
    char *token = _strtok(str, "-");

    printf("passed first token\n");
    // Keep printing tokens while one of the
    // delimiters present in str[].
    while (token != NULL)
    {
        printf("%s\n", token);
        token = _strtok(NULL, "-");
    }

    return 0;
}
