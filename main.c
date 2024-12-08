#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "shell.h"

void prompt() {
    printf("my_shell> ");
}

void execute_command(char **args) {
    pid_t pid = fork();
    if (pid == 0) {
        if (execvp(args[0], args) == -1) {
            perror("Error executing command");
        }
        exit(EXIT_FAILURE);
    } else if (pid > 0) {
        wait(NULL);
    } else {
        perror("Fork failed");
    }
}

int main(int argc, char *argv[]) {
    char *line = NULL;
    size_t len = 0;
    char *args[100];
    
    while (1) {
        prompt();

        if (getline(&line, &len, stdin) == -1) {
            perror("getline");
            break;
        }

        add_to_history(line);

        int i = 0;
        char *token = strtok(line, " \n");
        while (token != NULL) {
            args[i++] = token;
            token = strtok(NULL, " \n");
        }
        args[i] = NULL;

        if (args[0] == NULL) continue;

        if (handle_builtin_commands(args) || handle_history_command(args)) {
            continue;
        }

        execute_command(args);
    }

    clear_history();
    free(line);
    return 0;
}
