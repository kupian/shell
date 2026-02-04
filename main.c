//
// Created by Alex Carr on 02/02/2026.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#define MAX_INPUT_LENGTH 256
#define MAX_ARGUMENTS 10

void execute(char* input) {
    char* program = strtok(input, " ");
    char *argv[MAX_ARGUMENTS] = {NULL};

    int i = 0;
    argv[i] = program;

    char* nextArg;
    do {
        nextArg = strtok(NULL, " ");
        argv[++i] = nextArg;
    } while (nextArg != NULL);

    if (execvp(program, argv) == -1) {
        printf("Error starting %s: %s\n", argv[0], strerror(errno));
    }
}

int main() {
    printf("Shell by Alex Carr\n");

    while (1) {
        printf("> ");

        char* input = malloc(MAX_INPUT_LENGTH);
        fgets(input, MAX_INPUT_LENGTH, stdin);
        input[strlen(input) - 1] = '\0'; // Strip the newline character

        if (strcmp(input, "exit") == 0) return 0;

        pid_t pid = fork();
        if (pid != 0 ) {
            waitpid(pid, NULL, 0);
        }
        else {
            execute(input);
        }
    }
}