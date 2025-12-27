#include "getline.h"
#include <unistd.h>
#include <stdlib.h>

#define READ_SIZE 1024

/**
	* refill_buffer - reads data into static buffer
	* @buf: buffer
	* @buf_len: current buffer length
	* @buf_pos: current position
	*
	* Return: number of bytes read or -1
	*/
static ssize_t refill_buffer(char *buf, size_t *buf_len, size_t *buf_pos)
{
	ssize_t r;

	r = read(STDIN_FILENO, buf, READ_SIZE);
	if (r <= 0)
	return (-1);

	*buf_len = r;
	*buf_pos = 0;

	return (r);
}

/**
	* expand_line - reallocates line buffer if needed
	* @lineptr: line buffer
	* @n: buffer size
	*
	* Return: 0 on success, -1 on failure
	*/
static int expand_line(char **lineptr, size_t *n)
{
	char *tmp;
	size_t new_size;

	new_size = (*n) * 2;
	tmp = realloc(*lineptr, new_size);
	if (!tmp)
	return (-1);

	*lineptr = tmp;
	*n = new_size;

	return (0);
}

/**
	* _getline - reads a line from stdin
	* @lineptr: pointer to buffer
	* @n: size of buffer
	*
	* Return: number of chars read, -1 on EOF
	*/
ssize_t _getline(char **lineptr, size_t *n)
{
	static char buffer[READ_SIZE];
	static size_t buf_pos, buf_len;
	size_t i;
	ssize_t r;

	if (!lineptr || !n)
	return (-1);

	if (*lineptr == NULL || *n == 0)
	{
	*n = READ_SIZE;
	*lineptr = malloc(*n);
	if (!*lineptr)
	return (-1);
	}

	i = 0;
	while (1)
	{
	if (buf_pos >= buf_len)
	{
	r = refill_buffer(buffer, &buf_len, &buf_pos);
	if (r == -1)
	return (i > 0 ? (ssize_t)i : -1);
	}

	if (i + 1 >= *n && expand_line(lineptr, n) == -1)
	return (-1);

	(*lineptr)[i++] = buffer[buf_pos++];

	if ((*lineptr)[i - 1] == '\n')
	{
	(*lineptr)[i] = '\0';
	return ((ssize_t)i);
	}
	}
}
