#include "shell.h"

/**
	* execute_builtin - handle built-in commands
	* @argv: array of tokens
	* Return: 1 if builtin executed, 0 otherwise
	*/
int execute_builtin(char **argv)
{
	if (_strcmp(argv[0], "exit") == 0)
	{
	exit(0);
	}
	else if (_strcmp(argv[0], "env") == 0)
	{
	int i = 0;

	while (environ[i])
	{
	printf("%s\n", environ[i]);
	i++;
	}
	return (1);
	}
	return (0);
}

/**
	* run_external_command - Execute non-builtin command
	* @argv: array of tokens
	* Return: 0 on success
	*/
int run_external_command(char **argv)
{
	pid_t pid;
	int status;
	char *full_path;

	if (!argv || !argv[0])
	return (-1);

	full_path = find_command(argv[0]);
	if (full_path == NULL)
	{
	fprintf(stderr, "%s%s", argv[0], ERR_FOUND);
	return (-1);
	}

	pid = fork();
	if (pid == 0)
	{
	if (execve(full_path, argv, environ) == -1)
	{
	fprintf(stderr, "%s%s", argv[0], ERR_FOUND);
	exit(EXIT_FAILURE);
	}
	}
	else if (pid > 0)
	{
	waitpid(pid, &status, 0);
	}
	free(full_path);
	return (0);
}

/**
	* execute_command - Process a line
	* @line: input line
	* @prog_name: shell name
	* @line_number: line number
	* Return: 0
	*/
int execute_command(char *line, char *prog_name, int line_number)
{
	(void)prog_name;
	(void)line_number;
	char **argv;

	argv = split_line(line);
	if (!argv || !argv[0])
	{
	free_argv(argv);
	return (-1);
	}

	if (!execute_builtin(argv))
	run_external_command(argv);

	free_argv(argv);
	return (0);
}
