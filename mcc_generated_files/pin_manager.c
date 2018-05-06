/**
  System Interrupts Generated Driver File 

  @Company:
    Microchip Technology Inc.

  @File Name:
    pin_manager.c

  @Summary:
    This is the generated manager file for the MPLAB(c) Code Configurator device.  This manager
    configures the pins direction, initial state, analog setting.
    The peripheral pin select, PPS, configuration is also handled by this manager.

  @Description:
    This source file provides implementations for MPLAB(c) Code Configurator interrupts.
    Generation Information : 
        Product Revision  :  MPLAB(c) Code Configurator - 4.26.2
        Device            :  dsPIC33EP256MC502
    The generated drivers are tested against the following:
        Compiler          :  XC16 1.31
        MPLAB             :  MPLAB X 3.60

    Copyright (c) 2013 - 2015 released Microchip Technology Inc.  All rights reserved.

    Microchip licenses to you the right to use, modify, copy and distribute
    Software only when embedded on a Microchip microcontroller or digital signal
    controller that is integrated into your product or third party product
    (pursuant to the sublicense terms in the accompanying license agreement).

    You should refer to the license agreement accompanying this Software for
    additional information regarding your rights and obligations.

    SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
    EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
    MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
    IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
    CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
    OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
    INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
    CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
    SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
    (INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.

*/


/**
    Section: Includes
*/
#include <xc.h>
#include "pin_manager.h"

/**
    void PIN_MANAGER_Initialize(void)
*/
void PIN_MANAGER_Initialize(void)
{
    /******PORT REGISTER A AND B MAP FORdsPIC33EPXXXGP/MC202/502 DEVICES ********/
    /****SEE TABLE 4-59 FOR PORTA AND TABLE 4-60 FOR PORTB IN dsPIC33EPXXXMC20X/50X DATASHEET*/
    
    /****************************************************************************
     * Setting the Output Latch SFR(s)
     ***************************************************************************/
    
    LATA = 0x0000;
    LATB = 0x0110;  //RB4 and RB8 start high

    /****************************************************************************
     * Setting the GPIO Direction SFR(s)
     ***************************************************************************/
    TRISAbits.TRISA0 = 1;   //AN0 AS input
    TRISAbits.TRISA1 = 1;   //AN1 As input
    TRISAbits.TRISA2 = 1;   
    TRISAbits.TRISA3 = 1;
    TRISAbits.TRISA4 = 1;        
    
    TRISBbits.TRISB0=1;     //AN2 as input
    TRISBbits.TRISB1=1;     //AN3 as input
    TRISBbits.TRISB2=1;     //AN4 as input
    TRISBbits.TRISB3=1;     //AN5 as input
    TRISBbits.TRISB4=0;     // RB4(DIR) AS OUTPUT
    TRISBbits.TRISB5=1;        
    TRISBbits.TRISB6=1;   
    TRISBbits.TRISB7=1;   
    TRISBbits.TRISB8=0;        // RB8 (TX) AS OUTPUT
    TRISBbits.TRISB9=1;
    TRISBbits.TRISB10=0;       // RB10 (PWM3H) AS OUTPUT
    TRISBbits.TRISB11=0;       // RB11 (PWM3L) AS OUTPUT
    TRISBbits.TRISB12=0;       // RB12 (PWM2H) AS OUTPUT
    TRISBbits.TRISB13=0;       // RB13 (PWM2L) AS OUTPUT
    TRISBbits.TRISB14=0;       // RB14 (PWM1H) AS OUTPUT
    TRISBbits.TRISB15=0;       // RB15 (PWM1L) AS OUTPUT

    // ALL THE REST ARE INPUTS 

    /****************************************************************************
     * Setting the Weak Pull Up and Weak Pull Down SFR(s)
     ***************************************************************************/
    CNPDA = 0x0000;
    CNPDB = 0x0000;
    CNPUA = 0x0000;
    CNPUB = 0x0000;

    /****************************************************************************
     * Setting the Open Drain SFR(s)
     ***************************************************************************/
    ODCA = 0x0000;
    ODCB = 0x0000;

    /****************************************************************************
     * Setting the Analog/Digital Configuration SFR(s)
     ***************************************************************************/
    ANSELA = 0x0013;    
    ANSELAbits.ANSA0 = 1;    //AN0 is analog
    ANSELAbits.ANSA1 = 1;    //AN1 is analog

    ANSELAbits.ANSA4 = 1;    //RA4 is analog

    
    
    
    ANSELB = 0x010F;    //AN2 AN3 AN4 AN5 and RB8 are analog
    ANSELBbits.ANSB0 = 1;     //AN2 is analog
    ANSELBbits.ANSB1 = 1;     //AN3 is analog
    ANSELBbits.ANSB2 = 1;     //AN4 is analog
    ANSELBbits.ANSB3 = 1;     //AN5 is analog
    ANSELBbits.ANSB8 = 1;     //RB8 is analog ??

    /****************************************************************************
     * Set the PPS
     ***************************************************************************/
    __builtin_write_OSCCONL(OSCCON & 0xbf); // unlock PPS

    RPINR18bits.U1RXR = 0x0029;   //RB9->UART1:U1RX;
    RPOR3bits.RP40R = 0x0001;   //RB8->UART1:U1TX;

    __builtin_write_OSCCONL(OSCCON | 0x40); // lock   PPS

}

