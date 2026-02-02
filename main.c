//
// Created by Alex Carr on 02/02/2026.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#define MAX_INPUT_LENGTH 256

void execute(char* program) {
    char *argv[] = {program, NULL};
    if (execvp(program, argv) == -1) {
        printf("Error starting %s: %s\n", argv[0], strerror(errno));
    }
}

int main() {
    printf("Shell by Alex Carr\n");

    while (1) {
        printf("> ");

        char* input = malloc(MAX_INPUT_LENGTH);
        scanf("%s", input);

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