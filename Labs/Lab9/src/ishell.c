#include "ishell.h"
#include "wrappers.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_LINE 1024
#define MAX_TOKENS 100

int main() 
{
    // Infinite while loop
    while(1) 
    {
        // Set up initial string data structures for commands
        char cmd[MAX_LINE] = {0}; // string of original cmd
        char *all_cmd_tok[MAX_TOKENS] = {0};
        char *cmd_tok[MAX_TOKENS] = {0}; // array of string(tokens) for a single command
        int cmd_count = 0; // number of total commands
        int token_count = 0; // number of tokens in a single cmd
        int exit_flag = 0;

        // Print "ishell> " prompt
        printf("ishell> ");
        fflush(stdout);

        // Get input from user
        if (!fgets(cmd, sizeof(cmd), stdin)) {
            break;
        }
        // Remove newline
        cmd[strcspn(cmd, "\n")] = 0;

        // Skip empty input
        if (cmd[0] == '\0') {
            continue;
        }

        // Parse all commands
        char *token = strtok(cmd, ";");
        while (token != NULL && cmd_count < MAX_TOKENS - 1)
        {
            all_cmd_tok[cmd_count] = token;
            token = strtok(NULL, ";");
            cmd_count++;
        }
        all_cmd_tok[cmd_count] = NULL;  // execvp expects a NULL-terminated array

        // Invalid parsing
        if (cmd_count <= 0)
        {
            break;
        }

        // Parse every command
        for (int i = 0; i < cmd_count; i++)
        {
            char *cleaned_cmd = trim(all_cmd_tok[i]);
            // Built-in command: exit
            if (strcmp(cleaned_cmd, "exit") == 0) {
                exit_flag = 1;
                break;
            }

            token_count = 0;
            char *token = strtok(cleaned_cmd, " ");
            while (token != NULL && token_count < MAX_TOKENS - 1)
            {
                cmd_tok[token_count] = token;
                token = strtok(NULL, " ");
                token_count++;
            }
            cmd_tok[token_count] = NULL;  // execvp expects a NULL-terminated array

            // Invalid parsing
            if (token_count <= 0)
            {
                break;
            }

            // Fork a child process to execvp the command
            pid_t pid = fork();
            // child
            if (pid == 0) 
            {
                execvp(cmd_tok[0], cmd_tok);
                // If child process is not replaced by execvp process
                perror("execvp failed");
                exit(EXIT_FAILURE);
            } 
            else if (pid > 0) {
                // Parent
                int status;
                waitpid(pid, &status, 0);
                // Check for errors (status code)
                if (WIFEXITED(status))
                {
                    int exit_code = WEXITSTATUS(status);
                    if (exit_code == 0)
                    {
                        printf("[ishell: program terminated successfully]\n");
                    } 
                    else {
                        printf("[ishell: program terminated abnormally][exit code: %d]\n", exit_code);
                    }
                } 
                else if (WIFSIGNALED(status)) {
                    printf("[ishell: program was terminated by signal %d]\n", WTERMSIG(status));
                }
            } 
            else {
                perror("fork failed");
            }
        }

        // If need to exit
        if (exit_flag == 1)
        {
            break;
        }
    }

    printf("Exiting ishell.\n");
    return 0;
}