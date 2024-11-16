#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "iplot.h"

int main() {
    double limit;

    while (1) {
        printf("Enter the limit: ");
        scanf("%lf", &limit);

        if (limit < 0) {
            break;
        }

        writeFileContent(limit);

        pid_t pid = fork();
        if (pid == -1) {
            perror("Error at fork");
            exit(1);
        } else if (pid == 0) {
            sleep(5); 
            executeGnuplot();
        } else {
            wait(NULL);
        }
    }

    return 0;
}
