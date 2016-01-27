#include "method4x2.h"

/* Четырёх-точечный метод. исправил траблы с прореживанием
 *  3Q+M!! 23.09.2015
 */
 
 
void Method4x2::init(){
    x = new double [3*Q+M];
    x_default = x;
    for(int i=0;i<3*Q+M;i++) x[i]=0.0;

    circle_size = 3*Q+M;
    circle_count = 0;
    S1 = 0.0;
    S2 = 0.0;
    S3 = 0.0;
    return;
}

void Method4x2::clear(){
    for(int i=0;i<Q*M;i++) x[i]=0.0;
    return;
}

double Method4x2::circle_get(int pos){
    return *(x_default+(pos+circle_count)%(circle_size));
}

Method4x2::out Method4x2::exec(double in){
    out ret;
    
    double c1t,c2t,c1o,c2o;
  
    x++;circle_count++;
    if(circle_count>=circle_size){
        x = x_default;
        circle_count = 0;
    }
    *x=in;

    x0t = circle_get(circle_size);
    x1t = circle_get(circle_size-Q);
    x2t = circle_get(circle_size-2*Q);
    x3t = circle_get(circle_size-3*Q);

    x0o = circle_get(4*Q);
    x1o = circle_get(3*Q);    
    x2o = circle_get(2*Q);
    x3o = circle_get(1*Q);
         
    c1t = x1t*x1t + x2t*x2t - x0t*x2t - x1t*x3t;
    c1o = x1o*x1o + x2o*x2o - x0o*x2o - x1o*x3o;

    c2t = x1t*x2t - x0t*x3t;
    c2o = x1o*x2o - x0o*x3o;

    S1 += c1t*c2t - c1o*c2o;
    S2 += c1t*c1t - c1o*c1o;
    S3 += c1t - c1o;
  
    ret.freq = acos(S1/S2)/(2*M_PI*Q);
    ret.ampl = sqrt(S3)/(sqrt(M*2)*sin(2*M_PI*Q*ret.freq));
    
    return ret;
}

Method4x2::out Method4x2::medial(double *x,int M,int Q){
    out ret;

    double c1,c2;
    long double S1,S2,S3;
    double abs_sin;

    S1 = 0.0;
    S2 = S1;
    S3 = S1;

    for(int m=3*Q+M; m>0; m--){
        c1 = x[m-Q]*x[m-Q] + x[m-2*Q]*x[m-2*Q] - x[m]*x[m-2*Q] - x[m-Q]*x[m-3*Q];
        c2 = x[m-Q]*x[m-2*Q] - x[m]*x[m-3*Q];

        S1 += c1*c2;
        S2 += c1*c1;
        S3 += c1;
    }

    ret.freq = acos(S1/S2)/(2*M_PI*Q);
    abs_sin = sin(2*M_PI*ret.freq*Q);
    if(abs_sin<0) abs_sin = -abs_sin;
    ret.ampl = sqrt(S3)/(sqrt(2*M)*abs_sin);

    return ret;
}

/* EOF */
