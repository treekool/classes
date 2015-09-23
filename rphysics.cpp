#include "rphysics.h"

/* нормальный рандом */
// (мат. ожидание, дисперися)
double rPhysics::grandom(double M,double sigma){
    double x1,x2,y1,y2,w;
    do{
        x1=2.0*rand()/RAND_MAX-1.0;
        x2=2.0*rand()/RAND_MAX-1.0;
        w=x1*x1+x2*x2;
    }while(w>=1.0);

    w=sqrt((-2.0*log(w))/w);

    y1=x1*w;
    y2=x2*w;

    return M+y1*sigma;
}


/* Быстрое фурье */
void rPhysics::fft(double *real,double *imgn,int n){
    int step,start,old_start,i,j,theta=0;
    double tmpReal,tmpImgn;

    /******** Reverse bits *****/
    int b=0,l,k,bits=log(n)/log(2);
    double *copy_real = new double [n];
    for(i=0;i<n;i++) copy_real[i]=real[i];
    for(i=0;i<n;i++){
        b=0,k=bits;
        for(l=0;l<bits;l++){
            k--;
            b|=(((i&(1<<l)))>>l)<<k;
        }

        real[i] = copy_real[b];
        //real[i] = copy_real[rbit(i,10)];  // N = 1024
        //c_x[i].Real = x[rbit(i,3)];  // N = 8
    }

    /****************************/

    for(step=1;step<n;step = step << 1){
        old_start=0;
        for(start=step << 1;start<=n;start+=step << 1){
            theta = 0;
            for(i=old_start;i<start-step;i++){
                j=i+step;
                /* a-bc */

                tmpReal = real[i]-(real[j]*cos(-theta*2*M_PI/(step<<1))-
                                  imgn[j]*sin(-theta*2*M_PI/(step<<1)));
                tmpImgn = imgn[i]-(real[j]*sin(-theta*2*M_PI/(step<<1))+
                                  imgn[j]*cos(-theta*2*M_PI/(step<<1)));

                /* a+bc */

                real[i] = real[i]+(real[j]*cos(-theta*2*M_PI/(step<<1))-
                                  imgn[j]*sin(-theta*2*M_PI/(step<<1)));
                imgn[i] = imgn[i]+(real[j]*sin(-theta*2*M_PI/(step<<1))+
                                  imgn[j]*cos(-theta*2*M_PI/(step<<1)));

                real[j] = tmpReal;
                imgn[j] = tmpImgn;
                theta ++;

            }
            old_start = start;
        }
    }
}
