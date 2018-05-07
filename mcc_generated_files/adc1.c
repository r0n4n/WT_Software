
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
#include <stdio.h>
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



/**
  Section: Driver Interface
*/


void ADC1_Initialize (void)
{   
    AD1CON1bits.ADON=0; //ADC IS OFF DURING INITIALIZATION
    AD1CON1bits.AD12B=1; //ADC IS IN 1 CHANNEL 12BITS MODE
    AD1CON1bits.FORM=0; //ADC CONVERSION OUTPUT IS AN INTEGER
    AD1CON1bits.ASAM=1; //SAMPLING MODE AUTOMATIC
    AD1CON1bits.SSRCG=0; // PWM primary Special Event Trigger ends sampling and starts conversion
    AD1CON1bits.SSRC=3;  //PWM primary Special Event Trigger ends sampling and starts conversion
    
    AD1CON2bits.VCFG=0; //ADC IS USING AVDD AND AVSS AS VOLTAGE REFERENCE
    AD1CON2bits.CSCNA=1; //Scans inputs for CH0+ during Sample A bit        
    AD1CON2bits.SMPI=0b00110; //ADC interrupt is generated at the completion of every 6th sample/conversion operation
    AD1CON2bits.BUFM=0; //Always starts filling the buffer from the Start address
    AD1CON2bits.ALTS=0; //Always uses channel input selects for Sample MUXA
    
    AD1CON3bits.ADRC=1; // Clock derived from system clock
    AD1CON3bits.SAMC=3 ;//Auto-sample time 4TAD   MINIMAL IS 3TAD
    AD1CON3bits.ADCS = 4 ;////Clock derived from system clock 10*Tcy=TAD  DEPENDS ON CLOCK !!
         
            
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
    
    // Enabling ADC1 interrupt.
   IEC0bits.AD1IE = 1;

}






/*
 * AN0 -> ia 
 * AN1 -> ib 
 * AN2 -> vout 
 * AN3 -> va 
 * AN4 -> vb 
 * AN5 -> vc or AN5 -> freq 
 * 
 */
sensor get_sensor(void){
    
    sensor sensor;
    
    uint16_t AN0;
    uint16_t AN1;
    uint16_t AN2;
    uint16_t AN3;
    uint16_t AN4;
    uint16_t AN5;
    
    float AN0_unit;
    float AN1_unit;
    float AN2_unit;
    float AN3_unit;
    float AN4_unit;
    float AN5_unit;
    
    
    //float Gain_frequency = 66;  //Hardware frequency to voltage converter has a 66HZ/V output
    float Gain_current = 8;     //Hardware current sensors have a 8 A/V. The measurement is signed and the 0A reference is 2.5V. 
                                //The sensors amplitude is 20A, the gain is 20A/2.5V = 8A/V
                                //FOR NOW THE MAX POSITIVE CURRENT MEASURABLE BEFORE SATURATION IS (3.3V-2.5V)*8A/V=6.4A
                                //CONVERTING THE 5V output in 3.3V output will be necessary to get 20A full scale measurement
    float Gain_Vout = 28.125;   //Hardware voltage divider is designed for a 90V max voltage. The gain is 90V/3.2V = 28.125
    float Gain_vin= 1; // set gain value 
    
        //ADC1_Initialize();        
    
        // AD1CON1bits.SAMP = 1;        // start sampling ...
        //__delay32(60000000);            // for 100 mS at 31,25MHz
        // AD1CON1bits.SAMP = 0;        // start Converting
        //while (!AD1CON1bits.DONE);    // conversion done?
         //AD1CON1bits.DONE = 0;
        // while (!_AD1IF);// Wait for all 4 conversions to complete
        //_AD1IF = 0;
         
         /* Retrieving the sensed values from A/D buffer. The values are from 0 to 1024, converting from 0V to 3.3V */
         
         
         AN0 = ADC1BUF0;            // yes then get ADC value
         AN1 = ADC1BUF1;            // yes then get ADC value
         AN2 = ADC1BUF2;            // yes then get ADC value
         AN3 = ADC1BUF3;            // yes then get ADC value
         AN4 = ADC1BUF4;   
         AN5 = ADC1BUF5; 
         
         
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
         
         AN0_unit=((((float)AN0/4096)*3.3)-2.48)*Gain_current; // ia 
         AN1_unit=((((float)AN1/4096)*3.3)-2.48)*Gain_current; // ib 
         AN2_unit=(((float)AN2/4096)*3.3)*Gain_Vout; // vout
         AN3_unit=(((float)AN3/4096)*3.3)*Gain_vin;
         AN4_unit=(((float)AN4/4096)*3.3)*Gain_vin;
         AN5_unit=(((float)AN5/4096)*3.3)*Gain_vin;
         //AN2_unit=(((float)AN2/4096)*3.3)*Gain_frequency; // frequency
         
         
       
         /* Printing all the A/D results over the RS485  */
         

//         printf("I_T = %.3f  A ", CH0_unit);
//         printf("I_S = %.3f  A ", CH1_unit);
//         printf("RPM = %.1f  Hz ", CH2_unit);
//         printf("Vout= %.1f  V \n\r", CH3_unit);

         
         sensor.iabc.a=AN0_unit;
         sensor.iabc.b=AN1_unit;
         sensor.vout=AN2_unit;
         sensor.vabc.a=AN3_unit;
         sensor.vabc.b=AN4_unit; 
         sensor.vabc.c=AN5_unit; 
         // sensor.rpm=AN2_unit;
         return sensor;
}


/**
  End of File
*/
