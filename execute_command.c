#include "shell.h"

/**
	* _strlen - returns the length of a string
	* @s: string to evaluate
	*
	* Return: length of the string
	*/
int _strlen(char *s)
{
	int i = 0;

	while (s && s[i])
	i++;
	return (i);
}

/**
	* _strdup - duplicates a string
	* @str: string to duplicate
	*
	* Return: pointer to the new string, or NULL if it fails
	*/
char *_strdup(char *str)
{
	char *dup;
	int i, len;

	if (!str)
	return (NULL);

	len = _strlen(str);
	dup = malloc(len + 1);
	if (!dup)
	return (NULL);

	for (i = 0; i <= len; i++)
	dup[i] = str[i];

	return (dup);
}

/**
	* execute_command - fork and execve a command
	* @argv: argument vector
	* @ctx: shell context structure
	*/
void execute_command(char **argv, shell_ctx_t *ctx)
{
	pid_t child;
	int status;
	char *path;

	path = find_path(argv[0], ctx->env);
	if (!path)
	{
	write(STDERR_FILENO, "./hsh: 1: ", 10);
	write(STDERR_FILENO, argv[0], _strlen(argv[0]));
	write(STDERR_FILENO, ": not found\n", 12);
	ctx->exit_status = 127;
	return;
	}
	child = fork();
	if (child == 0)
	{
	if (execve(path, argv, ctx->env) == -1)
	{
	perror("execve");
	exit(1);
	}
	}
	else
	{
	waitpid(child, &status, 0);
	if (WIFEXITED(status))
	ctx->exit_status = WEXITSTATUS(status);
	}
	free(path);
}
