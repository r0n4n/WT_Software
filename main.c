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

/*DPC  - written by Mariusz Malinowski*/

#include <math.h>
#include "mcc_generated_files/mcc.h"
#include <stdio.h>
#include "xc.h"
#include "pwm.h"
#include "trigo.h"
#include "serialData.h"

/*----------------------------------------------------------*/
/* Constants */
#define DT 20e-6

#define _1_sqrt3 0.57735f 
#define sqrt2 1.4142135623f
#define sqrt23 0.816496580f // sqrt(2/3)
#define _sqrt3to2 0.866025403f // sqrt(3)/2
#define _1sqrt3 0.5774f // 1/sqrt(3)

/* variables for communication with Slave DSP */
int task_id = 0; /* communication channel */
//int index = -1; /* slave DSP command index */
float deadband = 2e-6; /* deadband period */
//int  sync_mode = SLVDSP1103_PWM3_SYNC_LEFT; /* sync mode */
float exec_time, total_time; /* variables for TRACE and COCKPIT */
float period = 20e-6; /* PWM period */

/* variables for PWM rectifier */
float L=0.010;
float Kp=0.0 ; 
float Ti=0.0 ; 
float Ts=DT ; 
//float pi=PI ; 
float ia=1, ib=2, ic=3, i_alf=0, i_bet=0, psi_alf,psi_bet,psi_alf_c,psi_bet_c;
float Theta,delta_Udc,u_alf,u_bet,delta_udc_old=0.0,udc, udc_old=0.0,ualf,ubet,w;
float p,q,delta_q,delta_p,p_old=0.0,q_old=0.0,p_ref, I_ref,I_ref_old=0.0,I_ref_max=10.0;
int sector,Sa_old=0,Sb_old=0,Sc_old=0,Sq,Sq_old,Sp,Sp_old, _Ts,_T_in, D_R, D_S, D_T ;

 

float hh=0; 
float udc_ref=600.0; 
float q_ref=0.0; 
float pdc=0.1; 
float ti=0.1; 
float T_in=0.0159; 
float ku1=1435.0; 
float ki1=18.55; 
float ki2=18.55;

unsigned int tab_11[12]={1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0};
unsigned int tab_12[12]={0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0};
unsigned int tab_13[12]={1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1};
unsigned int tab_21[12]={1, 1, 0, 0, 0, 1, 0, 0, 1, 1, 1, 0};
unsigned int tab_22[12]={1, 1, 1, 0, 1, 1, 0, 0, 0, 1, 0, 0};
unsigned int tab_23[12]={0, 1, 0, 0, 1, 1, 1, 0, 1, 1, 0, 0};
unsigned int tab_31[12]={1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1};
unsigned int tab_32[12]={0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0};
unsigned int tab_33[12]={1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1};
unsigned int tab_41[12]={1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1};
unsigned int tab_42[12]={0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0};
unsigned int tab_43[12]={0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0};

uint16_t CH0;
uint16_t CH1;
uint16_t CH2;
uint16_t CH3;


float Gain_frequency = 66;  //Hardware frequency to voltage converter has a 66HZ/V output
float Gain_current = 8;     //Hardware current sensors have a 8 A/V. The measurement is signed and the 0A reference is 2.5V. 
                            //The sensors amplitude is 20A, the gain is 20A/2.5V = 8A/V
                            //FOR NOW THE MAX POSITIVE CURRENT MEASURABLE BEFORE SATURATION IS (3.3V-2.5V)*8A/V=6.4A
                            //CONVERTING THE 5V output in 3.3V output will be necessary to get 20A full scale measurement
float Gain_Vout = 28.125; 

void measure(void);
void controller(void);
//void da_converter(void);
void PWM_sync_interrupt(void);
/*----------------------------------------------------------*/
union u
{
    unsigned int i; /**< acesso a pedaço de mémória de 32 bits através de tipo inteiro sem sinal. */
    float f; 
    double d ; 
    uint8_t s[4]; /**< acesso a pedaço de mémória de 32 bits pedaços correspondentes a caractéres. */
};



/*
                         Main application
 */
