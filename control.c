
#include "control.h"

 /* sensor declaration */
    sensor sense;
    
    /* line current declaration */
    alphabeta il_alphabeta;
    dq il_dq;
    dq i_ref;
    
    /* voltage declaration */
    alphabeta ul_alphabeta;
    dq ul_dq;
    
    float err_udc;
    float omega;
    float theta;
   
    abc s; // switch state 
    /* estimated voltage */
    abc us_abc ; 
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
        voltage_gain_coeff[0] = Kp_u;                           //Kp voltage_controler
      	voltage_gain_coeff[1] = Ki_u;                            //Ki voltage_controler
    	voltage_gain_coeff[2] = Kd_u;                            //Kd voltage_controler
        /***** TUNE Id GAIN CONTROLLER*****/
        id_gain_coeff[0] = Kp_id;                                //Kp id_controler
      	id_gain_coeff[1] = Ki_id;                                 //Ki id_controler
    	id_gain_coeff[2] = Kd_id;                                 //Kd id_controler
        /***** TUNE Iq GAIN CONTROLLER*****/
        iq_gain_coeff[0] = Kp_iq;                                //Kp iq_controler
      	iq_gain_coeff[1] = Ki_iq;                                 //Ki iq_controler
    	iq_gain_coeff[2] = Kd_iq;                                 //Kd iq_controler
        /**SET THE 3 PID COEFF**** */
        PIDCoeffCalc(&voltage_gain_coeff[0], &voltage_controler);             /*Derive the a,b, & c coefficients from the Kp, Ki & Kd */
        PIDCoeffCalc(&id_gain_coeff[0], &id_controler);             /*Derive the a,b, & c coefficients from the Kp, Ki & Kd */
        PIDCoeffCalc(&iq_gain_coeff[0], &iq_controler);             /*Derive the a,b, & c coefficients from the Kp, Ki & Kd */
        /** SET THE INITIAL REFERENCES*/
        voltage_controler.controlReference = UDC_REF;
        iq_controler.controlReference = i_ref.q;
        
        counter = 1  ;
}

void VOC_controller(sensor sense){
        

        /**********ESTIMATION + TRANSFORMATIONS **********/
        ul_alphabeta = abc_to_alphabeta(sense.vabc) ;
//        printf("ualpha=%ld   ", ul_alphabeta.alpha); 
//        printf("ubeta=%ld   \n\r", ul_alphabeta.beta); 
        theta = theta_estimator(ul_alphabeta);
        ul_dq = alphabeta_to_dq(ul_alphabeta, theta);
//        printf("ULd=%ld   \n\r", ul_dq.d/1000);
//        printf("ULq=%ld   \n\n\r", ul_dq.q/1000);
        sense.iabc.c = -(sense.iabc.a + sense.iabc.b) ; // get the last current line 
//        printf("ia=%ld   ", sense.iabc.a);
//        printf("ib=%ld   ", sense.iabc.b);
//        printf("ic=%ld   \n\r", sense.iabc.c);
        
        il_alphabeta = abc_to_alphabeta(sense.iabc);
        float theta2 = theta_estimator(il_alphabeta);
        printf("b=%ld   ", sense.vabc.b/sense.iabc.b); 
        printf("c=%ld  \n\r", sense.vabc.c/sense.iabc.c);
//        printf("ialpha=%ld   ", il_alphabeta.alpha); 
//        printf("ibeta=%ld   \n\r", il_alphabeta.beta); 
        il_dq = alphabeta_to_dq(il_alphabeta, theta);
//        printf("iLd=%ld   ",il_dq.d );
//        printf("iLq=%ld   \n\r",il_dq.q );
        
        
        
        
        /****************CONTROL ****************/
//        voltage_controler.measuredOutput = sense.vout;
//        PID (&voltage_controler);
//        id_controler.controlReference = voltage_controler.controlOutput;
//        id_controler.measuredOutput = il_dq.d;
//        PID (&id_controler);
//        us_dq.d = id_controler.controlOutput + ul_dq.d + il_dq.q*omega*L;
//        iq_controler.measuredOutput = il_dq.q;
//        PID (&iq_controler);
//        us_dq.q = iq_controler.controlOutput + il_dq.d*omega*L;
//        us_alphabeta = dq_to_alphabeta(us_dq, theta);
//        us_abc = alphabeta_to_abc(us_alphabeta);
}