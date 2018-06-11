/* 
 * File:   transform.h
 * Author: JAL
 *
 * Created on 2 mai 2018, 19:01
 */

#include <stdio.h>
#include <libq.h>

#include "typedef.h"
#include "math.h"

#ifndef TRANSFORM_H
#define	TRANSFORM_H
#ifdef	__cplusplus
extern "C" {
#endif

    alphabeta abc_to_alphabeta(abc abc);
    dq alphabeta_to_dq(alphabeta alphabeta, trigo_type cos_theta , trigo_type sin_theta ) ; 
    alphabeta dq_to_alphabeta(dq dq, trigo_type cos_theta , trigo_type sin_theta) ; 
    abc alphabeta_to_abc(alphabeta alphabeta);

    
#ifdef	__cplusplus
}
#endif

#endif	/* TRANSFORM_H */

