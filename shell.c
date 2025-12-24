#include "shell.h"

/**
	* run_shell - Main loop of the shell
	* @prog_name: Name of the shell executable
	*
	* Return: void
	*/
void run_shell(char *prog_name)
{
	char *lineptr = NULL;
	size_t n = 0;
	ssize_t nread;
	int line_number = 0;

	while (1)
	{
	if (isatty(STDIN_FILENO))
	printf(PROMPT_TEXT);

	nread = getline(&lineptr, &n, stdin);
	if (nread == -1)
	break;

	line_number++;
	if (nread > 1)
	execute_command(lineptr, prog_name, line_number);
	}

	free(lineptr);
}

/**
	* split_line - Split a line into words (tokens)
	* @line: input line
	* Return: array of strings
	*/
char **split_line(char *line)
{
	int bufsize = 64, position = 0;
	char **tokens = malloc(sizeof(char *) * bufsize);
	char *token;

	if (!tokens)
	exit(EXIT_FAILURE);

	token = strtok(line, " \t\r\n\a");
	while (token != NULL)
	{
	tokens[position++] = token;

	if (position >= bufsize)
	{
	bufsize += 64;
	tokens = realloc(tokens, sizeof(char *) * bufsize);
	if (!tokens)
	exit(EXIT_FAILURE);
	}

	token = strtok(NULL, " \t\r\n\a");
	}
	tokens[position] = NULL;
	return (tokens);
}

/**
	* free_argv - Free token array
	* @argv: array of strings
	*/
void free_argv(char **argv)
{
	free(argv);
}

/**
	* _strcmp - Compare two strings
	* @s1: string 1
	* @s2: string 2
	* Return: 0 if equal, non-zero otherwise
	*/
int _strcmp(char *s1, char *s2)
{
	int i = 0;

	while (s1[i] && s2[i] && s1[i] == s2[i])
	i++;
	return (s1[i] - s2[i]);
}
