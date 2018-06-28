
#include "control.h"

void run_transformations() ; 
void run_voltage_controller() ; 
void run_id_controller() ; 
void run_iq_controller() ; 
void run_decoupling()  ; 
void inverse_transformations() ; 

signal us ; // the us signal is the control output of the controller  
signal us_sat ; // the us_sat signal is the saturated control output of the controller  
state state_vector ; // the state vector contains all the measurements and their transformations 

int omega ; // pulsation of the signal 
int omega_L ; // pulsation of the signal multiply by the estimated inductance (L)
int last_theta ; // the value of theta at the previous iteration

// Warning ! : This value is firstly the cosinus of theta but will become his inverse 
int cos_theta ;  
//Same for sinus
int sin_theta ; 
int increment ; // the increment to not estimation omega every interation of the controller


tPID voltage_controler; // the pid object for the voltage controller 

tPID id_controler; // the pid object for the id controller 
tPID id_windup_controler;  // the pid object for id anti-windup controller 

tPID iq_controler; // the pid object for the iq controller 
tPID iq_windup_controler; // the pid object for iq anti-windup controller 


/*****************  MEMORY ALLOCATION FOR THE PIDS COEFF AND THE CONTROL HISTORY *********************/
fractional abcCoefficient_voltage[3] __attribute__ ((section (".xbss, bss, xmemory")));
fractional controlHistory_voltage[3] __attribute__ ((section (".ybss, bss, ymemory")));

fractional abcCoefficient_id[3] __attribute__ ((section (".xbss, bss, xmemory")));
fractional controlHistory_id[3] __attribute__ ((section (".ybss, bss, ymemory")));

fractional abcCoefficient_iq[3] __attribute__ ((section (".xbss, bss, xmemory")));
fractional controlHistory_iq[3] __attribute__ ((section (".ybss, bss, ymemory")));

fractional abcCoef_id_anti_windup[3] __attribute__ ((section (".xbss, bss, xmemory")));
fractional controlHistory_id_anti_windup[3] __attribute__ ((section (".ybss, bss, ymemory")));

fractional abcCoef_iq_anti_windup[3] __attribute__ ((section (".xbss, bss, xmemory")));
fractional controlHistory_iq_anti_windup[3] __attribute__ ((section (".ybss, bss, ymemory")));
/***********************************************************/

/****** array of the PID gains *********/
fractional voltage_gain_coeff[3] = {0 ,0 ,0};

fractional id_gain_coeff[3] = {0 ,0 ,0};
fractional id_anti_windup_coeff[3] = {0, 0, 0} ;

fractional iq_gain_coeff[3] = {0 ,0 ,0};
fractional iq_anti_windup_coeff[3] = {0, 0, 0} ; 
/*********************************************/
     
       
     
