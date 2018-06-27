/* 
 * File:   control.h
 * Author: rblan
 *
 * Created on 3 mai 2018, 14:09
 */

#ifndef CONTROL_H
#define	CONTROL_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <LIMITS.H>
    

#include "typedef.h"
#include "parameters.h"
#include "estimation.h"
#include "transform.h"
#include "mcc_generated_files/adc1.h"
#include "common.h"
#include "test_functions.h"

    
/* sensor declaration */
//sensor sense;
    
//int var_test ;  
    
void VOC_controller(); 
void VOC_initialize() ; 
void reference_voltage_saturation() ;

    

extern bool sending ;
extern char ReceivedChar; 
extern state state_vector ; 
extern signal us ; 
extern signal us_sat ; 

extern tPID voltage_controler;
extern tPID id_controler;
extern tPID iq_controler;

extern int omega ; 
extern int cos_theta ; 
extern int sin_theta ; 
extern int last_theta ; 
    
    
   
#ifdef	__cplusplus
}
#endif

#endif	/* CONTROL_H */

