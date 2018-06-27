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
    
    VOC_initialize() ; 
//    x = Q15(0.5) ; 
//    z= _Q15sqrt(x) ; 
//
//    y = _Q15norm(x) ; 
   
    
    setReceiverMode() ; 
//    PDC1 = 1 ; 
//    PDC2 = 2 ; 
//    PDC3 = 3 ;
//    setTransmitterMode() ;
//    us.dq.d = 32000 ; 
//    us.dq.q = 10 ; 
////    q = us.dq.d ; 
//    state_vector.vout = 32676 ;  
//    reference_voltage_saturation() ; 

    while (1)
    {
        
//        RA2_Toggle() ;
        
//         UART1_Write(3) ; 
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
//        int i = 0 ; 
//        for (i=0;i<10;i++){
//            send_int(3) ; 
//            sendData(3.0) ; 
//            sendData(chariot.f) ;
//             __delay_us(1000) ; // wait for the end of the conversion 

//        }
//
        if (etat == 1){
//                RA2_Toggle() ;  

            run() ;      
            etat = 0 ;
        }
    }
    return 1;
}

/*TAKE 20 µs to sample the 6 channels*/
void __attribute__ ( ( interrupt, no_auto_psv ) ) _PWM1Interrupt (  )
{
//    RA2_Toggle() ;  
//    RA2_SetHigh() ;
//    RA2_SetHigh() ; 
    int i ; 
    for (i=0;i<6;i++){
        __delay32(60) ; // wait  ns
        if (i==0) {
            etat =1 ; 
        }
        AD1CON1bits.SAMP = 1 ; // sampling start  
        __delay32(16) ; // wait for the end of the conversion 
        AD1CON1bits.SAMP = 0 ; // conversion start         
    }
//    RA2_SetLow() ;
//    RA2_SetHigh() ;
//    RA2_Toggle() ; 
	IFS5bits.PWM1IF = false;    
}


void __attribute__ ( ( __interrupt__ , auto_psv ) ) _AD1Interrupt ( void )
{
    IFS0bits.AD1IF = false; 
}



void run(void) {
//     RA2_SetLow() ;
    //RA2_Toggle() ;
    
    /********GET DATA*************/
    get_sensor(&sense);
    state_vector.ul.abc = sense.vabc ;
    state_vector.il.abc = sense.iabc ;
    state_vector.vout = sense.vout ; 
    /**************************/
//    id_controler.controlReference = 100; // ~0 µs
//    id_controler.measuredOutput = 0; // 34µs
//    PID (&id_controler); // 2 µs
    VOC_controller() ; // run the controller
    set_duty_cycle(us_sat.abc, state_vector.vout) ; // change the duty cycle

}

/**
 End of File
*/
