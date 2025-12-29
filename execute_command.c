#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>

/**
	* execute_child - execute command in child process
	* @argv: arguments array
	* @env: environment
	*
	* Return: void
	*/
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
{
	pid_t pid;
	int status;

	if (!argv || !argv[0])
	return;

	pid = fork();
	if (pid == -1)
	{
	perror("simple_shell");
	return;
	}

	if (pid == 0)
	execute_child(argv, env);
	else
	wait(&status);
}
