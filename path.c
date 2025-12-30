#include "shell.h"

/**
	* _realloc - reallocates a memory block
	* @ptr: old pointer
	* @old_size: old size
	* @new_size: new size
	* Return: new pointer
	*/
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *new_ptr, *old_ptr = ptr;
	unsigned int i;

	if (new_size == old_size)
	return (ptr);
	if (new_size == 0 && ptr != NULL)
	{
	free(ptr);
	return (NULL);
	}
	if (ptr == NULL)
	return (malloc(new_size));
	new_ptr = malloc(new_size);
	if (!new_ptr)
	return (NULL);
	for (i = 0; i < old_size && i < new_size; i++)
	new_ptr[i] = old_ptr[i];
	free(ptr);
	return (new_ptr);
}

/**
	* copy_env - creates a heap-allocated copy of the environment
	* Return: pointer to the new environment array
	*/
char **copy_env(void)
{
	int i, count = 0;
	char **new_env;

	while (environ[count])
	count++;
	new_env = malloc(sizeof(char *) * (count + 64));
	if (!new_env)
	return (NULL);
	for (i = 0; i < count; i++)
	new_env[i] = _strdup(environ[i]);
	new_env[i] = NULL;
	return (new_env);
}

/**
	* build_full_path - concatenates dir and command
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
	* find_path - locates a command in the PATH
	* @command: command
	* @env: environment
	* Return: full path or NULL
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
