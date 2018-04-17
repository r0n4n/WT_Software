
/**
  ADC1 Generated Driver File

  @Company
    Microchip Technology Inc.

  @File Name
    adc1.c

  @Summary
    This is the generated header file for the ADC1 driver using PIC24 / dsPIC33 / PIC32MM MCUs

  @Description
    This header file provides APIs for driver for ADC1.
    Generation Information :
        Product Revision  :  PIC24 / dsPIC33 / PIC32MM MCUs - pic24-dspic-pic32mm : v1.35
        Device            :  dsPIC33EP256MC502
    The generated drivers are tested against the following:
        Compiler          :  XC16 1.31
        MPLAB 	          :  MPLAB X 3.60
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

/**
  Section: Included Files
*/

#include <xc.h>
#include "adc1.h"

/**
  Section: Data Type Definitions
*/

/* ADC Driver Hardware Instance Object

  @Summary
    Defines the object required for the maintenance of the hardware instance.

  @Description
    This defines the object required for the maintenance of the hardware
    instance. This object exists once per hardware instance of the peripheral.

 */
typedef struct
{
	uint8_t intSample;
}

ADC_OBJECT;

static ADC_OBJECT adc1_obj;

/**
  Section: Driver Interface
*/


void ADC1_Initialize (void)
{
    // ASAM enabled; ADDMABM disabled; ADSIDL disabled; DONE disabled; SIMSAM Simultaneous; FORM Absolute decimal result, unsigned, right-justified; SAMP disabled; SSRC Internal counter ends sampling and starts conversion; AD12B 10-bit; ADON enabled; SSRCG disabled; 

   AD1CON1 = 0x80EC;

    // CSCNA disabled; VCFG0 AVDD; VCFG1 AVSS; ALTS enabled; BUFM disabled; SMPI 4; CHPS 4 Channel; 

   AD1CON2 = 0x10D;

    // SAMC 31; ADRC FOSC/2; ADCS 254; 

   AD1CON3 = 0x1FFE;

    // CH0SA AN3; CH0SB AN3; CH0NB AVSS; CH0NA AVSS; 
   
   AD1CON4 =0x0100 ; 

   AD1CHS0 = 0x303;

    // CSS25 disabled; CSS24 disabled; CSS31 disabled; CSS30 disabled; 

   AD1CSSH = 0x0;

    // CSS2 disabled; CSS1 disabled; CSS0 disabled; CSS5 disabled; CSS4 disabled; CSS3 disabled; 

   AD1CSSL = 0x0;

    // CH123SA CH1=OA2/AN0,CH2=AN1,CH3=AN2; CH123SB CH1=OA2/AN0,CH2=AN1,CH3=AN2; CH123NA CH1=VREF-,CH2=VREF-,CH3=VREF-; CH123NB CH1=VREF-,CH2=VREF-,CH3=VREF-; 

   AD1CHS123 = 0x0;


   adc1_obj.intSample = AD1CON2bits.SMPI;
   
}



void ADC1_Tasks ( void )
{
    // clear the ADC interrupt flag
    IFS0bits.AD1IF = false;
}



/**
  End of File
*/
