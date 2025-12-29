#include "getline.h"

/**
	* read_buffer - refill the static buffer from fd
	* @buffer: buffer to fill with new data
	* @size: pointer to current buffer size (number of bytes read)
	* @pos: pointer to current buffer position
	* @fd: file descriptor to read from
	*
	* Return: number of bytes read into buffer, or -1 on EOF/error
	*/
ssize_t read_buffer(char *buffer, ssize_t *size, ssize_t *pos, int fd)
{
	*size = read(fd, buffer, READ_SIZE);
	*pos = 0;
	if (*size <= 0)
	{
	return (-1);
	}
	return (*size);
}

/**
	* append_char - append a character to the line buffer, realloc if needed
	* @lineptr: pointer to buffer holding the line
	* @n: pointer to current buffer size
	* @i: current index in the buffer
	* @c: character to append
	*
	* Return: updated index after appending, or -1 on failure
	*/
ssize_t append_char(char **lineptr, size_t *n, ssize_t i, char c)
{
	if (i + 1 >= (ssize_t)*n)
	{
	*n *= 2;
	*lineptr = realloc(*lineptr, *n);
	if (!*lineptr)
	{
	return (-1);
	}
	}
	(*lineptr)[i] = c;
	i++;
	return (i);
}

/**
	* init_line - initialize the line buffer if NULL or size is 0
	* @lineptr: pointer to buffer
	* @n: pointer to current buffer size
	*
	* Return: 0 on success, -1 on failure
	*/
static int init_line(char **lineptr, size_t *n)
{
	if (!*lineptr || *n == 0)
	{
	*n = READ_SIZE;
	*lineptr = malloc(*n);
	if (!*lineptr)
	{
	return (-1);
	}
	}
	return (0);
}

/**
	* read_line_loop - read characters into line buffer until newline
	* @lineptr: buffer to store the line
	* @n: pointer to buffer size
	* @fd: file descriptor to read from
	* @buffer: static buffer holding read data
	* @size: pointer to current buffer size
	* @pos: pointer to current buffer position
	*
	* Return: number of characters read, or -1 on EOF/error
	*/
static ssize_t read_line_loop(char **lineptr, size_t *n, int fd,
	char *buffer, ssize_t *size, ssize_t *pos)
{
	ssize_t i = 0;
	char c;

	while (1)
	{
	if (*pos >= *size)
	{
	if (read_buffer(buffer, size, pos, fd) == -1)
	{
	return (i > 0 ? i : -1);
	}
	}

	c = buffer[(*pos)++];
	i = append_char(lineptr, n, i, c);
	if (i == -1)
	{
	return (-1);
	}

	if (c == '\n')
	{
	break;
	}
	}

	(*lineptr)[i] = '\0';
	return (i);
}

/**
	* _getline - read a line from a file descriptor
	* @lineptr: buffer to store the line
	* @n: pointer to buffer size
	* @fd: file descriptor to read from
	*
	* Return: number of characters read, or -1 on EOF/error
	*/
ssize_t _getline(char **lineptr, size_t *n, int fd)
{
	static char buffer[READ_SIZE];
	static ssize_t size;
	static ssize_t pos;

	if (!lineptr || !n || fd < 0)
	{
	return (-1);
	}

	if (init_line(lineptr, n) == -1)
	{
	return (-1);
	}

	return (read_line_loop(lineptr, n, fd, buffer, &size, &pos));
}
