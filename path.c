#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include "shell.h"

/**
	* get_path - get the value of PATH from environment
	* @env: environment variables
	*
	* Return: pointer to PATH string or NULL if not found
	*/
char *get_path(char **env)
{
	int i;
	size_t len = 5;

	for (i = 0; env[i]; i++)
	{
	if (strncmp(env[i], "PATH=", len) == 0)
	return (env[i] + len);
	}
	return (NULL);
}

/**
	* search_in_path - search command in a PATH string
	* @cmd: command name
	* @path: PATH value
	*
	* Return: full path string or NULL
	*/
static char *search_in_path(char *cmd, char *path)
{
	char *copy, *token, *full;
	struct stat st;

	copy = strdup(path);
	if (!copy)
	return (NULL);

	token = strtok(copy, ":");
	while (token)
	{
	full = malloc(strlen(token) + strlen(cmd) + 2);
	if (!full)
	break;

	sprintf(full, "%s/%s", token, cmd);
	if (stat(full, &st) == 0)
	{
	free(copy);
	return (full);
	}
	free(full);
	token = strtok(NULL, ":");
	}

	free(copy);
	return (NULL);
}

/**
	* find_command - find executable path of a command
	* @cmd: command name
	* @ctx: shell context
	*
	* Return: full path string or NULL if not found
	*/
char *find_command(char *cmd, shell_ctx_t *ctx)
{
	char *path;
	struct stat st;

	(void)ctx;

	if (!cmd)
	return (NULL);

	if (cmd[0] == '/' || cmd[0] == '.')
	{
	if (stat(cmd, &st) == 0)
	return (strdup(cmd));
	return (NULL);
	}

	path = get_path(ctx->env);
	if (!path || path[0] == '\0')
	return (NULL);

	return (search_in_path(cmd, path));
}
