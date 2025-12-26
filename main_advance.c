#include <stdio.h>
#include "getline.h"

/**
	* main - test custom getline
	*
	* Return: 0
	*/
int main(void)
{
	char *line = NULL;
	size_t len = 0;

	while (_getline(&line, &len) != -1)
	printf("%s", line);

	free(line);
	return (0);
}
