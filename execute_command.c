#include "shell.h"

/**
	* execute_command - executes a command
	* @line: input line
	* @name: shell name
	*
	* Return: 0
	*/
int execute_command(char *line, char *name)
{
	char *argv[BUFFER_SIZE];
	char *token, *cmd_path;
	pid_t pid;
	int argc = 0;

	token = strtok(line, " \t\n");
	while (token && argc < BUFFER_SIZE - 1)
	{
	argv[argc++] = token;
	token = strtok(NULL, " \t\n");
	}
	argv[argc] = NULL;

	if (argc == 0)
	return (0);

	cmd_path = get_command_path(argv[0]);
	if (!cmd_path)
	{
	fprintf(stderr, "%s: %s: not found\n", name, argv[0]);
	return (0);
	}

	pid = fork();
	if (pid == 0)
	{
	execve(cmd_path, argv, environ);
	perror(name);
	exit(1);
	}
	else
	wait(NULL);

	free(cmd_path);
	return (0);
}
