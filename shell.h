#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1024

void run_shell(char *name);
int execute_command(char *line, char *name);
char *get_command_path(char *command);

extern char **environ;

#endif
