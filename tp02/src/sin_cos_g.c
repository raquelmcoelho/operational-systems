#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sin_cos_g.h>

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
    for (int i = 0; i <= 360; i += 100) {
        FILE* file = fopen(method.dataFileName, "a");
        if (file == NULL) {
            perror("couln't open file");
            exit(1);
        }

        double radians = (double)i * (M_PI / 180.0);
        printf("writing %s %.2f at %d\n", method.name, method.calculate(radians), getpid());
        fprintf(file, "%d %.2lf\n", i, method.calculate(radians));
        fclose(file);

        sleep(1);
    }

    exit(0);
}

void fillValuesAtFile() {
    pid_t pid1 = fork();
    if (pid1 == 0) {
        fillFileWith(sinMethod);
        return;
    } else if (pid1 == -1) {
        perror("Couldn't create child");
        exit(1);
    }

    pid_t pid2 = fork();
    if (pid2 == 0) {
        fillFileWith(cosMethod);
        return;
    } else if (pid2 == -1) {
        perror("Couldn't create child");
        exit(1);
    }

    wait(NULL);
}



void plot(Method method) {
    printf("plotting %s at %d", method.name, getpid());
    if (execlp("gnuplot", "gnuplot", "-persist", method.commandeFileName, NULL) == -1) {
        perror("couln't plot");
        exit(1);
    }
}


void plotGnuplot() {
    pid_t pid1 = fork();
    if (pid1 == 0) {
        plot(sinMethod);
        return;
    } else if (pid1 == -1) {
        perror("Couldn't create child");
        exit(1);
    }

    pid_t pid2 = fork();
    if (pid2 == 0) {
        plot(cosMethod);
        return;
    } else if (pid2 == -1) {
        perror("Couldn't create child");
        exit(1);
    }
}

void main_() {
    fillValuesAtFile();
    plotGnuplot();
}
