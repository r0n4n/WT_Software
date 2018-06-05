
#include "transform.h"


#define ONE_BY_THREE 333 // 1/3 *1000  
#define ONE_BY_SQRT_THREE 577 // 1/srqt(3) * 1000
#define ONE_BY_SQRT_SIX 41 // 1/sqrt(6) = 0.4082
#define ONE_BY_SQRT_TWO 71 // 1/sqrt(2)=  0.7071
#define SQRT_TWO_BY_TRHEE 81 // sqrt(2/3) = 0.8165 
#define SQRT_SIX 24  // sqrt(6) = 2.4495 * 10 
#define SQRT_TWO 14 // sqrt(2) = 1.4142 * 10 
#define ONE_BY_SQRT_TWO_BY_TRHEE 1224 //1.2247
 

/* Formula taken from https://en.wikipedia.org/wiki/Direct-quadrature-zero_transformation */


/*Clarke transformation
 * Take 40 탎 to perform the tranformation with long int type 
 * Take 3.2 탎 to perform the transformation with fractional type 
 */
/*
*   Gain = x10  
*/
alphabeta abc_to_alphabeta(abc abc) {
    alphabeta alphabeta;
    
    alphabeta.alpha = (2*abc.a - abc.b - abc.c)/SQRT_SIX ; // divide by 10 
    alphabeta.beta = (abc.b - abc.c)/SQRT_TWO;
//    alphabeta.alpha = (2*abc.a - abc.b - abc.c)*ONE_BY_SQRT_SIX ;
//    alphabeta.beta = (abc.b - abc.c)*ONE_BY_SQRT_TWO;
//    alphabeta.alpha /= 1000 ;
//    alphabeta.beta /=1000 ;
    alphabeta.alpha *= 100 ;
    alphabeta.beta *=100 ;
    return alphabeta; // THE VALUES ARE *1 000 
}

/*Takes 60 탎 */
/*
*   Gain = x0.1  
*/
dq alphabeta_to_dq(alphabeta alphabeta, float theta){
    dq dq;
//    printf("theta=%f   \n\r", theta); 
//    printf("theta=%f   \n\r", theta); 
//    int cos_theta = (int)(cosf(theta)*1000) ; 
//    int sin_theta = (int)(sinf(theta)*1000) ; 
    int cos_theta = (int)(1/cosf(theta)*10) ; 
    int sin_theta = (int)(1/sinf(theta)*10) ; 
//    float cos_theta = cosf(theta) ; 
//    float sin_theta = sinf(theta) ;
//    printf("cos theta=%ld   ", cos_theta);
//    printf("sin_theta=%ld   \n\r", sin_theta);
    dq.d = alphabeta.alpha/cos_theta + alphabeta.beta/sin_theta;
    dq.q = alphabeta.beta/cos_theta - alphabeta.alpha/sin_theta;
//    dq.d = cos_theta*alphabeta.alpha + sin_theta*alphabeta.beta;
//    dq.q = cos_theta*alphabeta.beta - sin_theta*alphabeta.alpha;
//    dq.d = cos_theta*(float)alphabeta.alpha + sin_theta*(float)alphabeta.beta;
//    dq.q = cos_theta*(float)alphabeta.beta - sin_theta*(float)alphabeta.alpha;
//    dq.d/=100 ; 
//    dq.q/=100 ; 
//    printf("d=%ld   ",dq.d );
//    printf("q=%ld   \n\r",dq.q );
    return dq;
}

    /* Takes 3.8 탎 */ 
dq alphabeta_to_dq2(alphabeta alphabeta,  trigo_type cos_theta , trigo_type sin_theta ){
    dq dq;
//    printf("cos theta=%ld   ", cos_theta);
//    printf("sin_theta=%ld   \n\r", sin_theta);
    dq.d = cos_theta*alphabeta.alpha + sin_theta*alphabeta.beta;
    dq.q = cos_theta*alphabeta.beta - sin_theta*alphabeta.alpha;
//    dq.d/=1000 ; 
//    dq.q/=1000 ; 
//    printf("d=%ld   ",dq.d );
//    printf("q=%ld   \n\r",dq.q );
    return dq;
}


/* in = 
 * Gain = x0.1
 * out = 
 */
alphabeta dq_to_alphabeta(dq dq, float theta){
    alphabeta alphabeta;
//    dq.d /= 100 ; 
//    dq.q /= 100 ;
    int cos_theta = (int)(1/cosf(theta)*10) ; 
    int sin_theta = (int)(1/sinf(theta)*10) ; 
    
//    alphabeta.alpha = cos_theta*dq.d - sin_theta*dq.q;
//    alphabeta.beta = sin_theta*dq.d + cos_theta*dq.q;
    alphabeta.alpha = dq.d/cos_theta - dq.q/sin_theta;
    alphabeta.beta = dq.d/sin_theta + dq.q/cos_theta;
    
    alphabeta.alpha /=10 ; 
    alphabeta.beta /= 10 ; 
    return alphabeta;
}

alphabeta dq_to_alphabeta2(dq dq, trigo_type cos_theta , trigo_type sin_theta ){
    alphabeta alphabeta;
     
    alphabeta.alpha = cos_theta*dq.d - sin_theta*dq.q;
    alphabeta.beta = sin_theta*dq.d + cos_theta*dq.q;
    return alphabeta;
}

/*
 * Gain = x100
 */
abc alphabeta_to_abc(alphabeta alphabeta){    
    abc abc;
//    alphabeta.alpha = 10 ; 
//    alphabeta.beta = 10 ;
    
    abc.b = alphabeta.alpha*ONE_BY_SQRT_SIX;
    abc.c = abc.b - alphabeta.beta*ONE_BY_SQRT_TWO;
    abc.b +=  alphabeta.beta*ONE_BY_SQRT_TWO; 
    abc.a = alphabeta.alpha*SQRT_TWO_BY_TRHEE ; 
    
//    abc.a/=10 ; 
//    abc.b/=10 ; 
//    abc.c/=10 ; 
    
    return abc;
}
