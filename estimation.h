/* 
 * File:   estimation.h
 * Author: rblan
 *
 * Created on 2 mai 2018, 20:03
 */

#ifndef ESTIMATION_H
#define	ESTIMATION_H

#ifdef	__cplusplus
extern "C" {
#endif
    
#include <stdio.h>
#include <math.h>
#include <errno.h> /* for errno */
#include <dsp.h>
#include <LIMITS.H>
    
#include "common.h"
#include "parameters.h"
#include "typedef.h"

int theta_estimator(alphabeta ul);
//alphabeta line_voltage_estimator(abc iabc, alphabeta us_alpha_beta  ) ; 
//alphabeta converter_voltage_estimator(float udc, abc S) ; 
int omega_estimation(int last, int new ) ; 

#ifdef	__cplusplus
}
#endif

#endif	/* ESTIMATION_H */

