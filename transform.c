
#include "transform.h"
#include "math.h"

/* Formula taken from https://en.wikipedia.org/wiki/Direct-quadrature-zero_transformation */

alphabeta abc_to_alphabeta(abc abc) {
    //alphabeta.alpha=abc.a;
    //alphabeta.beta=(abc.a)*tan(theta);
    
alphabeta.alpha = (2*abc.a - abc.b - abc.c)*(1/sqrt(6));
alphabeta.beta = (abc.b - abc.c)*(1/sqrt(2));
}
dq alphabeta_to_dq(alphabeta alphabeta, float theta){

dq.d = cos(theta)*alphabeta.alpha + sin(theta)*alphabeta.beta;
dq.q = cos(theta)*alphabeta.beta - sin(theta)*alphabeta.alpha;
    
}
alphabeta dq_to_alphabeta(dq dq, float theta){

alphabeta.alpha = cos(theta)*dq.d - sin(theta)*dq.q;
alphabeta.beta = sin(theta)*dq.d + cos(theta)*dq.q;
}
abc alphabeta_to_abc(alphabeta alphabeta){
    
    //abc.a=alphabeta.alpha;
    //abc.b=-((alphabeta.alpha)/2)+(sqrt(3)/2)*alphabeta.beta;
    //abc.c=-((alphabeta.alpha)/2)-(sqrt(3)/2*alphabeta.beta;
    
    abc.a = (sqrt(2/3))*alphabeta.alpha;
    abc.b = abc.a - (1/sqrt(6))*alphabeta.alpha+(1/sqrt(2))*alphabeta.beta;
    abc.c = abc.b - (1/sqrt(2))*alphabeta.beta;
}
