#ifndef METHOD4X2_H
#define METHOD4X2_H

#include <math.h>

class Method4x2{
private:
    double *x;
    double S1,S2,S3;
    double x0t,x1t,x2t,x3t; //total
    double x0o,x1o,x2o,x3o; //old
    double *x_default;
    int circle_count;
    int circle_size;

public:
    int Q,M;

    /* структура выходных значений амплитуды и частоты */
    struct out{
        double freq;
        double ampl;
    };
  
    /* иницилизация циклического буффера и метода для рекурсивного выполнения */
    void init();
    void clear();
    double circle_get(int);
    /* рекурсивное выполнение метода */
    out exec(double);
    /* усреднение medial(x[N],M,Q,N) */
    out medial(double *,int,int);
    
};

#endif

/* EOF */
