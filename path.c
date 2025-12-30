#include "shell.h"
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/**
	* find_path_var - Finds the PATH variable in env
	* @env: Environment array
	*
	* Return: Pointer to PATH string or NULL if not found
	*/
char *find_path_var(char **env)
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
	* build_full_path - Concatenates directory and command
	* @dir: Directory path
	* @cmd: Command name
	*
	* Return: Newly allocated string with full path or NULL on failure
	*/
char *build_full_path(char *dir, char *cmd)
{
	char *full_path;
	int len_dir = 0, len_cmd = 0, i, j;

	while (dir[len_dir])
	len_dir++;
	while (cmd[len_cmd])
	len_cmd++;

	full_path = malloc(len_dir + len_cmd + 2);
	if (!full_path)
	return (NULL);

	for (i = 0; i < len_dir; i++)
	full_path[i] = dir[i];
	full_path[i++] = '/';
	for (j = 0; j < len_cmd; j++)
	full_path[i + j] = cmd[j];
	full_path[i + j] = '\0';

	return (full_path);
}

/**
	* get_path - Searches PATH directories for a command
	* @cmd: Command name
	* @env: Environment array
	*
	* Return: Full path to executable if found, else NULL
	*/
char *get_path(char *cmd, char **env)
{
	char *path_env, *path_copy;
	char *full_path;
	char *token;

	if (!cmd || !env)
	return (NULL);

	if (cmd[0] == '/' || cmd[0] == '.')
	return (strdup(cmd));

	path_env = find_path_var(env);
	if (!path_env)
	return (NULL);

	path_copy = strdup(path_env);
	if (!path_copy)
	return (NULL);

	token = strtok(path_copy, ":");
	while (token)
	{
	full_path = build_full_path(token, cmd);
	if (!full_path)
	{
	free(path_copy);
	return (NULL);
	}
	if (access(full_path, X_OK) == 0)
	{
	free(path_copy);
	return (full_path);
	}
	free(full_path);
	token = strtok(NULL, ":");
	}

	free(path_copy);
	return (NULL);
}
