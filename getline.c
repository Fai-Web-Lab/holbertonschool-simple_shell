#include "shell.h"

/**
	* _getline - reads input from a file descriptor into a buffer
	* @lineptr: pointer to the buffer
	* @n: pointer to the size of the buffer
	* @fd: file descriptor to read from
	* Return: number of characters read or -1 on failure/EOF
	*/
ssize_t _getline(char **lineptr, size_t *n, int fd)
{
	static char buffer[BUF_SIZE];
	static size_t pos;
	static size_t bytes;
	size_t i = 0, old_n;
	char c;

	if (*lineptr == NULL || *n == 0)
	{
	*n = BUF_SIZE;
	*lineptr = malloc(*n);
	if (!*lineptr)
	return (-1);
	}
	while (1)
	{
	if (pos >= bytes)
	{
	bytes = read(fd, buffer, BUF_SIZE);
	pos = 0;
	if (bytes <= 0)
	return (-1);
	}
	c = buffer[pos++];
	if (i >= *n - 1)
	{
	old_n = *n;
	*n += BUF_SIZE;
	*lineptr = _realloc(*lineptr, old_n, *n);
	if (!*lineptr)
	return (-1);
	}
	(*lineptr)[i++] = c;
	if (c == '\n')
	break;
	}
	(*lineptr)[i] = '\0';
	return (i);
}
