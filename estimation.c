#include "estimation.h"




fractional Atan2CORDIC( fractional y, fractional x );

#define THETA_STEP INT_MAX // 3*100
#define PI_10 314 
#define OMEGA_GAIN (INT_MAX/PI_10) 

//alphabeta line_voltage_estimator(abc iabc, alphabeta us_alpha_beta){
//    alphabeta i_alpha_beta ; 
//    alphabeta ul_alpha_beta ; 
//    static alphabeta old_i_alpha_beta ; 
//    old_i_alpha_beta.alpha = 0 ; 
//    old_i_alpha_beta.beta = 0 ; 
//    old_i_alpha_beta.alpha = 0 ; 
//    
//    iabc.c = -(iabc.a+ iabc.b) ; // get the last current line 
//    i_alpha_beta = abc_to_alphabeta(iabc) ; // two phase reference frame 
//    ul_alpha_beta.alpha = L*derivate(old_i_alpha_beta.alpha,i_alpha_beta.alpha,Ts) + us_alpha_beta.alpha ; 
//    ul_alpha_beta.beta= L*derivate(old_i_alpha_beta.beta,i_alpha_beta.beta,Ts) + us_alpha_beta.beta ; 
//    return ul_alpha_beta ;  
//}
      

//alphabeta converter_voltage_estimator(float udc, abc S){
//    alphabeta us_alpha_beta ; 
//    us_alpha_beta.alpha = 3/2*udc*(S.a - 0.5*(S.b + S.c)) ; 
//    us_alpha_beta.beta = 1/sqrt(3)*udc*(S.b-S.c) ; 
//    return us_alpha_beta ; 
//    
//}

/* Takes 8 µs to perform the estimation 
 */
int theta_estimator(alphabeta ul){
    return Atan2CORDIC(ul.beta, ul.alpha );
}



int omega_estimation(int last, int new ){
    static int last_omega = 0  ; 
    if (last-new >THETA_STEP) {
        return last_omega ;         
    }
    else {
        last_omega = derivate(last, new, FS) ;
        return last_omega ; 
    }  
}
