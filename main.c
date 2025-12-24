#include <unistd.h>
#include "shell.h"

/**
	* main - entry point of shell
	*
	* Return: Always 0
	*/
int main(void)
{
	shell_ctx_t ctx;

	ctx.last_status = 0;
	ctx.env = environ;

	shell_loop(&ctx);
	return (0);
}
