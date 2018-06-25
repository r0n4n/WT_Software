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
#include <dsp.h>
    #include "control.h"
    
    
extern bool sending ;
extern char ReceivedChar; 
extern state state_vector ; 
extern signal us ; 
    
void sendData(float data) ; 
void ReceiveData(float data) ; 
void serialInit() ; 
void sendVect(float *vect, int length ) ; 
void setTransmitterMode() ; 
void setReceiverMode() ;
void limited_counter() ; 
void listen_RS485() ;
void send_if_required() ; 

void send_measurements( ) ; //0
void send_dc_voltage() ; 
void send_ul_abc_to_alphabeta( ) ; //1
void send_omega() ;  //
void send_ul_alphabeta_to_dq( ) ;
void send_il_abc_to_alphabeta( ); 
void send_il_alphabeta_to_dq( ) ; 

void send_id_controller( ) ; 
void send_iq_controller( ) ;
void send_usq_decoupler_controller(  ) ; 
void send_usd_decoupler_controller( ) ; 

void send_us_dq_to_alphabeta( );
void send_us_alphabeta_to_abc( ); 
//void send_theta_cos_theta( state, trigo_type cos_theta, trigo_type sin_theta ) ;


#ifdef	__cplusplus
}
#endif

#endif	/* SERIALDATA_H */

