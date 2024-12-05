#include <stdio.h>
#include <stdlib.h>
#include <fsieve.h>

int main() {
    int max_val = 0;
    printf("Insert the limit where we can search the prime numbers:\n");
    scanf("%d", &max_val);
    fsieve(max_val);
    return EXIT_SUCCESS;
}