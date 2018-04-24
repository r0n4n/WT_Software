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
    
    double CH0_unit;
    double CH1_unit;
    double CH2_unit;
    double CH3_unit;
    
    float Gain_frequency = 66;  //Hardware frequency to voltage converter has a 66HZ/V output
    float Gain_current = 8;     //Hardware current sensors have a 8 A/V. The measurement is signed and the 0A reference is 2.5V. 
                                //The sensors amplitude is 20A, the gain is 20A/2.5V = 8A/V
                                //FOR NOW THE MAX POSITIVE CURRENT MEASURABLE BEFORE SATURATION IS (3.3V-2.5V)*8A/V=6.4A
                                //CONVERTING THE 5V output in 3.3V output will be necessary to get 20A full scale measurement
    float Gain_Vout = 28.125;   //Hardware voltage divider is designed for a 90V max voltage. The gain is 90V/3.2V = 28.125
    
    ADC1_Initialize();
    
    // init_pwm();
    
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
         __delay32(60000000);            // for 100 mS at 31,25MHz
        // AD1CON1bits.SAMP = 0;        // start Converting
        //while (!AD1CON1bits.DONE);    // conversion done?
         //AD1CON1bits.DONE = 0;
        // while (!_AD1IF);// Wait for all 4 conversions to complete
        //_AD1IF = 0;
         
         /* Retrieving the sensed values from A/D buffer. The values are from 0 to 1024, converting from 0V to 3.3V */
         
         CH0 = ADC1BUF0;            // yes then get ADC value
         CH1 = ADC1BUF1;            // yes then get ADC value
         CH2 = ADC1BUF2;            // yes then get ADC value
         CH3 = ADC1BUF3;            // yes then get ADC value
         
            /* For debuguing purpose : printing all values retrieved from the buffer */
            /*printf("I_T = %d   ", CH0);
            printf("I_S = %d   ", CH1);
            printf("RPM = %d   ", CH2);
            printf("Vout= %d   ", CH3);
            */
         
         /* 
          For debuguing purpose, converting the A/D values in V to check with reality
          * 
         CH0_unit=(float)((CH0/1024)*3.3);
         CH1_unit=(float)((CH1/1024)*3.3);
         CH2_unit=(float)((CH2/1024)*3.3);
         CH3_unit=(float)((CH3/1024)*3.3);
         */
         
         /* The software is configured to calculated with the following pinout
            AN1 -> CH0 -> Pin5 -> I_T 
            AN0 -> CH1 -> Pin2 -> I_S
            AN2 -> CH2 -> Pin3 -> RPM
            AN3 -> CH3 -> Pin4 -> Vout
          */
         
         CH0_unit=((((float)CH0/1024)*3.3)-2.48)*Gain_current;
         CH1_unit=((((float)CH1/1024)*3.3)-2.48)*Gain_current;
         CH2_unit=(((float)CH2/1024)*3.3)*Gain_frequency;
         CH3_unit=(((float)CH3/1024)*3.3)*Gain_Vout;
       
         /* Printing all the A/D results over the RS485  */
         
         printf("I_T = %.3f  A ", CH0_unit);
         printf("I_S = %.3f  A ", CH1_unit);
         printf("RPM = %.1f  Hz ", CH2_unit);
         printf("Vout= %.1f  V \n\r", CH3_unit);
         
         /*
                 
            
         */       
      
    }
}
/**
 End of File
*/