#include "shell.h"

/**
	* _strcmp - compares two strings
	* @s1: first string
	* @s2: second string
	*
	* Return: difference between strings
	*/
int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
	s1++;
	s2++;
	}
	return (*s1 - *s2);
}

/**
	* is_delim - checks if a character is a delimiter
	* @c: char to check
	* @delim: delimiter string
	*
	* Return: 1 if it is a delimiter, 0 otherwise
	*/
int is_delim(char c, const char *delim)
{
	while (*delim)
	{
	if (c == *delim)
	return (1);
	delim++;
	}
	return (0);
}

/**
	* _strtok - custom string tokenizer
	* @str: string to tokenize
	* @delim: delimiter string
	*
	* Return: pointer to the next token, or NULL
	*/
char *_strtok(char *str, const char *delim)
{
	static char *last;
	char *token;

	if (str != NULL)
	last = str;
	if (last == NULL || *last == '\0')
	return (NULL);

	while (*last && is_delim(*last, delim))
	last++;

	if (*last == '\0')
	return (NULL);

	token = last;
	while (*last && !is_delim(*last, delim))
	last++;

	if (*last != '\0')
	{
	*last = '\0';
	last++;
	}
	return (token);
}
