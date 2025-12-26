#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "shell.h"

/**
	* build_path - builds full path string "dir/cmd"
	* @dir: directory from PATH
	* @cmd: command name
	*
	* Return: malloc'd full path or NULL
	*/
static char *build_path(char *dir, char *cmd)
{
	size_t a = strlen(dir), b = strlen(cmd);
	char *full = malloc(a + b + 2);

	if (!full)
	return (NULL);

	memcpy(full, dir, a);
	full[a] = '/';
	memcpy(full + a + 1, cmd, b);
	full[a + b + 1] = '\0';

	return (full);
}

/**
	* find_command - searches PATH for an executable command
	* @cmd: command name
	* @ctx: shell context (unused)
	*
	* Description:
	* - Handles absolute/relative paths.
	* - Iterates through PATH directories.
	* - Builds full paths and checks X_OK.
	* - Returns malloc'd string or NULL.
	*
	* Return: full path or NULL
	*/
char *find_command(char *cmd, shell_ctx_t *ctx)
{
	char *path = getenv("PATH"), *copy, *dir, *full;

	(void)ctx;

	if (cmd[0] == '/' || cmd[0] == '.')
	return (access(cmd, X_OK) == 0 ? strdup(cmd) : NULL);

	if (!path)
	return (NULL);

	copy = strdup(path);
	if (!copy)
	return (NULL);

	dir = strtok(copy, ":");
	while (dir)
	{
	full = build_path(dir, cmd);
	if (full && access(full, X_OK) == 0)
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
