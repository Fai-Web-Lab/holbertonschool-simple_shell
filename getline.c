#include "getline.h"
#include <string.h>
#include <stddef.h>

/**
	* _read_buffer - fills the static buffer
	* @buf: static buffer
	* @buf_len: pointer to current buffer length
	* Return: number of bytes read
	*/
static ssize_t _read_buffer(char *buf, size_t *buf_len)
{
	*buf_len = read(STDIN_FILENO, buf, READ_BUF_SIZE);
	return (*buf_len);
}

/**
	* _append_chunk - appends chunk to line
	* @line: current line
	* @line_len: current line length
	* @chunk: chunk to append
	* @chunk_len: length of chunk
	* Return: new line pointer (malloced)
	*/
static char *_append_chunk(char *line, size_t line_len,
	char *chunk, size_t chunk_len)
{
	char *new_line = malloc(line_len + chunk_len + 1);

if (!new_line)
	{
	if (line)
	free(line);
	return (NULL);
	}

	if (line)
	{
	memcpy(new_line, line, line_len);
	free(line);
	}

	memcpy(new_line + line_len, chunk, chunk_len);
	new_line[line_len + chunk_len] = '\0';
	return (new_line);
}

/**
	* _getline - reads a line from stdin
	* Return: pointer to line (must be freed by caller)
	*/
char *_getline(void)
{
	static char buf[READ_BUF_SIZE];
	static size_t buf_pos;
	static size_t buf_len;
	char *line = NULL;
	size_t line_len = 0;
	ssize_t i;

	while (1)
	{
	if (buf_pos >= buf_len)
	{
	if (_read_buffer(buf, &buf_len) <= 0)
	return (NULL);
	buf_pos = 0;
	}

	for (i = buf_pos; i < buf_len; i++)
	{
	if (buf[i] == '\n')
	{
	line = _append_chunk(line, line_len, buf + buf_pos, i - buf_pos);
	if (!line)
	return (NULL);
	line_len += i - buf_pos;
	buf_pos = i + 1;
	return (line);
	}
	}

	line = _append_chunk(line, line_len, buf + buf_pos, buf_len - buf_pos);
	if (!line)
	return (NULL);
	line_len += buf_len - buf_pos;
	buf_pos = buf_len;
	}
}
