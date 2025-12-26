#include "getline.h"
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

/**
	* _my_getline - custom implementation of getline
	* @lineptr: pointer to buffer storing the read line
	* @n: pointer to buffer size
	*
	* Description:
	* - Reads from STDIN using read().
	* - Reallocates buffer when needed.
	* - Stops at newline.
	* - Returns number of bytes read or -1 on EOF/error.
	*
	* Return: number of bytes read or -1
	*/
ssize_t _my_getline(char **lineptr, size_t *n)
{
	char buffer[1024];
	ssize_t bytes, total = 0, i;
	char *new_ptr;

	if (!lineptr || !n)
	return (-1);

	if (*lineptr == NULL || *n == 0)
	{
	*n = 1024;
	*lineptr = malloc(*n);
	if (!*lineptr)
	return (-1);
	}

	while (1)
	{
	bytes = read(STDIN_FILENO, buffer, 1024);
	if (bytes <= 0)
	return (total == 0 ? -1 : total);

	if (total + bytes + 1 >= (ssize_t)*n)
	{
	*n *= 2;
	new_ptr = realloc(*lineptr, *n);
	if (!new_ptr)
	return (-1);
	*lineptr = new_ptr;
	}
	for (i = 0; i < bytes; i++)
	{
	(*lineptr)[total++] = buffer[i];
	if (buffer[i] == '\n')
	{
	(*lineptr)[total] = '\0';
	return (total);
	}
	}
	}
}
