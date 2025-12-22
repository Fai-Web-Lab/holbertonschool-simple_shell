#include "shell.h"

/**
	* is_only_spaces - checks if string has only spaces
	* @str: input string
	*
	* Return: 1 if only spaces, 0 otherwise
	*/
int is_only_spaces(char *str)
{
	int i = 0;

	while (str[i])
	{
	if (str[i] != ' ' && str[i] != '\n' && str[i] != '\t')
	return (0);
	i++;
	}
	return (1);
}

/**
	* execute_command - executes a command with arguments
	* @line: input line
	* @prog_name: program name
	*
	* Return: 0
	*/
int execute_command(char *line, char *prog_name)
{
	pid_t pid;
	char *argv[1024];
	int argc = 0;
	char *token;

	token = strtok(line, " \t\n");
	while (token != NULL && argc < 1023)
	{
	argv[argc++] = token;
	token = strtok(NULL, " \t\n");
	}
	argv[argc] = NULL;

	if (argc == 0)
	return (0);

	pid = fork();
	if (pid == 0)
	{
	if (execve(argv[0], argv, environ) == -1)
	{
	fprintf(stderr, "%s: No such file or directory\n", prog_name);
	exit(127);
	}
	}
	else
	wait(NULL);

	return (0);
}