void VOC_initialize(){
/****************** PID INITIALISATION ********************************/
        voltage_controler.abcCoefficients = &abcCoefficient_voltage[0];    /*Set up pointer to derived coefficients */
        id_controler.abcCoefficients = &abcCoefficient_id[0];    /*Set up pointer to derived coefficients */
        iq_controler.abcCoefficients = &abcCoefficient_iq[0];    /*Set up pointer to derived coefficients */
        id_windup_controler.abcCoefficients = &abcCoef_id_anti_windup[0]; 
        iq_windup_controler.abcCoefficients = &abcCoef_iq_anti_windup[0]; 
        
        voltage_controler.controlHistory = &controlHistory_voltage[0];     /*Set up pointer to controller history samples */
        id_controler.controlHistory = &controlHistory_id[0];     /*Set up pointer to controller history samples */
        iq_controler.controlHistory = &controlHistory_iq[0];     /*Set up pointer to controller history samples */
        id_windup_controler.controlHistory = &controlHistory_id_anti_windup[0];
        iq_windup_controler.controlHistory = &controlHistory_iq_anti_windup[0];
        
        /***/
        PIDInit(&voltage_controler);                          /*Clear the controler history and the controller output */
        PIDInit(&id_controler);                               /*Clear the controler history and the controller output */
        PIDInit(&id_windup_controler);                               /*Clear the controler history and the controller output */
        PIDInit(&iq_windup_controler); 
        
        /***** TUNE VOLTAGE GAIN CONTROLLERS*****/
        voltage_gain_coeff[0] = Q15(Kp_u) ; //3277 ; //Q15(-1) ;                           //Kp voltage_controler
      	voltage_gain_coeff[1] = Q15(0) ; //Q15(0) ; // Q15(Ki_u);                            //Ki voltage_controler
    	voltage_gain_coeff[2] = Q15(0) ; //Q15(0); //Q15(Kd_u);                            //Kd voltage_controler
        /***** TUNE Id GAIN CONTROLLER*****/
        id_gain_coeff[0] = Q15(Kp_id);                                //Kp id_controler
      	id_gain_coeff[1] = Q15(0);                                 //Ki id_controler
    	id_gain_coeff[2] = Q15(0);                                 //Kd id_controler
        /***** TUNE Iq GAIN CONTROLLER*****/
        iq_gain_coeff[0] = Q15(Kp_iq);                                //Kp iq_controler
      	iq_gain_coeff[1] = Q15(0);                                 //Ki iq_controler
    	iq_gain_coeff[2] = Q15(0);                                 //Kd iq_controler
        /***** TUNE ID ANTI_WINDUP GAIN CONTROLLER*****/ 
        id_anti_windup_coeff[0] = Q15(0) ; 
        id_anti_windup_coeff[0] = Q15(Ki_id) ;
        id_anti_windup_coeff[0] = Q15(0) ;
        /***** TUNE IQ ANTI_WINDUP GAIN CONTROLLER*****/ 
        iq_anti_windup_coeff[0] = Q15(0) ; 
        iq_anti_windup_coeff[0] = Q15(Ki_iq) ;
        iq_anti_windup_coeff[0] = Q15(0) ;
        
        /**SET THE 3 PID COEFF**** */
        PIDCoeffCalc(&voltage_gain_coeff[0], &voltage_controler);             /*Derive the a,b, & c coefficients from the Kp, Ki & Kd */
        PIDCoeffCalc(&id_gain_coeff[0], &id_controler);             /*Derive the a,b, & c coefficients from the Kp, Ki & Kd */
        PIDCoeffCalc(&iq_gain_coeff[0], &iq_controler);             /*Derive the a,b, & c coefficients from the Kp, Ki & Kd */
        PIDCoeffCalc(&id_anti_windup_coeff[0], &id_windup_controler); 
        PIDCoeffCalc(&iq_anti_windup_coeff[0], &iq_windup_controler); 
/****************************************************************************/
        
/******************** SET THE INITIAL REFERENCES***************************/
        voltage_controler.controlReference = UDC_REF ; 
        iq_controler.controlReference = 0;
        increment = 0 ; 
        us.dq.q = 0 ; 
        us.dq.d = 0 ; 
/**************************************************************************/

}

/* The VOC_controller function performs the VOC algorithm. See "Voltage Oriented 
 * Control of Three?Phase Boost PWM Converters" paper from Sylvain LECHAT SANJUAN. 
 */
void VOC_controller(){
   RA2_SetHigh() ;
   
   run_transformations() ;  
   run_voltage_controller() ; 
   run_id_controller() ; 
   run_iq_controller() ; 
   run_decoupling() ; 
   reference_voltage_saturation() ; 
   inverse_transformations() ; 
      
   RA2_SetLow() ;
}

void run_transformations(){
      /**********ESTIMATION + TRANSFORMATIONS **********/
//    RA2_SetHigh() ;
    
    state_vector.ul.alphabeta = abc_to_alphabeta(state_vector.ul.abc) ;   
    state_vector.ul.theta = theta_estimator(state_vector.ul.alphabeta); 

    increment++ ; 
    if (increment==30){
        omega = omega_estimation(last_theta, state_vector.ul.theta ) ;
        last_theta = state_vector.ul.theta ;
        increment = 0 ; 
    }

/******************************/
    cos_theta = _Q15cosPI(state_vector.ul.theta) ; 
    sin_theta = _Q15sinPI(state_vector.ul.theta) ;
    
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

    state_vector.ul.dq = alphabeta_to_dq(state_vector.ul.alphabeta, cos_theta, sin_theta); // 4 µs
    state_vector.il.abc.a = -(state_vector.il.abc.c + state_vector.il.abc.b) ; // get the last current line
    state_vector.il.alphabeta = abc_to_alphabeta(state_vector.il.abc);
    state_vector.il.dq = alphabeta_to_dq(state_vector.il.alphabeta, cos_theta, sin_theta); // 4µs 
   /****************end transformations ***********************/
}

