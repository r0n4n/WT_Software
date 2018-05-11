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

#include "typedef.h"
#include "parameters.h"
#include "estimation.h"
#include <dsp.h>
#include "mcc_generated_files/adc1.h"
#include <stdio.h>
    
#define UDC_REF 20 
    
void VOC_controller(sensor sensor) ; 
void VOC_initialize() ; 
    

    
    
   
#ifdef	__cplusplus
}
#endif

#endif	/* CONTROL_H */

