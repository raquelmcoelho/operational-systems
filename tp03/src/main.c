#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>	
#include <sys/types.h>	
#include <sys/stat.h>
#include <ctype.h>
#include <sys/wait.h>
#include <fsieve.h>

#define BYTE_SIZE 1	
#define INPUT 1	
#define OUTPUT 0	


const char filename[] = "prime_numbers.txt";

void handle_fatal_error(char msg[]) {
    printf("%s", msg);
    exit(EXIT_FAILURE);
}

void manage_process(int parent_pipe[]) {
    printf("(PID %d) - managing process\n", getpid());
    int int_buffer;
    int current_prime;
    if(read(parent_pipe[OUTPUT], &current_prime, sizeof(int)) > 0) {
        printf("(PID %d) - prime of this process: %d\n", getpid(), current_prime);
        if(current_prime == -1) {
            close(parent_pipe[OUTPUT]);
            return;
        }
        
        writePrimeNumberAtFile(current_prime);
    }

    pid_t pid;
    int son_pipe[2];

    if (pipe(son_pipe) == -1) {
        handle_fatal_error("Error creating pipe.\n");
    }

    pid = fork();
    if (pid < 0) {
        handle_fatal_error("Error using fork().\n");
    }
    if (pid == 0) {
        manage_process(son_pipe);
        return;
    }

    close(parent_pipe[INPUT]);
    close(son_pipe[OUTPUT]);

    while (read(parent_pipe[OUTPUT], &int_buffer, sizeof(int)) > 0) {
        printf("(PID %d) - reading %d from parent pipe\n", getpid(), int_buffer);  
        if(int_buffer % current_prime > 0 || int_buffer == -1) {
            printf("(PID %d) - sending %d to child pipe\n", getpid(), int_buffer);        
            write(son_pipe[INPUT], &int_buffer, sizeof(int));
        }
        if(int_buffer == -1) {
            break;
        }
    }

    close(son_pipe[INPUT]);
    close(parent_pipe[OUTPUT]);
    wait(NULL);
    printf("(PID %d): has received child termination.\n", getpid() );
}

int main() {
    int max_val = 0;
    printf("Insert the limit where we can search the prime numbers:\n");
    scanf("%d", &max_val);

    int external_pipe[2];

    if (pipe(external_pipe) == -1) {
        handle_fatal_error("Error creating pipe.\n");
    }

    for(int i = 2; i <= max_val + 1; i++) {
        int number = i;
        if(i == max_val + 1) {
            number = -1;
        }
        write(external_pipe[INPUT], &number, sizeof(i));
    }

    remove(filename);

    manage_process(external_pipe);

    return EXIT_SUCCESS;
}