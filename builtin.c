#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

extern char **environ; // Access the environment variables

// Change directory
void cd(char *path) {
    if (path == NULL) {
        // If no argument is provided, change to HOME directory
        char *home = getenv("HOME");
        if (home == NULL) {
            perror("cd: Unable to find HOME");
            return;
        }
        if (chdir(home) != 0) {
            perror("cd");
        }
    } else {
        // Change to the specified directory
        if (chdir(path) != 0) {
            perror("cd");
        }
    }
}

// Print environment path
void path(char **args) {
    if (args[1] == NULL) {
        // Display the current path
        printf("%s\n", path);
    } 
    else if (strcmp(args[1], "+") == 0 && args[2] != NULL) // If the first arg is '+', append the path var args[2].
    {
        // Append the specified pathname
        if (strlen(path) + strlen(args[2]) + 1 < MAX_PATH_LENGTH) {
            if (strlen(path) > 0) strcat(path, ":");
            strcat(path, args[2]);
        } else {
            fprintf(stderr, "path: Path too long to add\n");
        }
    } 
    else if (strcmp(args[1], "-") == 0 && args[2] != NULL) // If '-' is the first arg, remove args[2] from the PATH
    {
        // Remove the specified pathname
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
void exit(int status) {
    // Exit the shell
    exit(status);
}

// Built-in command handler
int handle_builtin_commands(char **args) {
    if (args[0] == NULL) return 0; // No command

    if (strcmp(args[0], "cd") == 0) // if command entered is cd, call "cd"
    {
        cd(&args);
        return 1;
    }
    if (strcmp(args[0], "path") == 0) {
        path(&args);
        return 1;
    }
    if (strcmp(args[0], "exit") == 0) {
        exit();
    }

    return 0; // Not a built-in command
}
