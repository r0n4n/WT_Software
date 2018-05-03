
#include "transform.h"
#include "math.h"

/* Formula taken from https://en.wikipedia.org/wiki/Direct-quadrature-zero_transformation */

alphabeta abc_to_alphabeta(abc abc) {
    //alphabeta.alpha=abc.a;
    //alphabeta.beta=(abc.a)*tan(theta);
    alphabeta alphabeta;
alphabeta.alpha = (2*abc.a - abc.b - abc.c)*(1/sqrt(6));
alphabeta.beta = (abc.b - abc.c)*(1/sqrt(2));

return alphabeta;
}
dq alphabeta_to_dq(alphabeta alphabeta, float theta){

    dq dq;
dq.d = cos(theta)*alphabeta.alpha + sin(theta)*alphabeta.beta;
dq.q = cos(theta)*alphabeta.beta - sin(theta)*alphabeta.alpha;

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
