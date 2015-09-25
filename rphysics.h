/* (c) 2015
 * попытка создать класс с кучей радиофизических "плюшек"
 */

#ifndef RPHYSICS_H
#define RPHYSICS_H

#include <stdlib.h>
#include <math.h>
#include <time.h>

class rPhysics{
public:
    double grandom(double, double);
    void fft(double *,double *, int);
    double dispersion(double *, int, int);
    void init_random(void);
};

#endif // RPHYSICS_H

/* EOF */
