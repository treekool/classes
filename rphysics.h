/* (c) 2015
 * попытка создать класс с кучей радиофизических "плюшек"
 */

#ifndef RPHYSICS_H
#define RPHYSICS_H

#include <stdlib.h>
#include <math.h>

class rPhysics{
public:
    double grandom(double, double);
    void fft(double *,double *,int);
};

#endif // RPHYSICS_H

