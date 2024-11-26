#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>	
#include <sys/types.h>	
#include <sys/stat.h>
#include <ctype.h>
#include <sys/wait.h>



// const char filename[] = "prime_numbers.txt";


#define BYTE_SIZE 1	
#define INPUT 1	
#define OUTPUT 0	

void handle_fatal_error(char msg[]) {
    // printf(msg);
    exit(EXIT_FAILURE);
}

void manage_parent(int anonymous_pipe[]) {
    char byte;
    printf("Parent process (PID %d)\n", getpid());
    close(anonymous_pipe[OUTPUT]);
    while (read(STDIN_FILENO, &byte, BYTE_SIZE) > 0) {
        if (isalnum(byte)) {
            write(anonymous_pipe[INPUT], &byte, 1);
        }
    }
    close(anonymous_pipe[INPUT]);
    wait(NULL);
    printf("Parent: has received child termination.\n");
}

void manage_child(int anonymous_pipe[]) {
    char byte;
    int letters = 0;
    int digits = 0;
    printf("Child process (PID %d)\n", getpid());
    printf("Enter Ctrl-D to end.\n");
    close(anonymous_pipe[INPUT]);
    while (read(anonymous_pipe[OUTPUT], &byte, BYTE_SIZE) > 0) {
        if (isdigit(byte)) {
            digits++;
        } else {
            letters++;
        }
    }
    close(anonymous_pipe[OUTPUT]);
    printf("\n%d digits received\n", digits);
    printf("%d letters received\n", letters);
}

int main() {
    // int max_val = 0;
    // printf("Insert the limit where we can search the prime numbers:\n");
    // scanf(&max_val);

    pid_t pid;
    int anonymous_pipe[2]; /* pipe descriptors */
    if (pipe(anonymous_pipe) == -1) {
        handle_fatal_error("Error creating pipe.\n");
    }
    pid = fork();
    if (pid < 0) {
        handle_fatal_error("Error using fork().\n");
    }
    if (pid > 0) {
        manage_parent(anonymous_pipe);
    } else {
        manage_child(anonymous_pipe);
    }

    return EXIT_SUCCESS;
}