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
#include "xc.h"
#include "pwm.h"
#include "serialData.h"
#include "typedef.h"
#include "estimation.h"
#include "transform.h"
#include <libpic30.h>
#include "control.h"

sensor sense ; 
state state_vector ; 
abc us_abc ;
signal ul_out ; 
signal il_out ; 
signal us ; 

int p ; 
int *test1 ;
 
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
 
    //setReceiverMode() ; 
    setTransmitterMode() ;

    while (1)
    {
        
        //RA2_Toggle() ; 

//        RA2_SetLow() ; 
       
       //VOC_controller(sense,&us_abc) ; 
       //set_duty_cycle(us_abc, 10000) ;

       /* Get the data */
//        char ReceivedChar;
//        if(U1STAbits.URXDA == 1)
//        {
//            //RA2_SetHigh() ;
//            __delay32(60000);
//            ReceivedChar = U1RXREG;
//            //RA2_SetLow() ; 
//            
//        }
      //send_ul_abc_to_alphabeta(state_vector ) ;
       //__delay32(100000);
//       float i ; 
//       for (i=0;i<10;i++){
//           sendData(i) ;
//       }
    
        
  
    }
    return 1;
}


void __attribute__ ( ( interrupt, no_auto_psv ) ) _PWM1Interrupt (  )
{
    //RA2_Toggle() ;  
    int i ; 
    //RA2_SetHigh() ; 
    for (i=0;i<6;i++){
        //RA2_SetHigh() ; 
        __delay32(16) ; // wait for the end of the conversion 
        AD1CON1bits.SAMP = 0 ;
        __delay32(60) ; // wait  ns
        AD1CON1bits.SAMP = 1 ; // start conversion   
    }
    //RA2_SetLow() ; 
	IFS5bits.PWM1IF = false; 
}


void __attribute__ ( ( __interrupt__ , auto_psv ) ) _AD1Interrupt ( void )
{
    
    RA2_Toggle() ;
    //RA2_SetHigh() ;
    
    get_sensor(&sense);
    state_vector.ul.abc = sense.vabc ; 
    state_vector.il.abc = sense.iabc ; 
    //state_vector.il.abc = sense.vabc ; 
     
    //VOC_controller(&state_vector,&us) ;
    //state_vector.il.dq.d = 1000 ;
    //send_measurements(state_vector ) ; 
//    send_ul_abc_to_alphabeta(state_vector ) ;
    //send_ul_alphabeta_to_dq(state_vector ) ; 
    //send_il_abc_to_alphabeta(state_vector ) ; 
    //send_il_alphabeta_to_dq( state_vector) ;
    //send_us_dq_to_alphabeta(us) ; 
    //send_us_alphabeta_to_abc(us) ; 
    
    //__delay32(600000);
//    set_duty_cycle(us_abc, 10000) ;
   // set_duty_cycle(us_abc, sense.vout) ;
    //RA2_Toggle() ;
    //RA2_SetLow() ;
    // clear the ADC interrupt flag
    IFS0bits.AD1IF = false; 
}

/**
 End of File
*/