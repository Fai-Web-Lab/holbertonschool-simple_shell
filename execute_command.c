#include "shell.h"

/**
	* execute_command - Forks and executes a command
	* @args: Array of strings containing command and arguments
	*/
void execute_command(char **args)
{
	pid_t child_pid;
	int status;
	char *actual_path;

	actual_path = find_path(args[0]);

	if (actual_path == NULL)
	{
	perror("./shell");
	return;
	}

	child_pid = fork();
	if (child_pid == -1)
	{
	perror("Error:");
	free(actual_path);
	return;
	}

	if (child_pid == 0)
	{
	if (execve(actual_path, args, environ) == -1)
	{
	perror("Error:");
	exit(1);
	}
	}
	else
	{
	wait(&status);
	free(actual_path);
	}
}
