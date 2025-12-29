#include "shell.h"
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
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
	exit(127);
	}
}

/**
	* execute_command - fork and execute command
	* @ctx: shell context
	* @argv: arguments array
	* @env: environment
	*
	* Return: void
	*/
void execute_command(shell_ctx_t *ctx, char **argv, char **env)
{
	pid_t pid;
	int status;

	if (!argv || !argv[0])
	return;

	pid = fork();
	if (pid == -1)
	{
	perror("simple_shell");
	ctx->exit_status = 1;
	return;
	}

	if (pid == 0)
	execute_child(argv, env);
	else
	{
	wait(&status);
	if (WIFEXITED(status))
	ctx->exit_status = WEXITSTATUS(status);
	else
	ctx->exit_status = 1;
	}
}
/**
	* is_number - checks if a string represents a positive integer
	* @s: input string
	*
	* Return: 1 if the string is a valid positive number, 0 otherwise
	*/
int is_number(char *s)
{
	int i = 0;

	if (!s)
	return (0);

	if (s[0] == '-')
	return (0);

	while (s[i])
	{
	if (s[i] < '0' || s[i] > '9')
	return (0);
	i++;
	}

	return (1);
}
/**
	* handle_exit_error - prints exit error message
	* @arg: invalid argument
	*
	* Return: always 2
	*/
int handle_exit_error(char *arg)
{
	int start = 0, len = 0;

	write(STDERR_FILENO, "./hsh: 1: exit: Illegal number:", 32);

	while (arg[start] == ' ')
	start++;

	len = strlen(arg + start);

	if (len > 0 && arg[start + len - 1] == '\n')
	len--;

	write(STDERR_FILENO, " ", 1);

	write(STDERR_FILENO, arg + start, len);

	write(STDERR_FILENO, "\n", 1);
	return (2);
}