void main(void)
{
    // initialize the device
    SYSTEM_Initialize();
    
      //Hardware voltage divider is designed for a 90V max voltage. The gain is 90V/3.2V = 28.125
    
    ADC1_Initialize();
    
    // When using interrupts, you need to set the Global Interrupt Enable bits
    // Use the following macros to:

    // Enable the Global Interrupts
    //INTERRUPT_GlobalEnable();

    // Disable the Global Interrupts
    //INTERRUPT_GlobalDisable();
    
    /**ALGO INIT TO MODIFIY******/
    //    ds1103_init(); /* basic initialization of DS1103 */
//    ds1103_tic_delay(2.0e-6); /* ensure 2 us settling time */
//    ds1103_dac_init(DS1103_DACMODE_LATCHED); /* init D/A converter in latched mode */
//    ds1103_slave_dsp_communication_init(); /* initialization of slave DSP communication */
//    ds1103_slave_dsp_pwm3_init(task_id, period,D_R,D_S,D_T, deadband, sync_mode); /* init and start of 3-phase PWM on DSP */
//    ds1103_slave_dsp_pwm3_start(task_id);
//    ds1103_slave_dsp_pwm3_duty_write_register(task_id, &index); /* registration of PWM duty cycle update command */
//    ds1103_set_interrupt_vector(ds1103_int_slave_DSP_PWM,(DS1103_Int_Handler_Type)&PWM_sync_interrupt,save_regs_on);
//    ds1103_enable_hardware_int(DS1103_INT_SLAVE_DSP_PWM);
//    ds1103_GLOBAL_INTERRUPT_ENABLE();
    /****************************************/
   
    while (1)
    {
       /** TO ADAPT*****/
//        master_cmd_server();
//        host_service(0, 0); 
        /*COCKPIT service */
        /***********************/
        
        // AD1CON1bits.SAMP = 1;        // start sampling ...
         //__delay32(60000000);            // for 100 mS at 31,25MHz
//         sendData(30) ; 
//         sendData(20) ; 
//        sendData(3) ; 
//        sendData(4) ;
         ia=((((float)CH0/1024)*3.3)-2.48)*Gain_current; // ia is a float but ch0 was double for test 
         ib=((((float)CH1/1024)*3.3)-2.48)*Gain_current;
         w=(((float)CH2/1024)*3.3)*Gain_frequency;
         udc=(((float)CH3/1024)*3.3)*Gain_Vout;
        sendData(ia) ; 
        sendData(ib) ;
        sendData(w) ; 
        sendData(udc) ; 

         //IO_RA2_Toggle() ; 
        // AD1CON1bits.SAMP = 0;        // start Converting
        //while (!AD1CON1bits.DONE);    // conversion done?
         //AD1CON1bits.DONE = 0;
        // while (!_AD1IF);// Wait for all 4 conversions to complete
        //_AD1IF = 0;  
    }
}



void measure(void)
{
    /* Retrieving the sensed values from A/D buffer. The values are from 0 to 1024, converting from 0V to 3.3V */
         
    CH0 = ADC1BUF0;            // yes then get ADC value
    CH1 = ADC1BUF1;            // yes then get ADC value
    CH2 = ADC1BUF2;            // yes then get ADC value
    CH3 = ADC1BUF3;            // yes then get ADC value

   /* For debuguing purpose : printing all values retrieved from the buffer */
//   printf("I_T = %d   ", CH0);
//   printf("I_S = %d   ", CH1);
//   printf("RPM = %d   ", CH2);
//   printf("Vout= %d   \n\r", CH3);
   

    /* For debuguing purpose, converting the A/D values in V to check with reality */ 
    
//    ia=(float)((CH0/1024)*3.3);
//    ib=(float)((CH1/1024)*3.3);
    /*w=(float)((CH2/1024)*3.3);
    udc=(float)((CH3/1024)*3.3);
    */

   /* The software is configured to calculated with the following pinout
      AN1 -> CH0 -> Pin5 -> I_T 
      AN0 -> CH1 -> Pin2 -> I_S
      AN2 -> CH2 -> Pin3 -> RPM
      AN3 -> CH3 -> Pin4 -> Vout
   */

//    ia=((((float)CH0/1024)*3.3)-2.48)*Gain_current; // ia is a float but ch0 was double for test 
//    ib=((((float)CH1/1024)*3.3)-2.48)*Gain_current;
//    w=(((float)CH2/1024)*3.3)*Gain_frequency;
//    udc=(((float)CH3/1024)*3.3)*Gain_Vout;

    /* Printing all the A/D results over the RS485  */
//    printf("I_T = %.3f  A ", ia);
//    printf("I_S = %.3f  A ", ib);
//    printf("RPM = %f  Hz ", w);
//    printf("Vout= %4.2f  V \n\r", udc);
    //sendData(1) ; 
    //sendData(2) ; 
    //sendData(w) ;
    //sendData(udc) ; 
    
}

