/* 
 * File:   parameters.h
 * Author: rblan
 *
 * Created on 3 mai 2018, 17:54
 */

#ifndef PARAMETERS_H
#define	PARAMETERS_H

#ifdef	__cplusplus
extern "C" {
#endif


#define L 1 //0.0001f // line inductance 
#define L_INV 10000
    
    
        
#define UDC_REF 600 // reference in volt multuply by 100  
    
#define Kp_u 0.1
#define Ki_u 0  //0.1 
#define Kd_u 0
    
#define Kp_id 0.1
#define Ki_id 0 
#define Kd_id 0
    
#define Kp_iq 0.1
#define Ki_iq 0 
#define Kd_iq 0

/*** ID ANTI_WINDUP GAIN  ****/
#define Ks_ID_ANTI_WINDUP 0
 
    
/*** IQ ANTI_WINDUP GAIN  ****/
#define Ks_IQ_ANTI_WINDUP 0

    

#define Ts 0.0001 
    
#define FS 20 // value to justify. It should be taked into account the sample frequency, the incremment for the derivation

#ifdef	__cplusplus
}
#endif

#endif	/* PARAMETERS_H */

