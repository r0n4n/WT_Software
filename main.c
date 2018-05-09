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



 

/*
                         Main application
 */ 
int main(void)
{
    // initialize the device
    SYSTEM_Initialize();
    VOC_initialize() ; 
     
    while (1)
    {
        
  //      RA2_Toggle() ; 
//        if (_AD1IF){
//            RA2_SetHigh() ; 
//        }
//        else {
//            RA2_SetLow() ;
//        }
       //RA2_SetHigh() ; 
//        int i ; 
//    for (i=0;i<6;i++){
//       sendData(i+1) ; 
//        sendData(i+2) ; 
//        sendData(i+3) ; 
//        sendData(i+4) ; 
//        sendData(i+5) ; 
//        sendData(i+6) ; 
//        printf("Vout= %d   ", i);
//        __delay32(60000000);
//       
//   }
//        RA2_SetLow() ; 
 
    }

    return 1;
}


void __attribute__ ( ( interrupt, no_auto_psv ) ) _PWM1Interrupt (  )
{
	
   // RA2_Toggle() ; 
    //__delay32(60000);
    int i ; 
    
    for (i=0;i<6;i++){
        //RA2_SetHigh() ; 
        __delay32(16) ; // wait for the end of the conversion 
        AD1CON1bits.SAMP = 0 ;
        __delay32(60) ; // wait  ns
        AD1CON1bits.SAMP = 1 ; // start conversion 
        //while (!AD1CON1bits.DONE) ; 
        
        //AD1CON1bits.DONE = 0 ; 
        //RA2_SetLow() ; 
    }
    
	IFS5bits.PWM1IF = false; 
}


void __attribute__ ( ( __interrupt__ , auto_psv ) ) _AD1Interrupt ( void )
{
    
    //RA2_Toggle() ;
    sensor sensor ;
    get_sensor(&sensor);
    VOC_controller(sensor) ; 
    //RA2_Toggle() ;
    // clear the ADC interrupt flag
    IFS0bits.AD1IF = false;
}

/**
 End of File
*/