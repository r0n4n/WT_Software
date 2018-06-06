
#include "control.h"


    signal ul ; 
    signal il ; 
    int value  ; 
    //signal us ; 
   
    
//    /* line current declaration */
//    alphabeta il_alphabeta;
//    dq il_dq;
//    dq i_ref;   
    
    /* voltage declaration */
//    alphabeta ul_alphabeta;
//    dq ul_dq;
    
    float err_udc;
    int omega ; 
    int omega_L ;
   // float vect[5] ; 
    trigo_type cos_theta ; 
    trigo_type sin_theta ; 
    trigo_type _Q15theta ; 
    trigo_type _Q15theta2 ;
    //float omega;
    float theta;    
   
    abc s; // switch state 
    /* estimated voltage */
     
//    alphabeta us_alphabeta;
//    dq us_dq; 
    double counter  ; 

    
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
        omega = 63 ;
        value = 13 ; 
        id =&value  ; 
        

//        chariot.s[0] = '\n' ; 
//        chariot.s[1] = 0 ; 
//        chariot.s[2] = 0 ; 
//        chariot.s[3] = 0 ;
        
}

void VOC_controller(state *state, signal *us){
       //RA2_SetHigh() ;
    //test = value ; 
    
    /**********ESTIMATION + TRANSFORMATIONS **********/
    
    state->ul.alphabeta = abc_to_alphabeta(state->ul.abc) ; // 40 탎(long int) ; 1.5 탎 (fract) ; 3 탎 (int)

    state->ul.theta = theta_estimator(state->ul.alphabeta); // 8 탎
        //_Q15theta = (trigo_type)theta ; 
//        _Q15theta  = (_Q15)(-1) ; 
//        _Q15theta2 = (_Q15)(0) ;
//         cos_theta = _Q15cos(0x3) ; 
//         sin_theta = _Q15cos(0x6) ; 
    state->ul.dq = alphabeta_to_dq(state->ul.alphabeta, state->ul.theta); // 16 탎
        //ul_dq = alphabeta_to_dq2(ul_alphabeta, cos_theta , sin_theta) ; 

     //  sense.iabc.c = -(sense.iabc.a + sense.iabc.b) ; // get the last current line // takes 400ns with long int and 200 ns with fractional
    state->il.abc.c = -(state->il.abc.a + state->il.abc.b) ; 
    state->il.alphabeta = abc_to_alphabeta(state->il.abc);
    state->il.dq = alphabeta_to_dq(state->il.alphabeta, state->ul.theta); // 43탎 
        //il_dq = alphabeta_to_dq2(il_alphabeta, cos_theta , sin_theta) ; 
       
       /****************end transformations ***********************/
         
        //RA2_SetHigh();
       
//        voltage_controler.controlReference = 8192 ; // Q15(0.25) ;
//        voltage_controler.measuredOutput = 0 ; // Q15(-0.25); // 34 탎
        /****************CONTROL ****************/
       
       /***************VOLTAGE CONTROLER *********/
//        voltage_controler.measuredOutput = state->vout; // 34 탎
//        PID (&voltage_controler); // 2탎
       /**********************************************/  
        
        /*************id LOOP ******************/
//        id_controler.controlReference = voltage_controler.controlOutput; // ~0 탎
        id_controler.controlReference = 1000; // ~0 탎id_controler.measuredOutput = state->il.dq.d; // 34�
        id_controler.measuredOutput = 100; // 34탎
//        id_controler.measuredOutput = state->il.dq.d; // 34탎
//        PID (&id_controler); // 2 탎 
        /*************************************/
        
        /******** iq loop************************/
        iq_controler.measuredOutput = state->il.dq.q; // 34탎 
//        PID (&iq_controler); // 2 탎 
        /****************************************/
        
        /************ decoupling***************/
        omega_L = omega*L ; 
//        us->dq.d = id_controler.controlOutput + ul.dq.d + il.dq.q*omega_L; // 14 탎 
//        us->dq.q = iq_controler.controlOutput + ul.dq.q - il.dq.d*omega_L; // 24 탎 
        /************************************/
        us->dq.d = 3000 ; 
        us->dq.q = 0 ; 
        //us->dq = dq_to_alphabeta(ul_dq, theta); 
        /***** INVERSE TRANSFORMATION  *********/
        us->alphabeta = dq_to_alphabeta(us->dq, state->ul.theta); // 20탎(int)
//         us_alphabeta = dq_to_alphabeta2(us_dq, cos_theta , sin_theta ) ; 
       // abc abc = alphabeta_to_abc(ul_alphabeta);  
        //*us_abc = abc ; 
        us->abc = alphabeta_to_abc(state->ul.alphabeta); // 48 탎 
//        us->abc = alphabeta_to_abc(us->alphabeta); // 48 탎 
        /********************************************/
//        vect[0] = (float)sense.vabc.a ; 
//        vect[1] = (float)sense.vabc.b ; 
//        vect[2] = (float)sense.vabc.c ; 
//        vect[3] = (float)ul_alphabeta.alpha; 
//        vect[4] = (float)ul_alphabeta.beta; 
//        
//        vect[0] = (float)ul.alphabeta.alpha ;
//        //vect[0] = (float)sense.vabc.a ;
//        vect[1] = (float)ul.alphabeta.beta ; 
////        vect[2] = theta ; 
//        vect[2] = cosf(theta) ; 
//        vect[3] = (float)ul.dq.d; 
//        vect[4] = (float)ul.dq.q ;  
//        
//        
//        vect[0] = (float)sense.iabc.a ; 
//        vect[1] = (float)sense.iabc.b ; 
//        vect[2] = (float)sense.iabc.c ; 
//        vect[3] = (float)il_dq.d; 
//        vect[4] = (float)il_dq.q ; 
        
        
//        vect[0] = (float)id_controler.controlOutput ; 
//        vect[1] = (float)iq_controler.controlOutput ; 
//        vect[2] = (float)il_dq.d;       
//        vect[3] = (float)il_dq.q ;
//        vect[4] = (float)sense.iabc.c ;
        
//        vect[0] = (float)id_controler.controlOutput ; 
//        vect[1] = (float)iq_controler.controlOutput ; 
//        vect[2] = (float)us_dq.d; 
//        vect[3] = (float)us_dq.q ;
//        vect[4] = (float)sense.iabc.c ;
//        
//        vect[0] = (float)us_alphabeta.alpha ; 
//        vect[1] = (float)us_alphabeta.beta ;
//        vect[2] = (float)us_dq.d; 
//        vect[3] = (float)us_dq.q ;
//        vect[4] = (float) us_abc->c ;
        
//        vect[0] = (float)us_dq.d; 
//        vect[1] = (float)us_dq.q ;
//        vect[2] = (float)(us_abc->a) ; 
//        vect[3] = (float) us_abc->b ; 
//        vect[4] = (float) us_abc->c ;
////    
//        vect[0] = (float)abc.a ; 
//        vect[1] = (float)abc.b ; 
//        vect[2] = (float)abc.c ; 
//        vect[3] = (float)(ul_alphabeta.alpha); 
//        vect[4] = (float)(ul_alphabeta.beta) ; 
//        (udc / (us_abc.a + udc/2 ))
        
//        vect[0] = (float)((abc.a + 60000/2)) ;
//        vect[1] = (float)((abc.a + 60000/2)/10) ;  
//        sendVect(vect,5) ;
        
        //RA2_SetLow() ;
}




