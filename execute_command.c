#include "shell.h"

extern char **environ;

/**
	* execute_command - Executes a command using fork and execve
	* @line: Command entered by the user
	* @prog_name: Shell program name
	* @line_number: Current command number
	*
	* Return: 0 on success, -1 on failure
	*/
int execute_command(char *line, char *simple_shell, int line_number)
{
	pid_t pid;
	char *argv[2];

	(void)line_number;

	line[strcspn(line, "\n")] = '\0';

	argv[0] = line;
	argv[1] = NULL;

	pid = fork();
	if (pid == -1)
	{
	perror("fork");
	return (-1);
	}

	if (pid == 0)
	{
	if (execve(argv[0], argv, environ) == -1)
	{
	fprintf(stderr, "%s: %s: not found\n", simple_shell, argv[0]);
	exit(127);
	}
	}
	else
	{
	wait(NULL);
	}

	return (0);
}
