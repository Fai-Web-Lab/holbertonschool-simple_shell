#include "shell.h"

/**
	* find_command - Find the full path of a command using PATH
	* @cmd: Command name
	*
	* Return: full path string (malloc'd), or NULL if not found
	*/
char *find_command(char *cmd)
{
	char *path_env, *path_copy, *dir;
	char *full_path;
	int len;

	path_env = getenv("PATH");
	if (!path_env)
	return (NULL);

	path_copy = strdup(path_env);
	if (!path_copy)
	return (NULL);

	dir = strtok(path_copy, ":");
	while (dir)
	{
	len = snprintf(NULL, 0, "%s/%s", dir, cmd);
	full_path = malloc(len + 1);
	if (!full_path)
	{
	free(path_copy);
	return (NULL);
	}
	sprintf(full_path, "%s/%s", dir, cmd);
	if (access(full_path, X_OK) == 0)
	{
	free(path_copy);
	return (full_path);
	}
	free(full_path);
	dir = strtok(NULL, ":");
	}
	free(path_copy);
	return (NULL);
}
