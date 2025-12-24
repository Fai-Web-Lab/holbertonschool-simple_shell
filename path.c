#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include "shell.h"

/**
	* search_in_path - search command in PATH
	* @cmd: command name
	* @path: PATH value
	*
	* Return: full path or NULL
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
	* find_command - find executable using PATH
	* @cmd: command name
	* @ctx: shell context
	*
	* Return: full path or NULL
	*/
char *find_command(char *cmd, shell_ctx_t *ctx)
{
	struct stat st;
	char *path;

	(void)ctx;

	if (!cmd)
	return (NULL);

	if (cmd[0] == '/' || cmd[0] == '.')
	{
	if (stat(cmd, &st) == 0)
	return (strdup(cmd));
	return (NULL);
	}

	path = getenv("PATH");
	if (!path || path[0] == '\0')
	return (NULL);

	return (search_in_path(cmd, path));
}
