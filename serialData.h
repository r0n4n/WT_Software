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
    
void sendData(float data) ; 
void ReceiveData(float data) ; 
void serialInit() ; 
void sendVect(float *vect, int length ) ; 
void setTransmitterMode() ; 
void setReceiverMode() ; 

#ifdef	__cplusplus
}
#endif

#endif	/* SERIALDATA_H */

