#include "shell.h"
#include <unistd.h>

/**
	* execute_command - executes a command using fork and execve
	* @cmd: command path
	* @args: argument vector
	*
	* Return: 0 on success, -1 on failure
	*/
int execute_command(char *cmd, char **args)
{
	pid_t pid;
	struct stat st;

	if (!cmd)
	{
	return (-1);
	}

	if (stat(cmd, &st) == -1)
	{
	print_error(cmd);
	return (-1);
	}

	pid = fork();
	if (pid == 0)
	{
	execve(cmd, args, environ);
	exit(1);
	}
	wait(NULL);
	return (0);
}
