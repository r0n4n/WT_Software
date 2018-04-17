/*
 * File:   pwm.c
 * Author: Jean
 *
 * Created on 27 juillet 2016, 15:52
 */


//shitty initialisation test

#include "xc.h"
#include "pwm.h"

void init_pwm(void) {
    
unsigned long pwm_frequ;
float pwm_period;
unsigned int ipwm_period;
    pwm_frequ = 182000;
    pwm_period = (1.0e9/(1.04*pwm_frequ));
    ipwm_period=(unsigned int)pwm_period;
    
    
    
    PTCON = 0; //Disable PWM for setting
    PTCON2 = 0; //Prescaler 1:1 PWM will use Tosc
    
    SEVTCMP = 0 ;
    
    PTPER = 200 ; //Define master time base register
    
    FCLCON1 = 0x0003; //Disabling Faults PWM1
    FCLCON2 = 0x0003; //Disabling Faults PWM2
    
    IOCON1 = 0; //RAZ Before setting
    IOCON1bits.PENH = 1; //PWM1H pin is enabled 
    IOCON1bits.PENL = 1; //PWM1L pin is enabled
    IOCON1bits.POLH = 0; //PWM1H is active low
    IOCON1bits.PMOD = 0; //Complementary pwm mode
    
    IOCON2 = 0; //RAZ Before setting
    IOCON2bits.PENH = 1; //PWM1H pin is enabled 
    IOCON2bits.PENL = 1; //PWM1L pin is enabled
    IOCON2bits.POLH = 0; //PWM1H is active low
    IOCON2bits.PMOD = 0; //Complementary pwm mode
    
    PWMCON1bits.ITB = 0; //PWM use PTPER as period time reference
    PWMCON1bits.MDCS = 0; //PWM use PDC1 and SDC1 for duty cycle setting 
    PWMCON1bits.DTC = 0; //PWM use positive deadtime for all output setted in DTR1
    PWMCON1bits.IUE = 0; //Uptades to the active PDC1 are synchronized to the pwm time base
    
    PWMCON2bits.ITB = 0; //PWM use PTPER as period time reference
    PWMCON2bits.MDCS = 0; //PWM use PDC1 and SDC1 for duty cycle setting 
    PWMCON2bits.DTC = 0; //PWM use positive deadtime for all output setted in DTR1
    PWMCON2bits.IUE = 0; //Uptades to the active PDC1 are synchronized to the pwm time base
    
    PDC1 = 100 ; //Duty cycle of 50%
    PDC2 = 100 ;
    PHASE1 = 0 ; //No phase shift
    PHASE2 = 0 ;
    DTR1 = 20 ; //more or less 100ns deadtime
    DTR2 = 5 ;
    ALTDTR2 = 5 ;
    ALTDTR1 = 20 ; //same
    
}
