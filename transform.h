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
#include "serialData.h"



#ifndef TRANSFORM_H
#define	TRANSFORM_H
#ifdef	__cplusplus
extern "C" {
#endif

    alphabeta abc_to_alphabeta(abc abc);
    dq alphabeta_to_dq(alphabeta alphabeta, float theta);
    dq alphabeta_to_dq2(alphabeta alphabeta, trigo_type cos_theta ,trigo_type sin_theta);
    alphabeta dq_to_alphabeta(dq dq, float theta);
    abc alphabeta_to_abc(alphabeta alphabeta);
    alphabeta dq_to_alphabeta2(dq dq, trigo_type cos_theta , trigo_type sin_theta ) ; 
    
    
#ifdef	__cplusplus
}
#endif

#endif	/* TRANSFORM_H */

