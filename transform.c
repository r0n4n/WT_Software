
#include "transform.h"


#define ONE_BY_THREE 333 // 1/3 *1000  
#define ONE_BY_SQRT_THREE 577 // 1/srqt(3) * 1000
#define ONE_BY_SQRT_SIX 41 // 1/sqrt(6) = 0.4082
#define ONE_BY_SQRT_TWO 71 // 1/sqrt(2)=  0.7071
#define SQRT_TWO_BY_TRHEE 81 // sqrt(2/3) = 0.8165 
#define SQRT_SIX 24  // sqrt(6) = 2.4495 * 10 
#define SQRT_TWO 14 // sqrt(2) = 1.4142 * 10 
#define ONE_BY_SQRT_TWO_BY_TRHEE 12 //1.2247 * 10 
 

/* Formula taken from https://en.wikipedia.org/wiki/Direct-quadrature-zero_transformation */


/*Clarke transformation
 * Take 40 µs to perform the tranformation with long int type 
 * Take 3.2 µs to perform the transformation with fractional type 
 */
/*
*   Gain = x10  
*/
alphabeta abc_to_alphabeta(abc abc) {
    alphabeta alphabeta;
    
    alphabeta.alpha = (2*abc.a - abc.b - abc.c)/SQRT_SIX ; // divide by 10 
    alphabeta.beta = (abc.b - abc.c)/SQRT_TWO;
    alphabeta.alpha *= 100 ;
    alphabeta.beta *=100 ;
    
    return alphabeta; // THE VALUES ARE *1 000 
}

/*Takes 60 µs */
/*
*   Gain = x0.1  
*/
dq alphabeta_to_dq(alphabeta alphabeta, trigo_type cos_theta , trigo_type sin_theta ){
    dq dq;
    
    dq.d = alphabeta.alpha/cos_theta + alphabeta.beta/sin_theta;
    dq.q = alphabeta.beta/cos_theta - alphabeta.alpha/sin_theta;
    
    return dq;
}


/* in = 
 * Gain = x0.1
 * out = 
 */
alphabeta dq_to_alphabeta(dq dq, trigo_type cos_theta , trigo_type sin_theta){
    alphabeta alphabeta;
//    dq.d /= 100 ; 
//    dq.q /= 100 ;
    alphabeta.alpha = dq.d/cos_theta - dq.q/sin_theta;
    alphabeta.beta = dq.d/sin_theta + dq.q/cos_theta;
    
//    alphabeta.alpha /=10 ; 
//    alphabeta.beta /= 10 ; 
    return alphabeta;
}


/*
 * Gain = x100
 */
abc alphabeta_to_abc(alphabeta alphabeta){    
    abc abc;
    alphabeta.alpha *= 100 ; 
    alphabeta.beta *= 100 ;
    
    abc.b = -alphabeta.alpha/SQRT_SIX;
    abc.c = abc.b - alphabeta.beta/SQRT_TWO;
    abc.b +=  alphabeta.beta/SQRT_TWO; 
    abc.a = alphabeta.alpha/ONE_BY_SQRT_TWO_BY_TRHEE ;  
    return abc;
}