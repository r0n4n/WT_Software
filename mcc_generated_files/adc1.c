
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

#define FCY 30401250UL

#include <xc.h>
#include <stdio.h>
#include "adc1.h"
#include <libpic30.h>


//#define VREF 3.3 
//#define _12BIT_MAX 4096 
//#define GAIN_VIN 16 // GAIN_VIN = 3.3/4096*20.3125*1000 = 16.3651
#define GAIN_VIN 24 // GAIN_VIN =  0.8/993*37*1000 = 29.8087

#define GAIN_VOUT  22     // GAIN_VOUT = 3.3/4096*28.125*1000 = 22.659
#define GAIN_I_IN  6 // GAIN_I_IN = 3.3/4096*8*1000 = 6,4453125
#define OFFSET_I_IN 12500 //offset current = 1.65*10*1000 = 16500000

#define OFFSET_V_IN 1193 
 
#define ADC_GAIN 10

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

/**
  Section: Driver Interface
*/

void ADC1_Initialize (void)
{   
     
    AD1CON1bits.ADON=0; //ADC IS OFF DURING INITIALIZATION
    AD1CON1bits.AD12B=1; //ADC IS IN 1 CHANNEL 12BITS MODE
    AD1CON1bits.FORM=1; //ADC CONVERSION OUTPUT IS A SIGNED INTEGER
    AD1CON1bits.ASAM=1; //SAMPLING MODE MANUEL
    AD1CON1bits.SSRCG=0; // MANUAL SAMPLE  MANUAL CONVERSION
    AD1CON1bits.SSRC=0;  // MANUAL SAMPLE  MANUAL CONVERSION
    
    AD1CON2bits.VCFG=0; //ADC IS USING AVDD AND AVSS AS VOLTAGE REFERENCE
    AD1CON2bits.CSCNA=1; //Scans inputs for CH0+ during Sample A bit      
    AD1CON2bits.CHPS =0;  //Converts CH0
    AD1CON2bits.SMPI=5; //ADC interrupt is generated at the completion of every 6th sample/conversion operation
    AD1CON2bits.BUFM=0; //Always starts filling the buffer from the Start address
    AD1CON2bits.ALTS=0; //Always uses channel input selects for Sample MUXA
    
    AD1CON3bits.ADRC=1; // Clock derived from system clock
    AD1CON3bits.SAMC=3 ;//Auto-sample time 4TAD   MINIMAL IS 3TAD
    AD1CON3bits.ADCS=4 ;////Clock derived from system clock 10*Tcy=TAD  DEPENDS ON CLOCK !!
         
            
    AD1CON4bits.ADDMAEN=0; //Conversion results stored in ADCxBUF0 through ADCxBUFF registers; DMA is not used
    AD1CHS0bits.CH0NB=0; //Negative Input Select for Sample MUXB bits =  Channel 0 negative input is VREFL
    AD1CHS0bits.CH0NA=0; //Negative Input Select for Sample MUXA bits =  Channel 0 negative input is VREFL
    
    AD1CSSH=0;            //None of the AO outputs are scanned
    AD1CSSLbits.CSS0=1;   //AN0 is scanned
    AD1CSSLbits.CSS1=1;   //AN1 is scanned
    AD1CSSLbits.CSS2=1;   //AN2 is scanned
    AD1CSSLbits.CSS3=1;   //AN3 is scanned
    AD1CSSLbits.CSS4=1;   //AN4 is scanned
    AD1CSSLbits.CSS5=1;   //AN5 is scanned
    
    AD1CON1bits.ADON=1;   //START ADC
    AD1CON1bits.SAMP = 1 ; // start sampling
    
    // Enabling ADC1 interrupt.
   IEC0bits.AD1IE = 1;
   
    __delay32(16) ; // wait 400 ns
    
}

/*
 * AN0 -> va
 * AN1 -> vb 
 * AN2 -> vc 
 * AN3 -> ic 
 * AN4 -> ib 
 * AN5 -> vout
 */
void get_sensor(sensor *sensor){
         
    /* Retrieving the sensed values from A/D buffer. The values are from -2048 to +2048, converting from 0V to 3.3V */
    /*The values of the buffer are signed 12bits*/
         /* ALL THE INPUT ARE *100 */
         sensor->vabc.a=(int)((ADC1BUF0-OFFSET_V_IN)*GAIN_VIN)/ADC_GAIN; // va
         sensor->vabc.b=(int)((ADC1BUF1-OFFSET_V_IN)*GAIN_VIN)/ADC_GAIN; // vb
         sensor->vabc.c=(int)((ADC1BUF2-OFFSET_V_IN)*GAIN_VIN)/ADC_GAIN ;// vc 
//          sensor->vabc.a=(int)(ADC1BUF0); // va
//         sensor->vabc.b=(int)(ADC1BUF1); // vb
//         sensor->vabc.c=(int)(ADC1BUF2) ;// vc 
         sensor->iabc.c=(int)(ADC1BUF3*GAIN_I_IN)/ADC_GAIN ; // ic 
         sensor->iabc.b=(int)(ADC1BUF4*GAIN_I_IN)/ADC_GAIN; // ib 
         sensor->vout=(int)(ADC1BUF5+MAX_SIGNED_12BITS)*GAIN_VOUT/ADC_GAIN; // (vout have to be < PWM_PERIOD. The set duty cycle function) 

}


/**
  End of File
*/
