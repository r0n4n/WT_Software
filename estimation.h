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

float theta_estimator(alphabeta ul);
alphabeta voltage_estimator(abc iabc) ; 

#ifdef	__cplusplus
}
#endif

#endif	/* ESTIMATION_H */

