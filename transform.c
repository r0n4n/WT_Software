
#include "transform.h"
#include "math.h"
#include <stdio.h>
#define ONE_BY_THREE 333 // 1/3 *1000  
#define ONE_BY_SQRT_THREE 577 // 1/srqt(3) * 1000
#define ONE_BY_SQRT_SIX 408 // 1/srqt(6) * 1000
#define ONE_BY_SQRT_TWO 707 // 1/srqt(2) * 1000
/* Formula taken from https://en.wikipedia.org/wiki/Direct-quadrature-zero_transformation */

alphabeta abc_to_alphabeta(abc abc) {
    alphabeta alphabeta;
    alphabeta.alpha = (2*abc.a - abc.b - abc.c)*ONE_BY_SQRT_SIX ;
    alphabeta.beta = (abc.b - abc.c)*ONE_BY_SQRT_TWO;
    alphabeta.alpha /= 1000 ;
    alphabeta.beta /=1000 ;
    return alphabeta; // THE VALUES ARE *1 000 
}
dq alphabeta_to_dq(alphabeta alphabeta, float theta){
    dq dq;
//    printf("theta=%f   \n\r", theta); 
//    printf("theta=%f   \n\r", theta); 
    long int cos_theta = (long int)(cosf(theta)*1000) ; 
    long int sin_theta = (long int)(sinf(theta)*1000) ; 
//    printf("cos theta=%ld   ", cos_theta);
//    printf("sin_theta=%ld   \n\r", sin_theta);
    dq.d = cos_theta*alphabeta.alpha + sin_theta*alphabeta.beta;
    dq.q = cos_theta*alphabeta.beta - sin_theta*alphabeta.alpha;
    dq.d/=1000 ; 
    dq.q/=1000 ; 
//    printf("d=%ld   ",dq.d );
//    printf("q=%ld   \n\r",dq.q );
    return dq;
    
}
alphabeta dq_to_alphabeta(dq dq, float theta){
    alphabeta alphabeta;
    alphabeta.alpha = cos(theta)*dq.d - sin(theta)*dq.q;
    alphabeta.beta = sin(theta)*dq.d + cos(theta)*dq.q;
    return alphabeta;
}

abc alphabeta_to_abc(alphabeta alphabeta){
    
    //abc.a=alphabeta.alpha;
    //abc.b=-((alphabeta.alpha)/2)+(sqrt(3)/2)*alphabeta.beta;
    //abc.c=-((alphabeta.alpha)/2)-(sqrt(3)/2*alphabeta.beta;
    
    abc abc;
    
    abc.a = (sqrt(2/3))*alphabeta.alpha;
    abc.b = abc.a - (1/sqrt(6))*alphabeta.alpha+(1/sqrt(2))*alphabeta.beta;
    abc.c = abc.b - (1/sqrt(2))*alphabeta.beta;
    
    return abc;
}
