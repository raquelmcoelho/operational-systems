#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <sys/wait.h>
#include <sin_cos_g.h>
#include <asm-generic/signal-defs.h>
#define _XOPEN_SOURCE 700

const Method sinMethod = {
    .calculate = &sin,
    .name = "sin",
    .dataFileName = "sinus.txt",
    .commandeFileName = "commande_sin.pg"
};

const Method cosMethod = {
    .calculate = &cos,
    .name = "cos",
    .dataFileName = "cosinus.txt",
    .commandeFileName = "commande_cos.pg"
};

void fillFileWith(Method method) {
    static int index = 0;

    if (index == 0) {
        remove(method.dataFileName);
    }

    FILE* file = fopen(method.dataFileName, "a");
    if (file == NULL) {
        perror("couln't open file");
        exit(EXIT_FAILURE);
    }

    double radians = (double)index * (M_PI / 180.0);
    printf("writing %s %.2f at %d\n", method.name, method.calculate(radians), getpid());
    fprintf(file, "%d %.2lf\n", index, method.calculate(radians));
    fclose(file);

    if (index == 360) {
        index = 0;
        exit(EXIT_SUCCESS);
    } else {
        index += 10;
        alarm(1);
    }
}

void fillCos() {
    fillFileWith(cosMethod);

}

void fillSin() {
    fillFileWith(sinMethod);
}

void fillValuesAtFile() {
    pid_t pid1 = fork();
    if (pid1 == 0) {
        struct sigaction sa1;
        memset(&sa1, 0, sizeof(sa1));
        sa1.sa_handler = &fillSin;
        if (sigaction(SIGALRM, &sa1, NULL) == -1) {
            perror("Error setting up SIGALRM");
            exit(EXIT_FAILURE);
        }

        alarm(1);
        while (1) {}

    } else if (pid1 == -1) {
        perror("Couldn't create child");
        exit(EXIT_FAILURE);
    }


    pid_t pid2 = fork();
    if (pid2 == 0) {
        struct sigaction sa2;
        memset(&sa2, 0, sizeof(sa2));
        sa2.sa_handler = &fillCos;
        if (sigaction(SIGALRM, &sa2, NULL) == -1) {
            perror("Error setting up SIGALRM");
            exit(EXIT_FAILURE);
        }
        alarm(1);
        while (1) {}

    } else if (pid2 == -1) {
        perror("Couldn't create child");
        exit(EXIT_FAILURE);
    }

    wait(NULL);
    wait(NULL);
}

void plot(Method method) {
    printf("plotting %s at %d", method.name, getpid());
    if (execlp("gnuplot", "gnuplot", "-persist", method.commandeFileName, NULL) == -1) {
        perror("couln't plot");
        exit(EXIT_FAILURE);
    }
}

void plotGnuplot() {
    pid_t pid1 = fork();
    if (pid1 == 0) {
        plot(sinMethod);
        return;
    } else if (pid1 == -1) {
        perror("Couldn't create child");
        exit(EXIT_FAILURE);
    }

    pid_t pid2 = fork();
    if (pid2 == 0) {
        plot(cosMethod);
        return;
    } else if (pid2 == -1) {
        perror("Couldn't create child");
        exit(EXIT_FAILURE);
    }

    wait(NULL);
    wait(NULL);
}


void writeAndPlot() {
    fillValuesAtFile();
    plotGnuplot();
}
