#ifndef SINCOSG_H
#define SINCOSG_H

#include <math.h>

typedef struct {
    double (*calculate)(double);
    char* name;
    char* dataFileName;
    char* commandeFileName;
} Method;

void fillFileWith(Method method);
void fillCos();
void fillSin();
void fillValuesAtFile();
void plot(Method method);
void plotGnuplot();
void writeAndPlot();

#endif // SINCOSG_H
