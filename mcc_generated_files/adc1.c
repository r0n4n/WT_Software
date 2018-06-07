
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


#define GAIN_VIN 16 // GAIN_VIN = 3.3/4096*20.3125*1000 = 16.3651
#define GAIN_VOUT  22     // GAIN_VOUT = 3.3/4096*28.125*1000 = 22.659
#define GAIN_I_IN  6 // GAIN_I_IN = 3.3/4096*8*1000 = 6,4453125
#define OFFSET_I_IN 12500 //offset current = 1.65*10*1000 = 16500000
#define OFFSET_V_IN 33515 //offset input voltage = 1.65*20.3125*1000000 = 33515625
#define ADC_GAIN 10 

signed long AN0;
signed long AN1;
signed long AN2;
signed long AN3;
signed long AN4;
signed long AN5;

long AN0_unit;
long AN1_unit;
long AN2_unit;
long AN3_unit;
long AN4_unit;
long AN5_unit;





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
    AD1CON2bits.SMPI=0b00101; //ADC interrupt is generated at the completion of every 6th sample/conversion operation
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
    AD1CON1bits.SAMP = 1 ; // start sampling
    
    // Enabling ADC1 interrupt.
   IEC0bits.AD1IE = 1;
   
    __delay32(16) ; // wait 400 ns
    
    //    //float Gain_frequency = 66;  //Hardware frequency to voltage converter has a 66HZ/V output
