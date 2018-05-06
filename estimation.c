#include "estimation.h"



alphabeta line_voltage_estimator(abc iabc, alphabeta us_alpha_beta){
    alphabeta i_alpha_beta ; 
    alphabeta ul_alpha_beta ; 
    static alphabeta old_i_alpha_beta ; 
    old_i_alpha_beta.alpha = 0 ; 
    old_i_alpha_beta.beta = 0 ; 
    
    iabc.c = -(iabc.a+ iabc.b) ; // get the last current line 
    i_alpha_beta = abc_to_alphabeta(iabc) ; // two phase reference frame 
    ul_alpha_beta.alpha = L*derivate(old_i_alpha_beta.alpha,i_alpha_beta.alpha,Ts) + us_alpha_beta.alpha ; 
    ul_alpha_beta.beta= L*derivate(old_i_alpha_beta.beta,i_alpha_beta.beta,Ts) + us_alpha_beta.beta ; 
    return ul_alpha_beta ;  
}
      

alphabeta converter_voltage_estimator(float udc, abc S){
    alphabeta us_alpha_beta ; 
    us_alpha_beta.alpha = 3/2*udc*(S.a - 0.5*(S.b + S.c)) ; 
    us_alpha_beta.beta = 1/sqrt(3)*udc*(S.b-S.c) ; 
    return us_alpha_beta ; 
    
}


float theta_estimator(alphabeta ul){
    float theta = atan2(ul.beta,ul.alpha) ; // check the parameters order 
    return theta ; 
}

float derivate(float old, float new, float step_time){
    float derivate = (new-old)/step_time ; 
    return derivate ; 
}