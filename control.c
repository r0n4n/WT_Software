
#include "control.h"

 /* sensor declaration */
    sensor sense;
    
    /* line current declaration */
    abc il;
    alphabeta il_alphabeta;
    dq il_dq;
    dq i_ref;
    
    /* voltage declaration */
    alphabeta ul_alphabeta;
    dq ul_dq;
    float udc;
    float udc_ref;
    float err_udc;
    float omega;
    float theta;
   
    abc s; // switch state 
    /* estimated voltage */
    abc us_abc ; 
    alphabeta us_alphabeta;
    dq us_dq;

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
        
        PIDInit(&voltage_controler);                          /*Clear the controler history and the controller output */
        PIDInit(&id_controler);                               /*Clear the controler history and the controller output */
        PIDInit(&iq_controler);                               /*Clear the controler history and the controller output */

        voltage_gain_coeff[0] = 20;                           //Kp voltage_controler
      	voltage_gain_coeff[1] = 3;                            //Ki voltage_controler
    	voltage_gain_coeff[2] = 0;                            //Kd voltage_controler
        id_gain_coeff[0] = 20;                                //Kp id_controler
      	id_gain_coeff[1] = 3;                                 //Ki id_controler
    	id_gain_coeff[2] = 0;                                 //Kd id_controler
        iq_gain_coeff[0] = 20;                                //Kp iq_controler
      	iq_gain_coeff[1] = 3;                                 //Ki iq_controler
    	iq_gain_coeff[2] = 0;                                 //Kd iq_controler
        
        PIDCoeffCalc(&voltage_gain_coeff[0], &voltage_controler);             /*Derive the a,b, & c coefficients from the Kp, Ki & Kd */
        PIDCoeffCalc(&id_gain_coeff[0], &id_controler);             /*Derive the a,b, & c coefficients from the Kp, Ki & Kd */
        PIDCoeffCalc(&iq_gain_coeff[0], &iq_controler);             /*Derive the a,b, & c coefficients from the Kp, Ki & Kd */

        voltage_controler.controlReference = udc_ref;
        iq_controler.controlReference = i_ref.q;
}

void VOC_controller(){
    
        sense=get_sensor();
        
        ul_alphabeta = abc_to_alphabeta(sense.vabc) ; 
        theta = theta_estimator(ul_alphabeta);
        ul_dq = alphabeta_to_dq(ul_alphabeta, theta);
        il_alphabeta = abc_to_alphabeta(il);
        il_dq = alphabeta_to_dq(il_alphabeta, theta);
        voltage_controler.measuredOutput = sense.vout;
        PID (&voltage_controler);
        id_controler.controlReference = voltage_controler.controlOutput;
        id_controler.measuredOutput = il_dq.d;
        PID (&id_controler);
        us_dq.d = id_controler.controlOutput + ul_dq.d + il_dq.q*omega*L;
        iq_controler.measuredOutput = il_dq.q;
        PID (&iq_controler);
        us_dq.q = iq_controler.controlOutput + il_dq.d*omega*L;
        us_alphabeta = dq_to_alphabeta(us_dq, theta);
        us_abc = alphabeta_to_abc(us_alphabeta);
}