#include "shell.h"

/**
	* execute_child - execute command in child process
	* @argv: arguments array
	* @env: environment
	*
	* Return: void
	*/
void execute_child(char **argv, char **env)
{
	char *cmd_path;

	if (argv[0][0] == '/')
	execve(argv[0], argv, env);

	cmd_path = get_path(argv[0]);
	if (cmd_path)
	execve(cmd_path, argv, env);

	perror("simple_shell");
	exit(127);
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
