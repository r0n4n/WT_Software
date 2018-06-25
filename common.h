/* 
 * File:   common.h
 * Author: rblan
 *
 * Created on 5 juin 2018, 16:48
 */

#ifndef COMMON_H
#define	COMMON_H

#ifdef	__cplusplus
extern "C" {
#endif
    
#include <dsp.h>
#include <libq.h>
#include <LIMITS.H>
#include "typedef.h"
    
    
fractional Atan2CORDIC( fractional y, fractional x );

int saturation(int min, int max, int value) ; 
int derivate(int before, int after, int ts) ; 
_Q15 multi_integ_frac(int integer,  int fract) ;
int module_square(complex complex) ;
int get_complex_angle(complex complex) ; 
void complex_real_imag(complex *complex) ; 
int inverse_trigo(int trigo) ; 

#ifdef	__cplusplus
}
#endif

#endif	/* COMMON_H */

