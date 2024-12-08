#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include "shell.h"

extern char **environ; // Access the environment variables
char path[MAX_PATH_LENGTH] = ""; // Global path variable

// Change directory
void cd(char *path) {
    if (path == NULL) {
        char *home = getenv("HOME");
        if (home == NULL) {
            perror("cd: Unable to find HOME");
            return;
        }
        if (chdir(home) != 0) {
            perror("cd");
        }
    } else {
        if (chdir(path) != 0) {
            perror("cd");
        }
    }
}

// Print or modify the PATH
void handle_path(char **args) {
    if (args[1] == NULL) {
        printf("%s\n", path);
    } else if (strcmp(args[1], "+") == 0 && args[2] != NULL) {
        if (strlen(path) + strlen(args[2]) + 1 < MAX_PATH_LENGTH) {
            if (strlen(path) > 0) strcat(path, ":");
            strcat(path, args[2]);
        } else {
            fprintf(stderr, "path: Path too long to add\n");
        }
    } else if (strcmp(args[1], "-") == 0 && args[2] != NULL) {
        char *start = strstr(path, args[2]);
        if (start) {
            int len = strlen(args[2]);
            memmove(start, start + len + (start[len] == ':' ? 1 : 0), strlen(start + len) + 1);
            if (start > path && *(start - 1) == ':') *(start - 1) = '\0';
        } else {
            fprintf(stderr, "path: Pathname not found\n");
        }
    } else {
        fprintf(stderr, "path: Invalid arguments\n");
    }
}

// Exit the shell
void builtin_exit(int status) {
    exit(status);
}

// Handle built-in commands
int handle_builtin_commands(char **args) {
    if (args[0] == NULL) return 0;

    if (strcmp(args[0], "cd") == 0) {
        cd(args[1]);
        return 1;
    } else if (strcmp(args[0], "path") == 0) {
        handle_path(args);
        return 1;
    } else if (strcmp(args[0], "exit") == 0) {
        builtin_exit(0);
    }

    return 0;
}
