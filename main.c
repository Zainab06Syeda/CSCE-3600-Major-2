#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

#define MAX_HISTORY 20

void prompt() {
    printf("my_shell> ");
}

void execute_command(char **args) {
    pid_t pid = fork();
    if (pid == 0) {
        // Child process
        if (execvp(args[0], args) == -1) {
            perror("Error executing command");
        }
        exit(EXIT_FAILURE);
    } else if (pid > 0) {
        // Parent process
        wait(NULL);
    } else {
        perror("Fork failed");
    }
}

int main(int argc, char *argv[]) {
    char *line = NULL;
    size_t len = 0;
    ssize_t nread;
    char *args[100];
    
    while (1) {
        prompt();

        nread = getline(&line, &len, stdin);
        if (nread == -1) {
            perror("getline");
            break;
        }

        // Tokenize the input
        int i = 0;
        char *token = strtok(line, " \n");
        while (token != NULL) {
            args[i++] = token;
            token = strtok(NULL, " \n");
        }
        args[i] = NULL;

        if (args[0] == NULL) {
            continue; // Empty command
        }

        // Implement built-in commands here
        if (strcmp(args[0], "exit") == 0) {
            break;
        }

        execute_command(args);
    }

    free(line);
    return 0;
}
