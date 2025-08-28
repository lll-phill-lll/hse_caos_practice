#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TOKENS 128
#define MAX_ARGS 16

typedef struct {
    char *args[MAX_ARGS];  
    char *input;          
    char *output;        
    char *error;        
    int append;        
} Command;

typedef struct {
    Command commands[MAX_TOKENS];
    int count;                  
} ParsedInput;

void parse_input(const char *input, ParsedInput *parsed) {
    char *tokens[MAX_TOKENS];
    int token_count = 0;
    char buffer[strlen(input) + 1];
    strcpy(buffer, input);
    char *token = strtok(buffer, " ");
    
    while (token && token_count < MAX_TOKENS) {
        tokens[token_count++] = token;
        token = strtok(NULL, " ");
    }
    
    parsed->count = 0;
    Command *cmd = &parsed->commands[parsed->count];
    memset(cmd, 0, sizeof(Command));
    int arg_index = 0;

    for (int i = 0; i < token_count; i++) {
        if (strcmp(tokens[i], "|") == 0) {
            cmd->args[arg_index] = NULL;
            parsed->count++;
            cmd = &parsed->commands[parsed->count];
            memset(cmd, 0, sizeof(Command));
            arg_index = 0;
        } else if (strcmp(tokens[i], ">") == 0 || strcmp(tokens[i], ">>") == 0) {
            cmd->append = (tokens[i][1] == '>');
            if (i + 1 < token_count) cmd->output = tokens[++i];
        } else if (strcmp(tokens[i], "2>") == 0) {
            if (i + 1 < token_count) cmd->error = tokens[++i];
        } else if (strcmp(tokens[i], "<") == 0) {
            if (i + 1 < token_count) cmd->input = tokens[++i];
        } else {
            if (arg_index < MAX_ARGS - 1) cmd->args[arg_index++] = tokens[i];
        }
    }
    cmd->args[arg_index] = NULL;
    parsed->count++;
}

void print_parsed(const ParsedInput *parsed) {
    for (int i = 0; i < parsed->count; i++) {
        printf("Command %d:\n", i + 1);
        for (char *const *arg = parsed->commands[i].args; *arg; arg++) {
            printf("  Arg: %s\n", *arg);
        }
        if (parsed->commands[i].input) printf("  Input: %s\n", parsed->commands[i].input);
        if (parsed->commands[i].output) printf("  Output: %s (%s)\n", parsed->commands[i].output, parsed->commands[i].append ? "append" : "write");
        if (parsed->commands[i].error) printf("  Stderr: %s\n", parsed->commands[i].error);
    }
}
