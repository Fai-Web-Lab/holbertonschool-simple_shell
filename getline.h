#ifndef GETLINE_H
#define GETLINE_H

#include <unistd.h>
#include <stdlib.h>

/**
	* _my_getline - custom getline implementation
	* @lineptr: pointer to buffer
	* @n: pointer to buffer size
	*
	* Return: number of bytes read or -1
	*/
ssize_t _my_getline(char **lineptr, size_t *n);

#endif
