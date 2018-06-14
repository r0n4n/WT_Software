/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using PIC24 / dsPIC33 / PIC32MM MCUs

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC24 / dsPIC33 / PIC32MM MCUs - pic24-dspic-pic32mm : v1.35
        Device            :  dsPIC33EP256MC502
    The generated drivers are tested against the following:
        Compiler          :  XC16 1.31
        MPLAB             :  MPLAB X 3.60
*/

/*
    (c) 2016 Microchip Technology Inc. and its subsidiaries. You may use this
    software and any derivatives exclusively with Microchip products.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION
    WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.

    MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE
    TERMS.
*/
#define FCY 30401250UL

#include "mcc_generated_files/mcc.h"
#include <stdio.h>
#include <time.h>
#include "xc.h"
#include "pwm.h"
#include "serialData.h"
#include "typedef.h"
#include "estimation.h"
#include "transform.h"
#include <libpic30.h>
#include "control.h"
//#include "common.h"

sensor sense ; 

abc us_abc ;
signal ul_out ; 
signal il_out ; 


//int omega ; 

int p ; 
long int q ; 
int *test1 ;
int counter = 0 ; 
int etat = 0 ; 
int x  ; 
int  y  ; 
int z ; 
int l ;




void run(void) ; 
 

clock_t last_time ; 

clock_t new_time ; 
// union u2
//{
//    int i; /**< acesso a pedaço de mémória de 32 bits através de tipo inteiro sem sinal. */
//    float f; 
//    char s[4]; /**< acesso a pedaço de mémória de 32 bits pedaços correspondentes a caractéres. */
//};
//
// union u2 chariot ;

//float vect[5] ;
//fractional Clarke[2][3] ;
/*
                         Main application
 */ 
int main(void)
{
    // initialize the device
    SYSTEM_Initialize(); // hardware initialization 
    serialInit() ; 
    
    VOC_initialize(test1) ; 
 
    setReceiverMode() ; 
//    setTransmitterMode() ;
//    x = 10 ; 
//    y = 10 ; 
    
//    x = _Q16reciprocalQ15(Q15(0.5)) ; 
//    x = 0x8000 ; 
//    z = (x & 0x8000 ) ;
//    z = z <<16 ; 
//    y = _Q16reciprocalQ15(Q15(0.5)) ; 
//    p = 1234 ; 
//    x = _Q16shl(2,16) ; 
//    y = Q15(0.5) ; 
//    z = _Q16reciprocalQ15( -16384 ); 
    while (1)
    {
        
//        RA2_Toggle() ;

//        x = -8 ;
//        y = Q15(-0.5) ;
//         RA2_SetHigh() ;
//         p = p >>2  ; 
//        z = _Q16mpy(x,y);
//         z = x*y ; 
//        z=  multi_integ_frac(x,  y) ; 
//        y = Q15(0.5) ;
//        z=  multi_integ_frac(x,  y) ; 
//        RA2_SetLow() ;
        //    PDC1 = omega ; 
        listen_RS485() ; 
        send_if_required() ; 

        if (etat == 1){
            run() ;
//            set_duty_cycle(us.abc, state_vector.vout) ;
            etat = 0 ;
        }
 

        
//        if(AD1CON1bits.DONE){
////                    RA2_SetLow() ;
//               
//        }

    }
    return 1;
}

/*TAKE 20 µs to sample the 6 channels*/
void __attribute__ ( ( interrupt, no_auto_psv ) ) _PWM1Interrupt (  )
{
//    RA2_Toggle() ;  
//    RA2_SetHigh() ;
    int i ; 
//    RA2_SetHigh() ; 

    for (i=0;i<6;i++){
        __delay32(60) ; // wait  ns
        if (i==0) {
            etat =1 ; 
        }
        AD1CON1bits.SAMP = 1 ; // sampling start  
//        __delay_us(10);// Wait for sampling time (10 us)
        __delay32(16) ; // wait for the end of the conversion 
        AD1CON1bits.SAMP = 0 ; // conversion start 
//        __delay_us(10);// Wait for sampling time (10 us)
//        while (!AD1CON1bits.DONE);
        
    }
//    RA2_SetLow() ;

    //    while (AD1CON1bits.DONE==0); 
//    AD1CON1bits.DONE = 1 ;
     
//    __delay_us(2);
//    RA2_SetLow() ;
//    RA2_SetHigh() ;


//    RA2_Toggle() ; 
//        IFS0bits.AD1IF = true; 

	IFS5bits.PWM1IF = false; 
//        run() ; 

     
}


void __attribute__ ( ( __interrupt__ , auto_psv ) ) _AD1Interrupt ( void )
{
//    RA2_Toggle() ;
//    RA2_SetHigh() ;
    //__delay_us(10);
//    set_duty_cycle(us_abc, 10000) ;
   // set_duty_cycle(us_abc, sense.vout) ;
    
//    RA2_Toggle() ;
//    RA2_SetLow() ;
    // clear the ADC interrupt flag
//    run() ; 
//    __delay32(600) ; // wait  ns
    IFS0bits.AD1IF = false; 
}



void run(void) {
//     RA2_SetLow() ;
//    RA2_Toggle() ;
    
    /********GET DATA*************/
    get_sensor(&sense);
    state_vector.ul.abc = sense.vabc ;
    state_vector.il.abc = sense.iabc ;
//    state_vector.il.abc = sense.vabc ;
//    state_vector.il.abc.a = sense.vabc.a/10 ; 
//    state_vector.il.abc.b = sense.vabc.b/10 ; 
//    state_vector.il.abc.c = sense.vabc.c/10 ; 
    state_vector.vout = 200 ;
    /**************************/
    
    VOC_controller(&state_vector,&us) ;
  
}

/**
 End of File
*/
