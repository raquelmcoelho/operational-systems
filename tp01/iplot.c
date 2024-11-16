#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "iplot.h"

void writeFileContent(double limit) {
    FILE *file = fopen("commandes.gp", "w");
    if (file == NULL) {
        perror("Erro while trying to open commandes.gp");
        exit(1);
    }

    fprintf(file, "set samples 500\n");
    fprintf(file, "set title \"Sinus cardinal\"\n");
    fprintf(file, "set xlabel \"x\"\n");
    fprintf(file, "set ylabel \"sin(x)/x\"\n");
    fprintf(file, "set xrange [-%f:%f]\n", limit, limit);
    fprintf(file, "plot sin(x)/x\n");
    fclose(file);
}

void executeGnuplot() {
    if (execlp("gnuplot", "gnuplot", "-persist", "commandes.gp", NULL) == -1) {
        perror("Error at gnuplot");
        exit(1);
    }
}
