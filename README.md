# Simple Shell

## Table of Contents
- [Description](#description)
- [Project Stages](#project-stages)
- [Features](#features)
- [System Calls Used](#system-calls-used)
- [Compilation](#compilation)
- [Usage Examples](#usage-examples)
- [Project Architecture](#project-architecture)
- [Authors](#authors)

## Description
The project is a simple version of `/bin/sh`. It is study the inner working of Linux operating system, while focusing on functions like `fork`, `execve`, and `wait`. However, each code is written in C and adheres strictly to betty style for formatting and documentation.  

## Project Stages
**1. Betty Adherence:** 
Every file is checked against the betty-style.pl and betty-doc.pl scripts. This ensures clean, readable, and well-documented code with limited functions per file and characters per line.

**2. Simple Shell 0.1:** 
- Displays a prompt `#cisfun$`.
- Executes single-word commands (no arguments).
- Handles End-of-File (Ctrl+D) to exit gracefully.
- Uses absolute paths for execution (e.g., `/bin/ls`).

**3. Simple Shell 0.2:**
- Implementation of a string tokenizer to handle spaces.
- Users can now pass arguments (e.g., `ls -l /tmp`).

**4. Simple Shell 0.3:**
- No longer requires absolute paths.
- The shell parses the `PATH` environment variable to locate executables.
- **Optimization:** `fork` is only called if the command is verified to exist.

**5. Simple Shell 0.4:**
- Implementation of the internal `exit` command to terminate the shell.

**6. Simple Shell 1.0:**
- Implementation of the `env` command to print the current user environment variables.

## Features
- **Interactive Mode:** Type commands directly into the prompt.
- **Non-Interactive Mode:** Pipe scripts or commands into the shell (e.g., `echo "/bin/ls" | ./shell`).
- **Path Resolution:** Automatic lookup of commands in `/bin/`, `/usr/bin/`, etc.
- **Error Handling:** Prints standard error messages when commands are not found or permissions are denied.
- **Signal Handling:** Specifically handles `Ctrl+C` (SIGINT) to ensure the shell doesn't terminate unexpectedly.

## System Calls Used
**`access`:** Check file permissions/existence.  
**`execve`:** Replace current process image with a new program.  
**`fork`:** Create a child process.  
**`wait`:** Synchronize parent with child completion.  
**`getline`:** Read a full line from stdin.  
**`strtok`:** Tokenize strings into command arguments.  
**`stat`:** Get file status to check for existence in PATH.  

## Compilation
Clone this repository and compile using the following:
```
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
```

## Usage Examples

- **Interactive Mode**
```
$ ./hsh
#cisfun$ ls -l
total 24
-rw-rw-r-- 1 user user 1205 May 15 10:00 main.c
-rwxrwxr-x 1 user user 8904 May 15 10:01 hsh
#cisfun$ env
USER=julien
PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin
#cisfun$ exit
```
- **Non-Interactive Mode**
```
$ echo "ls" | ./hsh
main.c hsh shell.c
```

## Project Architecture
```
├── main.c              # Entry point & REPL loop  
├── shell.c             # Builtin command logic (cd, setenv, exit)  
├── execute_command.c   # Process creation (fork & execve)  
├── path.c              # PATH resolution & memory management  
├── strings.c           # String utilities & custom tokenizer  
├── getline.c           # Custom input stream handling  
├── shell.h             # Global macros, structs, and prototypes  
└── getline.h           # Header for the custom getline function  
```

- **The Execution Flow (REPL)**

**1.Read:** `_getline` captures the user input from `stdin`.

**2.Tokenize:** `_strtok` parses the input string into an array of arguments (`argv`).

**3.Validate:** The shell checks if the command is a **Builtin** (managed in `shell.c`).

**4.Resolve:** If not a builtin, `find_path` (in `path.c`) searches the system `PATH` to find the binary.

**5.Execute:** `execute_command` forks a child process and calls `execve` to run the program.

**6.Cleanup:** The parent waits for the child to finish, updates the exit status, and frees temporary memory before re-displaying the prompt.


- **Data Architecture & Memory Management**

The shell maintains state using a centralized context structure:

**1. Context Control:** We use `shell_ctx_t` to avoid global variables. It tracks the heap-allocated environment and the exit status of the last command.

**2. Heap-Allocated Environment:** Unlike simple shells that use the inherited `environ`, this shell duplicates the environment to the heap using `copy_env`.

This allows for dynamic modification via `setenv`.

It ensures a "Clean Exit" strategy where all allocated memory is freed at termination, resulting in **0 leaks** in Valgrind.

- **Error Management**

Error reporting is standardized across the architecture to match the sh (Bourne Shell) specification:

**1. Command Not Found:** Handled in `execute_command.c` (Exit status 127).

**2. Builtin Errors:** Handled in `shell.c` (Exit status 2).

**3. Permission Denied:** Uses system `errno` values to report specific access issues.

## Authors

**Fai AlSharekh** - [GitHub](https://github.com/Fai-Web-Lab)  
**Manar AlThaqfi** - [GitHub](https://github.com/manaralthqfiu)