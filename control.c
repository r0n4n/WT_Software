
#include "control.h"

    float err_udc;
    int omega ; 
    int omega_L ;
    int last_theta ; 
    int cos_theta ; 
    int sin_theta ; 
    int last_va ;
    int increment ; 

   
    tPID voltage_controler;
    tPID id_controler;
    tPID iq_controler;
    
    fractional abcCoefficient_voltage[3] __attribute__ ((section (".xbss, bss, xmemory")));
    fractional controlHistory_voltage[3] __attribute__ ((section (".ybss, bss, ymemory")));
    
    fractional abcCoefficient_id[3] __attribute__ ((section (".xbss, bss, xmemory")));
    fractional controlHistory_id[3] __attribute__ ((section (".ybss, bss, ymemory")));
    
    fractional abcCoefficient_iq[3] __attribute__ ((section (".xbss, bss, xmemory")));
    fractional controlHistory_iq[3] __attribute__ ((section (".ybss, bss, ymemory")));
    
    fractional voltage_gain_coeff[3] = {0 ,0 ,0};
    fractional id_gain_coeff[3] = {0 ,0 ,0};
    fractional iq_gain_coeff[3] = {0 ,0 ,0};
     
      
     
void VOC_initialize(int *id){
    /* PID INITIALISATION */
        voltage_controler.abcCoefficients = &abcCoefficient_voltage[0];    /*Set up pointer to derived coefficients */
        id_controler.abcCoefficients = &abcCoefficient_id[0];    /*Set up pointer to derived coefficients */
        iq_controler.abcCoefficients = &abcCoefficient_iq[0];    /*Set up pointer to derived coefficients */

        voltage_controler.controlHistory = &controlHistory_voltage[0];     /*Set up pointer to controller history samples */
        id_controler.controlHistory = &controlHistory_id[0];     /*Set up pointer to controller history samples */
        iq_controler.controlHistory = &controlHistory_iq[0];     /*Set up pointer to controller history samples */
        
        /***/
        PIDInit(&voltage_controler);                          /*Clear the controler history and the controller output */
        PIDInit(&id_controler);                               /*Clear the controler history and the controller output */
        PIDInit(&iq_controler);                               /*Clear the controler history and the controller output */
        /***** TUNE VOLTAGE GAIN CONTROLLER*****/
        voltage_gain_coeff[0] = Q15(Kp_u) ; //3277 ; //Q15(-1) ;                           //Kp voltage_controler
      	voltage_gain_coeff[1] = Q15(0) ; //Q15(0) ; // Q15(Ki_u);                            //Ki voltage_controler
    	voltage_gain_coeff[2] = Q15(0) ; //Q15(0); //Q15(Kd_u);                            //Kd voltage_controler
        /***** TUNE Id GAIN CONTROLLER*****/
        id_gain_coeff[0] = Q15(Kp_id);                                //Kp id_controler
      	id_gain_coeff[1] = Q15(0);                                 //Ki id_controler
    	id_gain_coeff[2] = Q15(0);                                 //Kd id_controler
        /***** TUNE Iq GAIN CONTROLLER*****/
        iq_gain_coeff[0] = Q15(Kp_iq);                                //Kp iq_controler
      	iq_gain_coeff[1] = Q15(Ki_iq);                                 //Ki iq_controler
    	iq_gain_coeff[2] = Q15(Kd_iq);                                 //Kd iq_controler
        
        /**SET THE 3 PID COEFF**** */
        PIDCoeffCalc(&voltage_gain_coeff[0], &voltage_controler);             /*Derive the a,b, & c coefficients from the Kp, Ki & Kd */
        PIDCoeffCalc(&id_gain_coeff[0], &id_controler);             /*Derive the a,b, & c coefficients from the Kp, Ki & Kd */
        PIDCoeffCalc(&iq_gain_coeff[0], &iq_controler);             /*Derive the a,b, & c coefficients from the Kp, Ki & Kd */
        /** SET THE INITIAL REFERENCES*/
        //voltage_controler.controlReference = 20 ; //Q15(UDC_REF);
        iq_controler.controlReference = 0;
        increment = 0 ; 

}

void VOC_controller(state *state, signal *us){
   RA2_SetHigh() ;

    /**********ESTIMATION + TRANSFORMATIONS **********/
//    RA2_SetHigh() ;
    state->ul.alphabeta = abc_to_alphabeta(state->ul.abc) ; // 3 탎 (int)  
     
    state->ul.theta = theta_estimator(state->ul.alphabeta); // time change with the value of alpha and beta

    //state->ul.theta = generate_theta() ; 
    //omega = derivate(last_theta, (int)theta, FS) ; 
    
    increment++ ; 
    if (increment==2){
       //omega = state->ul.theta  - last_theta ;  
        omega = omega_estimation(last_theta, state->ul.theta ) ;
        last_theta = state->ul.theta ;
        increment = 0 ; 
    }

/******************************/
    cos_theta = _Q15cosPI(state->ul.theta)/10 ; 
    sin_theta = _Q15sinPI(state->ul.theta)/10 ;
    
    if (cos_theta!=0){
        cos_theta = INT_MAX/(cos_theta) ; 
    }
    else cos_theta = INT_MAX ; 
    if (sin_theta!=0){
        sin_theta = INT_MAX/(sin_theta) ; 
    }
    else 
        sin_theta = INT_MAX ; 
/*****************************/

    state->ul.dq = alphabeta_to_dq(state->ul.alphabeta, cos_theta, sin_theta); // 4 탎
//
    state->il.abc.c = -(state->il.abc.a + state->il.abc.b) ; // get the last current line
    state->il.alphabeta = abc_to_alphabeta(state->il.abc);
    state->il.dq = alphabeta_to_dq(state->il.alphabeta, cos_theta, sin_theta); // 4탎 
////    /****************end transformations ***********************/
         
       // RA2_SetHigh();
       

        /****************CONTROL ****************/
       
       /***************VOLTAGE CONTROLER *********/
//        voltage_controler.measuredOutput = state->vout; // 200 ns
//        PID (&voltage_controler); // 1.5탎
       /**********************************************/  
        
        /*************id LOOP ******************/
////        id_controler.controlReference = voltage_controler.controlOutput; // ~0 탎
        id_controler.controlReference = 4000; // 
        id_controler.measuredOutput = state->il.dq.d; // 34탎
//                id_controler.measuredOutput = 0; // 34탎
        PID (&id_controler); // 2 탎 
//        /*************************************/
        
        /******** iq loop************************/
        iq_controler.measuredOutput = state->il.dq.q; //  
        PID (&iq_controler); //  
        /****************************************/
        
        /************ decoupling***************/
//        omega_L = omega*L ; // 130ns
        omega_L = 94 ;
       us->dq.d = id_controler.controlOutput + state->ul.dq.d + (state->il.dq.q*omega_L)/10; // 500 ns 
       us->dq.q = iq_controler.controlOutput + state->ul.dq.q - (state->il.dq.d*omega_L)/10; // 500 ns 
        /************************************/
//        us->dq.d = 3000 ; 
//        us->dq.q = 0 ; 
        /***** INVERSE TRANSFORMATION  *********/
        us->alphabeta = dq_to_alphabeta(us->dq, cos_theta, sin_theta); // 4.3탎
       us->abc = alphabeta_to_abc(us->alphabeta); // 2.6 탎 
        /********************************************/
        
        RA2_SetLow() ;
}




