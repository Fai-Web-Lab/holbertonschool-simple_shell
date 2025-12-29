#ifndef GETLINE_H
#define GETLINE_H

#include <unistd.h>
#include <stdlib.h>

#define READ_SIZE 1024

ssize_t _getline(char **lineptr, size_t *n, int fd);
ssize_t fill_buffer(char *buffer, ssize_t *size, ssize_t *pos, int fd);
ssize_t append_char(char **lineptr, size_t *n, ssize_t i, char c);

#endif
