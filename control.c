
#include "control.h"


 /* sensor declaration */
    //sensor sense;
    
    /* line current declaration */
    alphabeta il_alphabeta;
    dq il_dq;
    dq i_ref;
    
    /* voltage declaration */
    alphabeta ul_alphabeta;
    dq ul_dq;
    
    float err_udc;
    _Q15 omega ; 
    float vect[5] ; 
    trigo_type cos_theta ; 
    trigo_type sin_theta ; 
    trigo_type _Q15theta ; 
    trigo_type _Q15theta2 ;
    //float omega;
    float theta;    
   
    abc s; // switch state 
    /* estimated voltage */
     
    alphabeta us_alphabeta;
    dq us_dq; 
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
     
      
     
void VOC_initialize(){
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
        voltage_gain_coeff[0] = Q15(Kp_u);                           //Kp voltage_controler
      	voltage_gain_coeff[1] = Q15(Ki_u);                            //Ki voltage_controler
    	voltage_gain_coeff[2] = Q15(Kd_u);                            //Kd voltage_controler
        /***** TUNE Id GAIN CONTROLLER*****/
        id_gain_coeff[0] = Q15(Kp_id);                                //Kp id_controler
      	id_gain_coeff[1] = Q15(Ki_id);                                 //Ki id_controler
    	id_gain_coeff[2] = Q15(Kd_id);                                 //Kd id_controler
        /***** TUNE Iq GAIN CONTROLLER*****/
        iq_gain_coeff[0] = Q15(Kp_iq);                                //Kp iq_controler
      	iq_gain_coeff[1] = Q15(Ki_iq);                                 //Ki iq_controler
    	iq_gain_coeff[2] = Q15(Kd_iq);                                 //Kd iq_controler
        /**SET THE 3 PID COEFF**** */
        PIDCoeffCalc(&voltage_gain_coeff[0], &voltage_controler);             /*Derive the a,b, & c coefficients from the Kp, Ki & Kd */
        PIDCoeffCalc(&id_gain_coeff[0], &id_controler);             /*Derive the a,b, & c coefficients from the Kp, Ki & Kd */
        PIDCoeffCalc(&iq_gain_coeff[0], &iq_controler);             /*Derive the a,b, & c coefficients from the Kp, Ki & Kd */
        /** SET THE INITIAL REFERENCES*/
        voltage_controler.controlReference = Q15(UDC_REF);
        iq_controler.controlReference = Q15(0);
        

//        chariot.s[0] = '\n' ; 
//        chariot.s[1] = 0 ; 
//        chariot.s[2] = 0 ; 
//        chariot.s[3] = 0 ;
}

void VOC_controller(sensor sense, abc *us_abc){
        
       RA2_SetHigh() ;

        /**********ESTIMATION + TRANSFORMATIONS **********/
       ul_alphabeta = abc_to_alphabeta(sense.vabc) ; // 40 탎(long int) ; 1.5 탎 (fract) ; 3 탎 (int)
          
//        printf("ualpha=%ld   ", ul_alphabeta.alpha); 
//        printf("ubeta=%ld   \n\r", ul_alphabeta.beta); 
       theta = theta_estimator(ul_alphabeta); // 8 탎
        //_Q15theta = (trigo_type)theta ; 
//        _Q15theta  = (_Q15)(-1) ; 
//        _Q15theta2 = (_Q15)(0) ;
//         cos_theta = _Q15cos(0x3) ; 
//         sin_theta = _Q15cos(0x6) ; 
        ul_dq = alphabeta_to_dq(ul_alphabeta, theta); // 16 탎
        //ul_dq = alphabeta_to_dq2(ul_alphabeta, cos_theta , sin_theta) ; 

//        vect[0] = (float)ul_alphabeta.alpha ; 
//        vect[1] = (float)ul_alphabeta.beta ; 
//        vect[2] = theta ; 
//        vect[3] = (float)ul_dq.d; 
//        vect[4] = (float)ul_dq.q ;      
//        sendVect(vect, 5 ) ; 

//        printf("ULd=%ld   \n\r", ul_dq.d/1000);
//        printf("ULq=%ld   \n\n\r", ul_dq.q/1000);
          sense.iabc.c = -(sense.iabc.a + sense.iabc.b) ; // get the last current line // takes 400ns with long int and 200 ns with fractional
//        printf("ia=%ld   ", sense.iabc.a);
//        printf("ib=%ld   ", sense.iabc.b);
//        printf("ic=%ld   \n\r", sense.iabc.c);
        
        il_alphabeta = abc_to_alphabeta(sense.iabc);
        //float theta2 = theta_estimator(il_alphabeta);
//        printf("b=%ld   ", sense.vabc.b/sense.iabc.b); 
//        printf("c=%ld  \n\r", sense.vabc.c/sense.iabc.c);
//        printf("ialpha=%ld   ", il_alphabeta.alpha); 
//        printf("ibeta=%ld   \n\r", il_alphabeta.beta); 
        il_dq = alphabeta_to_dq(il_alphabeta, theta); 
        //il_dq = alphabeta_to_dq2(il_alphabeta, cos_theta , sin_theta) ; 
        vect[0] = (float)sense.vabc.a ; 
        vect[1] = (float)sense.vabc.b ; 
        vect[2] = (float)sense.vabc.c ; 
        vect[3] = (float)il_dq.d; 
        vect[4] = (float)il_dq.q ;      
        sendVect(vect, 5 ) ;
        
       
//        printf("iLd=%ld   ",il_dq.d );
//        printf("iLq=%ld   \n\r",il_dq.q );
        
        
//        float test = 15 ; 
//        fractional  frac =1  ; 
//        int test1 = 15 ; 
        
        //RA2_SetHigh();
       
        /****************CONTROL ****************/
//        voltage_controler.measuredOutput = sense.vout; // 34 탎
//        PID (&voltage_controler); // 2탎
//        id_controler.controlReference = voltage_controler.controlOutput; // ~0 탎
//        id_controler.measuredOutput = il_dq.d; // 34탎
//        PID (&id_controler); // 2 탎 
//        us_dq.d = id_controler.controlOutput + ul_dq.d + il_dq.q*omega*L; // 14 탎 
//        iq_controler.measuredOutput = il_dq.q; // 34탎 
//        PID (&iq_controler); // 2 탎 
//        us_dq.q = iq_controler.controlOutput + il_dq.d*omega*L; // 24 탎 
//         //us_alphabeta = dq_to_alphabeta(us_dq, theta); // 20탎(int)
//         us_alphabeta = dq_to_alphabeta2(us_dq, cos_theta , sin_theta ) ; 
//        *us_abc = alphabeta_to_abc(us_alphabeta); // 48 탎 
        RA2_SetLow() ;
}