#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

void run_shell(char *simple_shell);
int execute_command(char *line, char *simple_shell, int line_number);

# define BUFFER_SIZE (1024)
# define PROMPT_TEXT "$ "
# define ERRFILE     "No such file or directory\n"
# define ERRFOUND    "not found\n"

#endif
