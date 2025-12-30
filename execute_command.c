#include "shell.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

/**
	* execute_command - executes a command with arguments
	* @cmd: command name or path
	* @args: arguments array, NULL-terminated
	* @env: environment array
	*
	* Return: child process exit status, -1 on failure
	*/
int execute_command(char *cmd, char **args, char **env)
{
	pid_t pid;
	int status;
	char *path;

	if (cmd[0] != '/')
	{
	path = get_path(cmd, env);
	if (!path)
	{
	write(STDERR_FILENO, cmd, strlen(cmd));
	write(STDERR_FILENO, ": not found\n", 12);
	return (-1);
	}
	cmd = path;
	}

	pid = fork();
	if (pid == 0)
	{
	execve(cmd, args, env);
	perror("execve failed");
	exit(EXIT_FAILURE);
	}
	else if (pid > 0)
	{
	wait(&status);
	if (cmd != args[0])
	free(cmd);
	return (status);
	}
	else
	{
	perror("fork failed");
	return (-1);
	}
}