void run_voltage_controller() {
    /***************VOLTAGE CONTROLER *********/
    voltage_controler.measuredOutput = state_vector.vout; // 200 ns
    PID (&voltage_controler); // 1.5µs
   /**********************************************/
}


void run_id_controller() {
    /*************id LOOP ******************/
    id_controler.controlReference = voltage_controler.controlOutput; // ~0 µs
    id_controler.measuredOutput = state_vector.il.dq.d; // 34µs
    PID (&id_controler); // 2 µs

    
    id_windup_controler.controlReference = id_controler.controlHistory[0] ; 
    id_windup_controler.measuredOutput = (us_sat.dq.d - us.dq.d)*Ks_ID_ANTI_WINDUP ; 
    PID (&id_windup_controler); // 2 µs
    /*************************************/
}

void run_iq_controller() {
    /******** iq loop************************/
    iq_controler.measuredOutput = state_vector.il.dq.q; // 
    PID (&iq_controler); // 
    
    iq_windup_controler.controlReference = iq_controler.controlHistory[0] ; 
    iq_windup_controler.measuredOutput = (us_sat.dq.q - us.dq.q)*Ks_IQ_ANTI_WINDUP ; 
    PID (&iq_windup_controler); 
    /****************************************/
}

void run_decoupling() {
/************ decoupling***************/
    omega_L = omega/L_INV ; // 130ns
    us.dq.d = (id_controler.controlOutput+id_windup_controler.controlOutput)  + state_vector.ul.dq.d + (state_vector.il.dq.q*omega_L); // 500 ns 
    us.dq.q = (iq_controler.controlOutput+iq_windup_controler.controlOutput) + state_vector.ul.dq.q - (state_vector.il.dq.d*omega_L); // 500 ns 
/************************************/
}

/**
 * This function apply a saturation on the reference volatage. See page 26 of 
 * "Voltage Oriented Control of Three?Phase Boost PWM Converters". 
 * @param state
 * @param us
 */
void reference_voltage_saturation(){
    complex us_complex ; 
    bool sat = false ; 
    us_complex.real = us.dq.d ; 
    us_complex.imag = us.dq.q ; 
    us_complex.module = module_square(us_complex) ; // !!!! here is the square of the module : d²+q² and not sqrt(d²+q²). It's to avoid to calculate the sqrt
    us_complex.angle = get_complex_angle(us_complex) ; 
    int vout_by_two = state_vector.vout/2 ; 
    long int vout_by_two_square = ((long int)state_vector.vout*(long int)state_vector.vout)/4 ; // (Vdc/2)²

    /*****************************/
    
    if (us_complex.module>vout_by_two_square) {
        us_complex.module =  vout_by_two ; 
        sat = true ; 
    }
    else if ( us_complex.module<(-vout_by_two_square)) {
        us_complex.module =  -vout_by_two ;
        sat = true ;  
    }
    else 
        sat = false ; 
    /***********************/
    
    if (sat) { // if there is saturation 
        complex_real_imag(&us_complex) ; 
        us_sat.dq.d  = us_complex.real ; 
        us_sat.dq.q = us_complex.imag ; 
    }
    else {
        us_sat.dq.d  = us.dq.d ; 
        us_sat.dq.q = us.dq.q ; 
    }
    
//    int i = 0 ; 
}

void inverse_transformations() {
/** INVERSE TRANSFORMATION  *********/
       us_sat.alphabeta = dq_to_alphabeta(us_sat.dq, cos_theta, sin_theta); // 4.3µs
       us_sat.abc = alphabeta_to_abc(us_sat.alphabeta); // 2.6 µs 
  /********************************************/
}

