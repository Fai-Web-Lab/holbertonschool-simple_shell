#include "shell.h"

/**
	* tokenize - Splits a string into tokens
	* @line: The string to split
	* Return: Null-terminated array of strings
	*/
char **tokenize(char *line)
{
	char **tokens = malloc(64 * sizeof(char *));
	char *token;
	int i = 0;

	if (!tokens)
	return (NULL);

	token = strtok(line, " \t\r\n\a");
	while (token != NULL)
	{
	tokens[i] = strdup(token);
	i++;
	token = strtok(NULL, " \t\r\n\a");
	}
	tokens[i] = NULL;
	return (tokens);
}

/**
	* free_args - Frees the array of strings
	* @args: Array to free
	*/
void free_args(char **args)
{
	int i;

	if (!args)
	return;

	for (i = 0; args[i]; i++)
	free(args[i]);
	free(args);
}
