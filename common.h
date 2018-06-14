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

int saturation(int min, int max, int value) ; 
int derivate(int before, int after, int ts) ; 
_Q15 multi_integ_frac(int integer,  int fract) ;

#ifdef	__cplusplus
}
#endif

#endif	/* COMMON_H */

