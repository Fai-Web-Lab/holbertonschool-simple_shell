#include "shell.h"

/**
	* _strcmp - Compare two strings
	* @s1: first string
	* @s2: second string
	*
	* Return: 0 if equal, else non-zero
	*/

extern char **environ;

int _strcmp(char *s1, char *s2)
{
	while (*s1 && (*s1 == *s2))
	{
	s1++;
	s2++;
	}
	return (*s1 - *s2);
}

/**
	* split_line - Tokenize input line into argv array
	* @line: input line
	*
	* Return: array of tokens (NULL terminated)
	*/
char **split_line(char *line)
{
	char **argv = NULL;
	char *token;
	int argc = 0;

	token = strtok(line, " \t\n");
	while (token)
	{
	argv = realloc(argv, sizeof(char *) * (argc + 2));
	if (!argv)
	return (NULL);
	argv[argc] = strdup(token);
	if (!argv[argc])
	return (NULL);
	argc++;
	token = strtok(NULL, " \t\n");
	}
	if (argv)
	argv[argc] = NULL;
	return (argv);
}

/**
	* free_argv - Free argv array
	* @argv: array to free
	*/
void free_argv(char **argv)
{
	int i = 0;

	if (!argv)
	return;

	while (argv[i])
	{
	free(argv[i]);
	i++;
	}
	free(argv);
}

/**
	* execute_command - Execute a command line
	* @line: input line
	*
	* Return: 0
	*/
int execute_command(char *line)
{
	char **argv;
	char *full_path;
	pid_t pid;
	int status;

	argv = split_line(line);
	if (!argv || !argv[0])
	{
	free_argv(argv);
	return (0);
	}

	full_path = find_command(argv[0]);
	if (!full_path)
	{
	fprintf(stderr, "%s: %s", argv[0], ERR_FOUND);
	free_argv(argv);
	return (0);
	}

	pid = fork();
	if (pid == 0)
	{
	if (execve(full_path, argv, environ) == -1)
	perror("execve");
	exit(EXIT_FAILURE);
	}
	else if (pid < 0)
	perror("fork");
	else
	waitpid(pid, &status, 0);

	free(full_path);
	free_argv(argv);
	return (0);
}
