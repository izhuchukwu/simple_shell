#include "shell.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * _strcmp - compares two strings
 * @s1: the first string
 * @s2: the second string
 * Return: a negative num if s1 < s2, positive if s1 > s2 or zero if s1 == s2
 */
int _strcmp(char *s1, char *s2)
{
	char *s11;
	char *s22;

	s11 = s1;
	s22 = s2;

	while (*s11 == *s22)
	{
		if (*s11 == '\0')
			break;
		if (*s22 == '\0')
			break;
		s11 = s11 + 1;
		s22 = s22 + 1;
	}

	if (*s11 < *s22)
		return (*s11 - *s22);
	if (*s11 > *s22)
		return (*s11 - *s22);

	return (0);
}

/**
 * _strlen - get the length of a string
 * @s: the string
 * Return: the number of characters in the string minus the null char
 */
int _strlen(char *s)
{
	int len;

	len = 0;
	while (s[len] != '\0')
	{
		len = len + 1;
	}
	return (len);
}
