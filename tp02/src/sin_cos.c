
#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <../include/sin_cos.h>

void printTrigValues() {
    pid_t pid1 = fork();
    if (pid1 == 0) {
        printSin();
        return;
    } else if (pid1 == -1) {
        perror("Couldn't create child");
        exit(1);
    }

    pid_t pid2 = fork();
    if (pid2 == 0) {
        printCos();
        return;
    } else if (pid2 == -1) {
        perror("Couldn't create child");
        exit(1);
    }

    wait(NULL);
}


void printSin() {
    for (int i = 0; i <= 360; i += 100) {
        double radians = (double)i * (M_PI / 180.0);
        printf("Child 1(%d): sinus(%d)=%.2lf\n", getpid(), i, sin(radians));
        sleep(1);
    }

    exit(0);
}

void printCos() {
    for (int i = 0; i <= 360; i += 100) {
        double radians = (double)i * (M_PI / 180.0);
        printf("Child 2(%d): cosinus(%d)=%.2lf\n", getpid(), i, cos(radians));
        sleep(1);
    }

    exit(0);
}