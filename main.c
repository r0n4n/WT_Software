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

#include <stdio.h>
#include <time.h>
#include <libpic30.h>
#include "mcc_generated_files/mcc.h"
#include "xc.h"
#include "pwm.h"
#include "serialData.h"
#include "typedef.h"
#include "estimation.h"
#include "transform.h"
#include "control.h"


sensor sense ; // structure which contains all the measurements 
int etat = 0 ; // variable for the state machine 

/************* VARIABLE FOR TESTS***********/
int x  ; 
int  y  ; 
int z ; 
int l ;
int p ; 
long int q ; 
clock_t last_time ; 
clock_t new_time ; 
/*******************************************/

void run(void) ; 
 
/*
                         Main application
 */ 
int main(void)
{
    // initialize the device
    SYSTEM_Initialize(); // hardware initialization 
    
    serialInit() ; // initialize the RS-485 communication 
    VOC_initialize() ; // initialize the controller 

    
    setReceiverMode() ; // put the board as a receiver 
//    setTransmitterMode() ; //  put the board as a transmitter

    while (1) // do loop 
    {
//        RA2_Toggle() ;
//        RA2_SetHigh() ;
//        RA2_SetLow() ;

        listen_RS485() ; // check if data have been received with the RS485
        send_if_required() ; // send data if required 
        
/********    TEST LOOP to improve the serial mecanism ******/
//        int i = 0 ; 
//        for (i=0;i<10;i++){
//            send_int(3) ; 
//            sendData(3.0) ; 
//            sendData(chariot.f) ;
//             __delay_us(1000) ; // wait for the end of the conversion 
//        }
/***********************************************************/

        if (etat == 1){ // if new data have been sample 
//                RA2_Toggle() ;  
            run() ;     // run the controller  
            etat = 0 ;  // set state to idle mode  
        }
    } 
    return 1;
}

/**
 * The _PWM1Interrupt routine is called each period of PWM 
 */
void __attribute__ ( ( interrupt, no_auto_psv ) ) _PWM1Interrupt (  )
{
//    RA2_Toggle() ;  
//    RA2_SetHigh() ;
//    RA2_SetHigh() ; 
    int i ; 
    for (i=0;i<6;i++){ // boucle for to sample the 6 channels
        __delay32(60) ; // wait for the end of the conversion 
        if (i==0) {
            etat =1 ; 
        }
        AD1CON1bits.SAMP = 1 ; // start sampling
        __delay32(16) ; // wait for the end of sampling 
        AD1CON1bits.SAMP = 0 ; // start conversion          
    }
//    RA2_SetLow() ;
//    RA2_SetHigh() ;
//    RA2_Toggle() ; 
	IFS5bits.PWM1IF = false;    // clear the PWM flag 
}


/**
 * The _AD1Interrupt routine is not used. 
 */
void __attribute__ ( ( __interrupt__ , auto_psv ) ) _AD1Interrupt ( void )
{
    IFS0bits.AD1IF = false; 
}


/***
 * The run function performs one step of the controller from the measurements 
 * conversion to the setting of the PWM duty cycle. 
 * 
 */
void run(void) {
//     RA2_SetLow() ;
//      RA2_Toggle() ;
    
    /********GET DATA*************/
    get_sensor(&sense); // get data from the buffers and do the conversions
    
    /**FULFILL THE STATE_VECTOR *****/
    state_vector.ul.abc = sense.vabc ;
    state_vector.il.abc = sense.iabc ;
    state_vector.vout = sense.vout ; 
    /**************************************/
    
    VOC_controller() ; // run the VOC controller
    set_duty_cycle(us_sat.abc, state_vector.vout) ; // change the duty cycle
}

/**
 End of File
*/
