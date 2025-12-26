#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "shell.h"

/**
	* get_path_value - extracts PATH value from environ
	*
	* Return: malloc'd string containing PATH value or NULL
	*/
static char *get_path_value(void)
{
	int i = 0;
	char *p;

	while (environ[i])
	{
	if (strncmp(environ[i], "PATH=", 5) == 0)
	{
	p = strdup(environ[i] + 5);
	return (p);
	}
	i++;
	}
	return (NULL);
}

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
	* Return: full path or NULL
	*/
char *find_command(char *cmd, shell_ctx_t *ctx)
{
	char *path, *copy, *dir, *full;

	(void)ctx;

	if (cmd[0] == '/' || cmd[0] == '.')
	return (access(cmd, X_OK) == 0 ? strdup(cmd) : NULL);

	path = get_path_value();
	if (!path)
	return (NULL);

	copy = strdup(path);
	free(path);
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
