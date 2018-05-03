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
#include "typedef.h"
#include <dsp.h>

/*
                         Main application
 */


    tPID voltage_controler;
    tPID id_controler;
    tPID iq_controler;
    fractional abcCoefficient_voltage[3] __attribute__ ((section (".xbss, bss, xmemory")));
    fractional controlHistory_voltage[3] __attribute__ ((section (".ybss, bss, ymemory")));
    fractional abcCoefficient_id[3] __attribute__ ((section (".xbss, bss, xmemory")));
    fractional controlHistory_id[3] __attribute__ ((section (".ybss, bss, ymemory")));
    fractional abcCoefficient_iq[3] __attribute__ ((section (".xbss, bss, xmemory")));
    fractional controlHistory_iq[3] __attribute__ ((section (".ybss, bss, ymemory")));
    fractional voltage_gain_coeff[3] = {0 ,0 ,0};
    fractional id_gain_coeff[3] = {0 ,0 ,0};
    fractional iq_gain_coeff[3] = {0 ,0 ,0};  
    
int main(void)
{
    // initialize the device
    SYSTEM_Initialize();
    init_pwm();
    
        voltage_controler.abcCoefficients = &abcCoefficient_voltage[0];    /*Set up pointer to derived coefficients */
        id_controler.abcCoefficients = &abcCoefficient_id[0];    /*Set up pointer to derived coefficients */
        iq_controler.abcCoefficients = &abcCoefficient_iq[0];    /*Set up pointer to derived coefficients */

        voltage_controler.controlHistory = &controlHistory_voltage[0];     /*Set up pointer to controller history samples */
        id_controler.controlHistory = &controlHistory_id[0];     /*Set up pointer to controller history samples */
        iq_controler.controlHistory = &controlHistory_iq[0];     /*Set up pointer to controller history samples */
        
        PIDInit(&voltage_controler);                          /*Clear the controler history and the controller output */
        PIDInit(&id_controler);                               /*Clear the controler history and the controller output */
        PIDInit(&iq_controler);                               /*Clear the controler history and the controller output */

        voltage_gain_coeff[0] = Q15(0.7);
      	voltage_gain_coeff[1] = Q15(0.2);
    	voltage_gain_coeff[2] = Q15(0);
        id_gain_coeff[0] = Q15(0.7);
      	id_gain_coeff[1] = Q15(0.2);
    	id_gain_coeff[2] = Q15(0);
        iq_gain_coeff[0] = Q15(0.7);
      	iq_gain_coeff[1] = Q15(0.2);
    	iq_gain_coeff[2] = Q15(0);
        
        PIDCoeffCalc(&voltage_gain_coeff[0], &voltage_controler);             /*Derive the a,b, & c coefficients from the Kp, Ki & Kd */
        PIDCoeffCalc(&id_gain_coeff[0], &id_controler);             /*Derive the a,b, & c coefficients from the Kp, Ki & Kd */
        PIDCoeffCalc(&iq_gain_coeff[0], &iq_controler);             /*Derive the a,b, & c coefficients from the Kp, Ki & Kd */

        voltage_controler.controlReference = Q15(0.28);
        iq_controler.controlReference = Q15(0);

    sensor sense;
    abc s;
    // When using interrupts, you need to set the Global Interrupt Enable bits
    // Use the following macros to:

    // Enable the Global Interrupts
    //INTERRUPT_GlobalEnable();

    // Disable the Global Interrupts
    //INTERRUPT_GlobalDisable();
   
    while (1)
    {
        sense=get_sensor();
        s=state_switch();
 
        id_controler.controlReference = Q15(0.1);
        
        voltage_controler.measuredOutput = Q15(0.2);
        id_controler.measuredOutput = Q15 (0.01);
        iq_controler.measuredOutput = Q15 (0.2);
        
        PID (&voltage_controler);
        PID (&id_controler);
        PID (&iq_controler);

        
        __delay32(60000000);
        
         }

    return 1;
}
/**
 End of File
*/