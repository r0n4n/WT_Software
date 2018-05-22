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

#include "typedef.h"
#include <math.h>
#include "transform.h"
#include "parameters.h"
#include <errno.h> /* for errno */
#include <dsp.h>

float theta_estimator(alphabeta ul);
alphabeta line_voltage_estimator(abc iabc, alphabeta us_alpha_beta  ) ; 
alphabeta converter_voltage_estimator(float udc, abc S) ; 
float derivate(float old, float new, float step_time) ; 

#ifdef	__cplusplus
}
#endif

#endif	/* ESTIMATION_H */

