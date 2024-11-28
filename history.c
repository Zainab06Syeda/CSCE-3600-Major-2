#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_HISTORY 20

char *history[MAX_HISTORY];
int history_count = 0;

void add_to_history(const char *command) {
    if (history_count < MAX_HISTORY) {
        history[history_count] = strdup(command);
        history_count++;
    } else {
        free(history[0]); // Free the oldest history
        for (int i = 1; i < MAX_HISTORY; i++) {
            history[i - 1] = history[i];
        }
        history[MAX_HISTORY - 1] = strdup(command);
    }
}

void print_history() {
    printf("Command History:\n");
    for (int i = 0; i < history_count; i++) {
        printf("%d: %s\n", i + 1, history[i]);
    }
}

void clear_history() {
    for (int i = 0; i < history_count; i++) {
        free(history[i]);
    }
    history_count = 0;
}

int handle_history_command(char **args) {
    if (strcmp(args[0], "myhistory") == 0) {
        if (args[1] == NULL) {
            print_history();
        } else if (strcmp(args[1], "-c") == 0) {
            clear_history();
        } else if (strcmp(args[1], "-e") == 0 && args[2] != NULL) {
            int cmd_index = atoi(args[2]) - 1;
            if (cmd_index >= 0 && cmd_index < history_count) {
                printf("Executing: %s\n", history[cmd_index]);
                // Execute the historical command
                char *cmd = history[cmd_index];
                char *args[100];
                char *token = strtok(cmd, " \n");
                int i = 0;
                while (token != NULL) {
                    args[i++] = token;
                    token = strtok(NULL, " \n");
                }
                args[i] = NULL;
                execute_command(args); // Reusing the execute_command function from main.c
            }
        }
        return 1;
    }

    return 0;
}
