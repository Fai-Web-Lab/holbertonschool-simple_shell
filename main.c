#include <stdio.h>
#include <stdlib.h>
#include "getline.h"

/**
	* main - test custom getline
	*
	* Return: Always 0
	*/
int main(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t read;

	while ((read = _getline(&line, &len)) != -1)
	write(1, line, read);

	free(line);
	return (0);
}
