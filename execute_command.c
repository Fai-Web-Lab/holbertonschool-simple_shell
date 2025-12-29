#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>

/**
	* execute_command - executes a command with optional arguments
	* @cmd: command path
	* @args: NULL-terminated argument array (currently cmd only)
	*
	* Return: 0 on success, -1 on failure
	*/
<<<<<<< HEAD
void execute_child(char **argv, char **env)
{
	if (execve(argv[0], argv, env) == -1)
	{
	perror("simple_shell");
	exit(1);
	}
}

/**
	* execute_command - fork and execute command
	* @argv: arguments array
	* @env: environment
	*
	* Return: void
	*/
void execute_command(char **argv, char **env)
=======
int execute_command(char *cmd, char **args)
>>>>>>> 6c97ab6 (working on advanced 9: simple shell 0.1.1)
{
	pid_t pid;
	struct stat st;

	if (stat(cmd, &st) == -1)
	{
	print_error(cmd);
	return (-1);
	}

	pid = fork();
	if (pid == 0)
	{
	execve(cmd, args, environ);
	}

	wait(NULL);
	return (0);
}
