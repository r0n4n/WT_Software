/* 
 * File:   serialData.h
 * Author: rblan
 *
 * Created on April 26, 2018, 5:01 PM
 */

#ifndef SERIALDATA_H
#define	SERIALDATA_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <xc.h>
#include "mcc_generated_files/mcc.h"
#include "mcc_generated_files/pin_manager.h"
#include "typedef.h"
    
void sendData(float data) ; 
void ReceiveData(float data) ; 
void serialInit() ; 
void sendVect(float *vect, int length ) ; 
void setTransmitterMode() ; 
void setReceiverMode() ;

void send_measurements(state state) ; 
void send_ul_abc_to_alphabeta(state state) ; 
void send_ul_alphabeta_to_dq(state state) ;
void send_il_abc_to_alphabeta(state state); 
void send_il_alphabeta_to_dq(state state) ; 
void send_us_dq_to_alphabeta(signal us);
void send_us_alphabeta_to_abc(signal us); 
void send_theta_cos_theta(state state, trigo_type cos_theta, trigo_type sin_theta ) ;
void send_omega(int omega, float theta) ; 
void send_id_controller(tPID id_PID) ; 
void send_iq_controller(tPID iq_PID) ;
void send_usq_decoupler_controller(state state,signal us, tPID iq_PID) ; 
void send_usd_decoupler_controller(state state,signal us, tPID id_PID) ; 

#ifdef	__cplusplus
}
#endif

#endif	/* SERIALDATA_H */

