#ifndef FSIEVE_H
#define FSIEVE_H

void fsieve(int limit);
void send_all_numbers_to_first_pipe(int external_pipe[], int limit);
void handle_fatal_error(char msg[]);
void manage_process(int parent_pipe[]);
void handle_proccess_prime(int parent_pipe[], int *current_prime);
void create_next_filter(int parent_pipe[], int child_pipe[]);
void filter_numbers(int parent_pipe[], int child_pipe[], int current_prime);
void write_prime_number_at_file(int value);

#endif // FSIEVE_H