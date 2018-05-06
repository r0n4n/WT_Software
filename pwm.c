/*
 * File:   pwm.c
 * Author: Jean
 *
 * Created on 27 juillet 2016, 15:52
 */


//shitty initialisation test


#include "pwm.h"

void init_pwm(void) {
    
    PTCON = 0; //Disable PWM for setting
    PTCONbits.SEIEN=1; // Special Event Interrupt is enabled
    PTCONbits.SEVTPS=3; // 1:4 postscaler generates Special Event trigger at every second compare match event
    
    PTCON2 = 0; //Prescaler 1:1 PWM will use Tosc
   
    SEVTCMP = 0 ; //Special event compare at the start of the period
    PTPER = 400 ; //Define master time base register
    
    
    /*******************PWMx FAULT CURRENT-LIMIT **************/
    FCLCON1 = 0x0003; //Disabling Faults PWM1
    FCLCON2 = 0x0003; //Disabling Faults PWM2
    FCLCON3 = 0x0003; //Disabling Faults PWM3
    
    //FCLCON1 = 0x0001; //The selected Fault source forces PWMxH, PWMxL pins to FLTDAT values (cycl
    //FCLCON2 = 0x0001; //The selected Fault source forces PWMxH, PWMxL pins to FLTDAT values (cycl
    //FCLCON3 = 0x0001; //The selected Fault source forces PWMxH, PWMxL pins to FLTDAT values (cycl
    /**********************************************************/
    
    /**************** I/O CONTROL REGISTER ********************/
    /* PWM1 I/O CONTROL REGISTER */
    IOCON1 = 0; //RAZ Before setting
   // IOCON1bits.PENH = 1; //PWM1H pin is enabled 
    //IOCON1bits.PENL = 1; //PWM1L pin is enabled
    IOCON1bits.POLH = 0; //PWM1H is active low
    IOCON1bits.PMOD = 0; //Complementary pwm mode
    
    /* PWM2 I/O CONTROL REGISTER */
    IOCON2 = 0; //RAZ Before setting
    //IOCON2bits.PENH = 1; //PWM2H pin is enabled 
   //IOCON2bits.PENL = 1; //PWM2L pin is enabled
    IOCON2bits.POLH = 0; //PWM2H is active low
    IOCON2bits.PMOD = 0; //Complementary pwm mode
    
    /* PWM3 I/O CONTROL REGISTER */
    IOCON3 = 0; //RAZ Before setting
    IOCON3bits.PENH = 1; //PWM3H pin is enabled 
    IOCON3bits.PENL = 1; //PWM3L pin is enabled
    IOCON3bits.POLH = 0; //PWM3H is active low
    IOCON3bits.PMOD = 0; //Complementary pwm mode
    /*********************************************/
    
    /**********************  PWMx CONTROL REGISTER  ***************/
    /*** PWM1 CONTROL REGISTER ***/
    PWMCON1bits.ITB = 0; //PWM use PTPER as period time reference
    PWMCON1bits.MDCS = 0; //PWM use PDC1 and SDC1 for duty cycle setting 
    PWMCON1bits.DTC = 0; //PWM use positive deadtime for all output setted in DTR1
    PWMCON1bits.IUE = 0; //Uptades to the active PDC1 are synchronized to the pwm time base
    
     /*** PWM2 CONTROL REGISTER ***/
    PWMCON2bits.ITB = 0; //PWM use PTPER as period time reference
    PWMCON2bits.MDCS = 0; //PWM use PDC1 and SDC1 for duty cycle setting 
    PWMCON2bits.DTC = 0; //PWM use positive deadtime for all output setted in DTR1
    PWMCON2bits.IUE = 0; //Uptades to the active PDC1 are synchronized to the pwm time base
    
     /*** PWM3 CONTROL REGISTER ***/
    PWMCON3bits.ITB = 0; //PWM use PTPER as period time reference
    PWMCON3bits.MDCS = 0; //PWM use PDC1 and SDC1 for duty cycle setting 
    PWMCON3bits.DTC = 0; //PWM use positive deadtime for all output setted in DTR1
    PWMCON3bits.IUE = 0; //Uptades to the active PDC1 are synchronized to the pwm time base
    /****************************************************************************/
    
    /*********** PWM DUTY CYCLE ************/
    PDC1 = 200 ; //PWM1 DUTY CYCLE // Duty cycle of 50%
    PDC2 = 200 ; //PWM2 DUTY CYCLE
    PDC3 = 200 ; //PWM3 DUTY CYCLE
    /*************************************/
    
    /************ PHASE-SHIFT  ******************/
    //No phase shift
    PHASE1 = 0 ; // PWM1 PHASE-SHIFT
    PHASE2 = 0 ; // PWM2 PHASE-SHIFT
    PHASE3 = 0 ; // PWM3 PHASE-SHIFT
    /********************************************/
    
    /***************** PWM DEAD-TIME   ***********************/
    DTR1 = 5 ;// PWM1 DEAD-TIME //more or less 100ns deadtime
    DTR2 = 5 ; // PWM2 DEAD-TIME
    DTR3 = 5 ; // PWM3 DEAD-TIME
    /*******************************************************/
    
    /**************   ALTERNATE DEAD-TIME *************/
    ALTDTR1 = 5 ; // PWM1 ALTERNATE DEAD-TIME
    ALTDTR2 = 5 ;  // PWM2 ALTERNATE DEAD-TIME
    ALTDTR3 = 5 ;  // PWM3 ALTERNATE DEAD-TIME
    /***************************************************/

    
    /******* Interrupts ****/
    IFS5bits.PWM1IF = false;
    IEC5bits.PWM1IE = true;
   
    PTCONbits.PTEN = 1; // enable PWM
}



abc state_switch(void) {
    
    abc abc;
    
    abc.a=PORTBbits.RB15;
    abc.b=PORTBbits.RB13;
    abc.c=PORTBbits.RB11;
    
//    printf("switch a = %f", abc.a);
//    printf("switch b = %f", abc.b);
//    printf("switch c = %f", abc.c);
    
    return abc;
}

