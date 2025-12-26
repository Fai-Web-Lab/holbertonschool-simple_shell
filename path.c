#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include "shell.h"

/**
	* find_command - searches PATH for an executable command
	* @cmd: command name (e.g., "ls")
	* @ctx: shell context (unused but kept for structure)
	*
	* Return: malloc'd full path string or NULL if not found
	*
	* Description:
	* - If cmd starts with '/' or '.', treat it as direct path.
	* - Otherwise search each directory in PATH.
	* - Returns a malloc'd string that must be freed by caller.
	*/
char *find_command(char *cmd, shell_ctx_t *ctx)
{
	char *path = getenv("PATH");
	char *copy, *dir, *full;
	int len;

	(void)ctx;
	if (cmd[0] == '/' || cmd[0] == '.')
	{
	if (access(cmd, X_OK) == 0)
	return strdup(cmd);
	return (NULL);
	}

	if (!path)
	return (NULL);

	copy = strdup(path);
	dir = strtok(copy, ":");

	while (dir)
	{
	len = strlen(dir) + strlen(cmd) + 2;
	full = malloc(len);
	snprintf(full, len, "%s/%s", dir, cmd);

	if (access(full, X_OK) == 0)
	{
	free(copy);
	return (full);
	}

	free(full);
	dir = strtok(NULL, ":");
	}

	free(copy);
	return (NULL);
}
