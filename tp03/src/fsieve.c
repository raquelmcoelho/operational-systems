#include "fsieve.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>	
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>	
#include <ctype.h>

#define BYTE_SIZE 1	
#define INPUT 1	
#define OUTPUT 0
#define FINISH_NUMBER -1
#define PRINT 0

const char filename[] = "prime_numbers.txt";
int number_of_pipes = 0;

void fsieve(int limit) {
    int external_pipe[2];

    if (pipe(external_pipe) == -1) {
        handle_fatal_error("Error creating pipe.\n");
    }

    send_all_numbers_to_first_pipe(external_pipe, limit);
    remove(filename);
    manage_process(external_pipe);
}

void send_all_numbers_to_first_pipe(int external_pipe[], int limit) {
    for(int i = 2; i <= limit + 1; i++) {
        int number = i;
        if(i == limit + 1) {
            number = FINISH_NUMBER;
        }
        write(external_pipe[INPUT], &number, sizeof(i));
    }
}

void handle_fatal_error(char msg[]) {
    printf("%s", msg);
    exit(EXIT_FAILURE);
}

void manage_process(int parent_pipe[]) {
    if(PRINT) 
        printf("(PID %d) - managing process\n", getpid());

    int current_prime, child_pipe[2];

    handle_proccess_prime(parent_pipe, &current_prime);
    printf("PIPES: %d\n", number_of_pipes++);
    if (pipe(child_pipe) == -1) {
        handle_fatal_error("Error creating pipe.\n");
    }

    create_next_filter(parent_pipe, child_pipe);
    filter_numbers(parent_pipe, child_pipe, current_prime);

    wait(NULL);
    if(PRINT) 
        printf("(PID %d) - has received child termination.\n", getpid() );
}

void handle_proccess_prime(int parent_pipe[], int *current_prime) {
    if(read(parent_pipe[OUTPUT], current_prime, sizeof(int)) > 0) {
        if(PRINT) 
            printf("(PID %d) - prime of this process: %d\n", getpid(), *current_prime);
        if(*current_prime == FINISH_NUMBER) {
            close(parent_pipe[OUTPUT]);
            exit(EXIT_SUCCESS);
        }

        write_prime_number_at_file(*current_prime);
    }
}

void create_next_filter(int parent_pipe[], int child_pipe[]) {
    pid_t pid;

    pid = fork();
    if (pid < 0) {
        handle_fatal_error("Error using fork().\n");
    }
    
    if (pid == 0) {
        manage_process(child_pipe);
        close(parent_pipe[OUTPUT]);
        exit(EXIT_SUCCESS);
    }
}

void filter_numbers(int parent_pipe[], int child_pipe[], int current_prime) {
    int int_buffer;
    close(parent_pipe[INPUT]);
    close(child_pipe[OUTPUT]);

    while (read(parent_pipe[OUTPUT], &int_buffer, sizeof(int)) > 0) {
        if(PRINT) 
            printf("(PID %d) - reading %d from parent pipe\n", getpid(), int_buffer);  
        if(int_buffer % current_prime > 0 || int_buffer == FINISH_NUMBER) {
            if(PRINT) 
                printf("(PID %d) - sending %d to child pipe\n", getpid(), int_buffer);        
            write(child_pipe[INPUT], &int_buffer, sizeof(int));
        }
        if(int_buffer == FINISH_NUMBER) {
            break;
        }
    }

    close(child_pipe[INPUT]);
    close(parent_pipe[OUTPUT]);
}


void write_prime_number_at_file(int value) {
    FILE *file = fopen(filename, "a");
    if(PRINT) 
        printf("(PID %d) - adding %d to file\n", getpid(), value);
    fprintf(file,"%d\n",value);
    fflush(file);
    fclose(file);
} 
