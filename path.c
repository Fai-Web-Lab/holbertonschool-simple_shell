#include "shell.h"

/**
	* get_path_value - finds PATH string in env
	* @env: environment
	* Return: pointer to path value
	*/
char *get_path_value(char **env)
{
	int i = 0;

	while (env[i])
	{
	if (strncmp(env[i], "PATH=", 5) == 0)
	return (env[i] + 5);
	i++;
	}
	return (NULL);
}

/**
	* find_path - finds executable path
	* @command: command name
	* @env: environment
	* Return: full path string
	*/
char *find_path(char *command, char **env)
{
	char *path_val, *path_copy, *dir, *full;
	struct stat st;

	if (stat(command, &st) == 0)
	return (strdup(command));

	path_val = get_path_value(env);
	if (!path_val)
	return (NULL);

	path_copy = strdup(path_val);
	dir = strtok(path_copy, ":");
	while (dir)
	{
	full = malloc(strlen(dir) + strlen(command) + 2);
	if (full)
	{
	sprintf(full, "%s/%s", dir, command);
	if (stat(full, &st) == 0)
	{
	free(path_copy);
	return (full);
	}
	free(full);
	}
	dir = strtok(NULL, ":");
	}
	free(path_copy);
	return (NULL);
}
