#ifndef SHELL_H
#define SHELL_H

void prompt();
void execute_command(char **args);
int handle_builtin_commands(char **args);
int handle_history_command(char **args);
void add_to_history(const char *command);

#endif
