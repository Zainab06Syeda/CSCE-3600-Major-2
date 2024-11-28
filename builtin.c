#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

extern char **environ; // Access the environment variables

// Change directory
void change_directory(char *path) {
    if (path == NULL) {
        path = getenv("HOME");  // Default to HOME if no path is given
    }
    
    if (chdir(path) != 0) {
        perror("cd failed");
    }
}

// Print environment path
void print_path() {
    printf("PATH: %s\n", getenv("PATH"));
}

// Exit the shell
void exit_shell() {
    printf("Exiting shell...\n");
    exit(0);
}

// Built-in command handler
int handle_builtin_commands(char **args) {
    if (args[0] == NULL) return 0; // No command

    if (strcmp(args[0], "cd") == 0) {
        change_directory(args[1]);
        return 1;
    }
    if (strcmp(args[0], "path") == 0) {
        print_path();
        return 1;
    }
    if (strcmp(args[0], "exit") == 0) {
        exit_shell();
        return 1;
    }

    return 0; // Not a built-in command
}
