#include "shell.h"

/**
	* find_path - Locates a command in the PATH
	* @command: The command to find
	* Return: Full path to command if found, or NULL
	*/
char *find_path(char *command)
{
	char *path, *path_copy, *token, *full_path;
	struct stat st;
	int i;

	for (i = 0; command[i]; i++)
	if (command[i] == '/')
	return (stat(command, &st) == 0 ? strdup(command) : NULL);

	path = getenv("PATH");
	if (!path || strlen(path) == 0)
	return (NULL);

	path_copy = strdup(path);
	token = strtok(path_copy, ":");
	while (token)
	{
	full_path = malloc(strlen(token) + strlen(command) + 2);
	sprintf(full_path, "%s/%s", token, command);

	if (stat(full_path, &st) == 0)
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
