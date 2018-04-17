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

#include "mcc_generated_files/mcc.h"
#include <stdio.h>
#include "xc.h"
#include "pwm.h"

/*
                         Main application
 */
void main(void)
{
    // initialize the device
    SYSTEM_Initialize();
    
    uint16_t CH0;
    uint16_t CH1;
    uint16_t CH2;
    uint16_t CH3;
    /*float CH0_volts;
    float CH1_volts;
    float CH2_volts;
    float CH3_volts;*/
    ADC1_Initialize();
    init_pwm();
    
    PTCONbits.PTEN = 1;
    
    // When using interrupts, you need to set the Global Interrupt Enable bits
    // Use the following macros to:

    // Enable the Global Interrupts
    //INTERRUPT_GlobalEnable();

    // Disable the Global Interrupts
    //INTERRUPT_GlobalDisable();
   
    while (1)
    {

        // AD1CON1bits.SAMP = 1;        // start sampling ...
//         __delay32(60000000);            // for 100 mS at 31,25MHz
        // AD1CON1bits.SAMP = 0;        // start Converting
        //while (!AD1CON1bits.DONE);    // conversion done?
         //AD1CON1bits.DONE = 0;
        // while (!_AD1IF);// Wait for all 4 conversions to complete
        //_AD1IF = 0;
//         CH0 = ADC1BUF0;            // yes then get ADC value
//         CH1 = ADC1BUF1;            // yes then get ADC value
//         CH2 = ADC1BUF2;            // yes then get ADC value
//         CH3 = ADC1BUF3;            // yes then get ADC value
         
         /*printf("ADC1BUF0=%d  ", ADC1BUF0);
         printf("ADC1BUF1=%d  ", ADC1BUF1);
         printf("ADC1BUF2=%d  ", ADC1BUF2);
         printf("ADC1BUF3=%d  ", ADC1BUF3);
         printf("ADC1BUF4=%d  ", ADC1BUF4);
         printf("ADC1BUF5=%d  ", ADC1BUF5);
         printf("ADC1BUF6=%d  ", ADC1BUF6);
         printf("ADC1BUF7=%d  ", ADC1BUF7);
         printf("ADC1BUF8=%d  ", ADC1BUF8);
         printf("ADC1BUF9=%d  ", ADC1BUF9);
         printf("ADC1BUFA=%d  ", ADC1BUFA);
         printf("ADC1BUFB=%d  ", ADC1BUFB);
         printf("ADC1BUFC=%d  ", ADC1BUFC);
         printf("ADC1BUFD=%d  ", ADC1BUFD);
         printf("ADC1BUFE=%d  ", ADC1BUFE);
         printf("ADC1BUFF=%d  \n\n\r", ADC1BUFF);*/
       
//            printf("CH0= %d   ", CH0);
//            printf("CH1= %d   ", CH1);
//            printf("CH2= %d   ", CH2);
//            printf("CH3= %d   \n\r", CH3);
    }
}
/**
 End of File
*/