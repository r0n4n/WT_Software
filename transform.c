
#include "transform.h"


#define ONE_BY_THREE 333 // 1/3 *1000  
#define ONE_BY_SQRT_THREE 577 // 1/srqt(3) * 1000
#define ONE_BY_SQRT_SIX 408 // 1/srqt(6) * 1000
#define ONE_BY_SQRT_TWO 707 // 1/srqt(2) * 1000
#define SQRT_TWO_BY_TRHEE 816 // sqrt(2/3) * 1000 

/* Formula taken from https://en.wikipedia.org/wiki/Direct-quadrature-zero_transformation */


/*Clarke transformation
 * Take 40 탎 to perform the tranformation with long int type 
 * Take 3.2 탎 to perform the transformation with fractional type 
 */
alphabeta abc_to_alphabeta(abc abc) {
    alphabeta alphabeta;
    
    alphabeta.alpha = (2*abc.a - abc.b - abc.c)*ONE_BY_SQRT_SIX ;
    alphabeta.beta = (abc.b - abc.c)*ONE_BY_SQRT_TWO;
    alphabeta.alpha /= 1000 ;
    alphabeta.beta /=1000 ;
    return alphabeta; // THE VALUES ARE *1 000 
}

/*Takes 60 탎 */
dq alphabeta_to_dq(alphabeta alphabeta, float theta){
    dq dq;
//    printf("theta=%f   \n\r", theta); 
//    printf("theta=%f   \n\r", theta); 
    int cos_theta = (int)cosf(theta)*1000 ; 
    int sin_theta = (int)sinf(theta)*1000 ; 
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



alphabeta dq_to_alphabeta(dq dq, float theta){
    alphabeta alphabeta;
    
    int cos_theta = (int)(cosf(theta)*1000) ; 
    int sin_theta = (int)(sinf(theta)*1000) ; 
    
    alphabeta.alpha = cos_theta*dq.d - sin_theta*dq.q;
    alphabeta.beta = sin_theta*dq.d + cos_theta*dq.q;
    return alphabeta;
}

alphabeta dq_to_alphabeta2(dq dq, trigo_type cos_theta , trigo_type sin_theta ){
    alphabeta alphabeta;
     
    alphabeta.alpha = cos_theta*dq.d - sin_theta*dq.q;
    alphabeta.beta = sin_theta*dq.d + cos_theta*dq.q;
    return alphabeta;
}

abc alphabeta_to_abc(alphabeta alphabeta){    
    abc abc;
    
    abc.a = SQRT_TWO_BY_TRHEE*alphabeta.alpha;
    abc.b = abc.a - ONE_BY_SQRT_SIX*alphabeta.alpha+ONE_BY_SQRT_TWO*alphabeta.beta;
    abc.c = abc.b - ONE_BY_SQRT_TWO*alphabeta.beta;
    abc.a/=1000 ; 
    abc.b/=1000 ; 
    abc.c/=1000 ; 
    
    return abc;
}
