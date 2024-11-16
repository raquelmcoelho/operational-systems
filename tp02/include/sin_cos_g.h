#ifndef SINCOSG_H
#define SINCOSG_H

#include <math.h>

typedef struct {
    double (*calculate)(double);
    char* name;
    char* dataFileName;
    char* commandeFileName;
} Method;

void main_();
void fillValuesAtFile();
void fillFileWith(Method method);
void plotGnuplot();
void plot(Method method);

#endif // SINCOSG_H
