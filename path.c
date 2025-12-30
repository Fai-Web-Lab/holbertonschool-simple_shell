#include "shell.h"

/**
	* _strncmp - compares n characters of strings
	* @s1: string 1
	* @s2: string 2
	* @n: char count
	* Return: difference
	*/
int _strncmp(char *s1, char *s2, size_t n)
{
	size_t i;

	for (i = 0; i < n && s1[i] && s2[i]; i++)
	{
	if (s1[i] != s2[i])
	return (s1[i] - s2[i]);
	}
	if (i == n)
	return (0);
	return (s1[i] - s2[i]);
}

/**
	* _strdup - duplicates a string
	* @str: string to dup
	* Return: pointer to new string
	*/
char *_strdup(char *str)
{
	char *dup;
	int i, len;

	if (!str)
	return (NULL);
	len = _strlen(str);
	dup = malloc(sizeof(char) * (len + 1));
	if (!dup)
	return (NULL);
	for (i = 0; i <= len; i++)
	dup[i] = str[i];
	return (dup);
}

/**
	* build_full_path - combines dir and cmd
	* @dir: directory
	* @command: command
	* Return: full path string
	*/
char *build_full_path(char *dir, char *command)
{
	char *full;
	int i, j;

	full = malloc(_strlen(dir) + _strlen(command) + 2);
	if (!full)
	return (NULL);
	for (i = 0; dir[i]; i++)
	full[i] = dir[i];
	full[i++] = '/';
	for (j = 0; command[j]; j++)
	full[i + j] = command[j];
	full[i + j] = '\0';
	return (full);
}

/**
	* find_path - finds command in PATH
	* @command: command name
	* @env: environment
	* Return: path or NULL
	*/
char *find_path(char *command, char **env)
{
	char *path_val = NULL, *path_copy, *dir, *full;
	struct stat st;
	int i = 0;

	if (stat(command, &st) == 0)
	return (_strdup(command));
	while (env[i])
	{
	if (_strncmp(env[i], "PATH=", 5) == 0)
	{
	path_val = env[i] + 5;
	break;
	}
	i++;
	}
	if (!path_val)
	return (NULL);
	path_copy = _strdup(path_val);
	dir = _strtok(path_copy, ":");
	while (dir)
	{
	full = build_full_path(dir, command);
	if (full && stat(full, &st) == 0)
	{
	free(path_copy);
	return (full);
	}
	free(full);
	dir = _strtok(NULL, ":");
	}
	free(path_copy);
	return (NULL);
}
