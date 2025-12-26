#include "getline.h"

#define READ_SIZE 1024

/**
	* resize_buffer - resizes line buffer if needed
	* @lineptr: buffer pointer
	* @n: buffer size
	* @i: current index
	*
	* Return: 0 on success, -1 on failure
	*/
static int resize_buffer(char **lineptr, size_t *n, ssize_t i)
{
	char *new_line;

	if (i + 1 < (ssize_t)*n)
	return (0);

	*n *= 2;
	new_line = realloc(*lineptr, *n);
	if (!new_line)
	return (-1);

	*lineptr = new_line;
	return (0);
}

/**
	* refill_buffer - refills static buffer using read
	* @buffer: static buffer
	* @buf_len: buffer length
	* @buf_pos: buffer position
	*
	* Return: number of bytes read
	*/
static ssize_t refill_buffer(char *buffer, ssize_t *buf_len, ssize_t *buf_pos)
{
	*buf_len = read(STDIN_FILENO, buffer, READ_SIZE);
	*buf_pos = 0;
	return (*buf_len);
}

/**
	* _getline - reads a line from stdin
	* @lineptr: pointer to buffer
	* @n: buffer size
	*
	* Return: number of characters read, -1 on EOF
	*/
ssize_t _getline(char **lineptr, size_t *n)
{
	static char buffer[READ_SIZE];
	static ssize_t buf_len, buf_pos;
	ssize_t i = 0;

	if (!lineptr || !n)
	return (-1);

	if (*lineptr == NULL || *n == 0)
	{
	*n = READ_SIZE;
	*lineptr = malloc(*n);
	if (!*lineptr)
	return (-1);
	}

	while (1)
	{
	if (buf_pos >= buf_len &&
	refill_buffer(buffer, &buf_len, &buf_pos) <= 0)
	return (i > 0 ? i : -1);

	if (resize_buffer(lineptr, n, i) == -1)
	return (-1);

	(*lineptr)[i] = buffer[buf_pos++];
	if ((*lineptr)[i++] == '\n')
	{
	(*lineptr)[i] = '\0';
	return (i);
	}
	}
}