//    float Gain_current = 8;     //Hardware current sensors have a 8 A/V. The measurement is signed and the 0A reference is 2.5V. 
//                                //The sensors amplitude is 20A, the gain is 20A/2.5V = 8A/V
//                                //FOR NOW THE MAX POSITIVE CURRENT MEASURABLE BEFORE SATURATION IS (3.3V-2.5V)*8A/V=6.4A
//                                //CONVERTING THE 5V output in 3.3V output will be necessary to get 20A full scale measurement
//    float Gain_Vout = 28.125;   //Hardware voltage divider is designed for a 90V max voltage. The gain is 90V/3.2V = 28.125
//    float Gain_vin= 20.3125; // set gain value
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
void get_sensor(sensor *sensor){
    
        
    /* Retrieving the sensed values from A/D buffer. The values are from 0 to 1024, converting from 0V to 3.3V */

    //RA2_SetHigh() ;
//    AN0 = (signed long)ADC1BUF0;            // yes then get ADC value
//    AN1 = (signed long)ADC1BUF1;            // yes then get ADC value
//    AN2 = (signed long)ADC1BUF2;            // yes then get ADC value
//    AN3 = (signed long)ADC1BUF3;            // yes then get ADC value
//    AN4 = (signed long)ADC1BUF4;   
//    AN5 = (signed long)ADC1BUF5; 
//         
         
    /* For debuguing purpose : printing all values retrieved from the buffer */
//    printf("AN0=%dl   ", ADC1BUF0);
//   //  __delay32(1000) ; // wait for the end of the conversion 
//    printf("AN1=%dl   ", ADC1BUF1);
//     //__delay32(1000) ; // wait for the end of the conversion 
//    printf("AN2=%dl   ", ADC1BUF2);
//    // __delay32(1000) ; // wait for the end of the conversion 
//    printf("AN3=%dl   ", ADC1BUF3);
//    // __delay32(1000) ; // wait for the end of the conversion 
//    printf("AN4=%dl   ", ADC1BUF4);
//    // __delay32(1000) ; // wait for the end of the conversion 
//    printf("AN5=%dl   \n\r", ADC1BUF5);
     //__delay32(1000) ; // wait for the end of the conversion 
    /******************************************/
//    long int i=0 ; 
//    printf("i=%ld   ", i);
//    printf("i=%ld   ", i+1);
//    printf("i=%ld   ", i+2);
//    printf("i=%ld   ", i+3);
//    printf("i=%ld   ", i+4);
//    printf("i=%ld  \n\r", i+5);
    
    /* SEND DATA TO SIMULINK*/
//    sendData(AN0) ; 
//    sendData(AN1) ;
//    sendData(AN2) ;
//    sendData(AN3) ;
//    sendData(AN4) ;
//    sendData(AN5) ;
//    __delay_ms(1000);
    /***************/
    
    /****PERFOORM THE CONVERSION ****/
       
//         AN0_unit=((((float)AN0/4096)*3.3)-2.48)*Gain_current; // ia 
//         AN1_unit=((((float)AN1/4096)*3.3)-2.48)*Gain_current; // ib 
//         AN2_unit=(((float)AN2/4096)*3.3)*Gain_Vout; // vout
//         AN3_unit=(((float)AN3/4096)*3.3)*Gain_vin;
//         AN4_unit=(((float)AN4/4096)*3.3)*Gain_vin;
//         AN5_unit=(((float)AN5/4096)*3.3)*Gain_vin;
         //AN2_unit=(((float)AN2/4096)*3.3)*Gain_frequency; // frequency
//         AN0_unit=(long int)ADC1BUF0 *6445-1984000; // ia 
//         AN1_unit=(long int)ADC1BUF1*6445-1984000; // ib 
//         AN2_unit=(long int)ADC1BUF2*22659; // vout
//         AN3_unit=(long int)ADC1BUF3*16365-33515625;
//         AN4_unit=(long int)ADC1BUF4*16365-33515625;
//         AN5_unit=(long int)ADC1BUF5*16365-33515625;
//         
//         AN0_unit=ADC1BUF0*GAIN_I_IN-OFFSET_I_IN; // ia 
//         AN1_unit=ADC1BUF1*GAIN_I_IN-OFFSET_I_IN; // ib 
//         AN2_unit=ADC1BUF2*GAIN_VOUT; // vout
//         AN3_unit=ADC1BUF3*GAIN_VIN; // va 
//         AN4_unit=ADC1BUF4*GAIN_VIN; // vb 
//         AN5_unit=ADC1BUF5*GAIN_VIN; // vc 
         
         /* ALL THE INPUT ARE *1000*/
//    int test = -10000 ; 
         sensor->vabc.a=(int)(ADC1BUF0*GAIN_VIN)/ADC_GAIN; //-OFFSET_V_IN; // va
         sensor->vabc.b=(int)(ADC1BUF1*GAIN_VIN)/ADC_GAIN; //-OFFSET_V_IN; // vb
         sensor->vabc.c=(int)(ADC1BUF2*GAIN_VIN)/ADC_GAIN ; //-OFFSET_V_IN; // vc 
         //sensor->vabc.c= test/1000 ; //-OFFSET_V_IN; // vc 
         sensor->iabc.a=(int)(ADC1BUF3*GAIN_I_IN)/ADC_GAIN ; //-OFFSET_I_IN; // ia 
         sensor->iabc.b=(int)(ADC1BUF4*GAIN_I_IN)/ADC_GAIN; //-OFFSET_I_IN; // ib 
         sensor->vout=(int)(ADC1BUF5*GAIN_VOUT); // vout
          
//         float vect[5] ;
//        vect[0] = (float)(sensor->vabc.a) ; 
//        vect[1] = (float)(sensor->vabc.a) ; 
//        vect[2] = (float)(sensor->vabc.a) ; 
///        vect[3] =(float)(sensor->vabc.a) ; 
//        vect[4] =  (float)(sensor->vabc.a); 
// 
//        sendVect(vect, 5 ) ; 
         //sensor.rpm=AN2_unit;
//         sendData((float)sensor->vabc.a) ; 
//         sendData((float)sensor->iabc.a) ; 
         //sendData((float)ADC1BUF0) ; 
         //float i = 0 ; 
//         for (i=0;i<10; i++){
//             sendData(i) ; 
//         }
         //printf("sum=%ld   ", sensor->vabc.c + sensor->vabc.b + sensor->vabc.a);
         
         
         
         //RA2_SetLow() ;
         
       
    /* Printing all the A/D results over the RS485  */
//    printf("AN0=%ld   ", AN0_unit/1000);
//    printf("AN1=%ld   ", AN1_unit/1000);
//    printf("AN2=%ld   ", AN2_unit/1000);
//    printf("AN3=%ld   ", AN3_unit/1000);
//    printf("AN4=%ld   ", AN4_unit/1000);
//    printf("AN5=%ld   \n\r", AN5_unit/1000);
    /***************************************************/   
    
    /* Printing all the A/D results over the RS485  */
//    printf("va=%ld   ", sensor->vabc.a/1000);
//    printf("vb=%ld   ", sensor->vabc.b/1000);
//    printf("vc=%ld   ",sensor->vabc.c/1000);
//    printf("ia=%ld   ", sensor->iabc.a/1000);
//    printf("ib=%ld   ", sensor->iabc.b/1000);
//    printf("vout=%ld   \n\r",sensor->vout/1000);
    /***************************************************/  
}


/**
  End of File
*/