void controller(void){
    ic=-(ia+ib); 
    //uc=-(ua+ub); 
    
    /*Transformations*/
    i_alf = sqrt23*(ia-0.5*ib-0.5*ic);
    i_bet = sqrt23*(_sqrt3to2)*(ib-ic);
    
    /* Flux, instantaneous active and reactive power estimator */
    /*Converter Voltage*/ 
    ualf=0.6666*udc*(Sa_old-0.5*(Sb_old+Sc_old)); 
    ubet=_1sqrt3*udc*(Sb_old- Sc_old);
    /*Converter Flux*/
    psi_alf_c += Ts*(ualf-_T_in*psi_alf_c); 
    psi_bet_c += Ts*(ubet-_T_in*psi_bet_c);
    psi_alf = psi_alf_c + i_alf*L; /* Line Flux */
    psi_bet = psi_bet_c + i_bet*L;
    /* Instantaneous power estimations*/ 
    p= 2*314*(psi_alf*i_bet - psi_bet*i_alf); 
    q= 314*(psi_alf*i_alf + psi_bet*i_bet);
    Theta=atan2(psi_bet,psi_alf);
    
    /* Sector detection */
    if ((0 <= Theta) & (Theta < pi_6)) {sector = 1;} /* 0 <= Theta < 30 */
    if ((pi_6 <= Theta) & (Theta < _1pi3)) {sector = 2;} /* 30 <= Theta < 60 */
    if ((_1pi3 <= Theta) & (Theta < pi_2)) {sector = 3;} /* 60 <= Theta < 90 */
    if ((pi_2 <= Theta) & (Theta < _2pi3)) {sector = 4;} /* 90 <= Theta < 120*/
    if ((_2pi3 <= Theta) & (Theta < _5pi_6)) {sector = 5;} /*120 <= Theta < 150*/
    if ((_5pi_6 <= Theta) & (Theta <= pi)) {sector = 6;} /*150 <= Theta < 180*/
    if ((-pi <= Theta) & (Theta < -_2pi3)) {sector = 7;} /*180 <= Theta < 210*/
    if ((-_5pi_6 <= Theta) & (Theta < -_2pi3)) {sector = 8;} /*210 <= Theta < 240*/
    if ((-_2pi3 <= Theta) & (Theta < -pi_2)) {sector = 9;} /*240 <= Theta < 270*/
    if ((-pi_2 <= Theta) & (Theta < -_1pi3)) {sector = 10;} /*270 <= Theta < 300*/
    if ((-_1pi3 <= Theta) & (Theta < -pi_6)) {sector = 11;} /*300 <= Theta < 330*/
    if ((-pi_6 <= Theta) & (Theta < 0)) {sector = 0;} /*330 <= Theta < 360*/
    
    /*Control structure*/
    delta_Udc=udc_ref-udc;
    I_ref=I_ref_old+pdc*delta_Udc+pdc*((Ts/ti)-1)*delta_udc_old;
    p_ref=I_ref*udc;
    delta_p=p_ref-p;
    
     /* p histeres */
    if (delta_p>hh) Sp = 1;
    if (delta_p<(-hh)) Sp = 0;
    if ((delta_p<hh) & (delta_p>(-hh))) Sp=Sp_old;
    /*************************************************************************/
    
    /* q histeres */
    delta_q=q_ref-q;
    if (delta_q>hh) Sq = 1; 
    if (delta_q<(-hh)) Sq = 0;
    if ((delta_q<hh) & (delta_q>(-hh))) Sq=Sq_old;
    /*************************************************************************/
    
    if((Sp==1) & (Sq==0)){D_R=tab_11[sector]; D_S=tab_12[sector]; D_T=tab_13[sector]; }
    if((Sp==1) & (Sq==1)){D_R=tab_21[sector]; D_S=tab_22[sector]; D_T=tab_23[sector]; }
    if((Sp==0) & (Sq==0)){D_R=tab_31[sector]; D_S=tab_32[sector]; D_T=tab_33[sector]; }
    if((Sp==0) & (Sq==1)){D_R=tab_41[sector]; D_S=tab_42[sector]; D_T=tab_43[sector];}
    /*Old values*/
    udc_old=udc; p_old=p; q_old=q; 
    Sp_old=Sp; Sq_old=Sq; Sa_old=D_R; Sb_old=D_S; Sc_old=D_T; I_ref_old=I_ref; delta_udc_old=delta_Udc; ;
    //break; /*END*/
}




void PWM_sync_interrupt(void) /* interrupt service routine for PWM sync interrupt */
{
    //host_service(1, 0); /* TRACE service */
    //ds1103_tic_start(); /* start time measurement */
    
    controller();
    //ds1103_slave_dsp_pwm3_duty_write(task_id, index,D_R,D_S,D_T);
    //da_converter();
    //exec_time = ds1103_tic_read();
}


//void da_converter(void)
//{
//    ds1103_dac_write(1,ia*0.1); /* output via DS1103 on-board DAC channel 1 */
//    ds1103_dac_write(2,px*0.001);
//    ds1103_dac_write(3,qx*0.001);
//    ds1103_dac_strobe();
//}

void __attribute__ ( ( interrupt, no_auto_psv ) ) _PWM1Interrupt (  )
{
	IO_RA2_Toggle() ; 
    measure();
	IFS5bits.PWM1IF = false; 
}

/**
 End of File
*/