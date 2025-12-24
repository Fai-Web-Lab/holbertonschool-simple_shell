#include "shell.h"

/**
	* find_command - Find command in PATH
	* @cmd: command to search
	* Return: full path to command or NULL
	*/
char *find_command(char *cmd)
{
	char *path, *token, *full_path;
	size_t len;

	if (!cmd)
	return (NULL);

	path = getenv("PATH");
	if (!path)
	return (NULL);

	path = strdup(path);
	token = strtok(path, ":");
	while (token != NULL)
	{
	len = strlen(token) + strlen(cmd) + 2;
	full_path = malloc(len);
	if (!full_path)
	exit(EXIT_FAILURE);

	snprintf(full_path, len, "%s/%s", token, cmd);

	if (access(full_path, X_OK) == 0)
	{
	free(path);
	return (full_path);
	}

	free(full_path);
	token = strtok(NULL, ":");
	}

	free(path);
	return (NULL);
}
