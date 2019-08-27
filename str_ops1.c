#include "shell.h"
#include <stdio.h>

/**
  * _atoi - converst a string to an integer
  * @s: string to be converted
  * Return: integers in a string
  */

int _atoi(char *s)
{
	int num, len, numcount, mult, x, neg;

	len = 0;
	x = 0;
	numcount = 0;
	mult = 1;
	neg = 1;
	num = 0;

	while (s[len] != '\0')
	{
		if (s[len] >= '0' && s[len] <= '9')
		{
			numcount++;
			if (!(s[len + 1] >= '0' && s[len + 1] <= '9'))
				break;
		}
		len++;
	}
	for (; numcount > 1; numcount--)
		mult *= 10;
	for (; x <= len; x++)
	{
		if (s[x] == '-')
			neg *= -1;
		else if (s[x] <= '9' && s[x] >= '0')
		{
			num += (s[x] - '0') * mult * neg;
			mult /= 10;
		}
	}
	return (num);
}

/**
  * sizeof_command - returns the size of command, breaks if it hits &&, ||, ;
  * @tokens: standard input tokenized
  * Return: the size of the command
  */
int sizeof_command(char **tokens)
{
	int i = 0;

	if (!tokens)
		return (0);
	for (i = 0; tokens[i]; i++)
	{
		if (tokens[i][0] == '&' && tokens[i][1] == '&')
			break;
		if (tokens[i][0] == '|' && tokens[i][1] == '|')
			break;
		if (tokens[i][0] == ';')
			break;
	}
	return (i);
}

/**
 * _isdigit - check for a digit (0 through 9)
 * @c: digit checked
 * Return: 1 if c is a digit returns 0 otherwise
 */

int _isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);

	return (0);
}