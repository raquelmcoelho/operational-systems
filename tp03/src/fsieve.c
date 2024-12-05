#include "fsieve.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


void writePrimeNumberAtFile(int value) {
    FILE *file = fopen("prime_numbers.txt", "a");
    printf("(PID %d) - adding %d to file\n", getpid(), value);
    fprintf(file,"%d\n",value);
    fflush(file);
    fclose(file);
} 