/* 
 * File:   parameters.h
 * Author: rblan
 *
 * Created on 3 mai 2018, 17:54
 */

#ifndef PARAMETERS_H
#define	PARAMETERS_H

#ifdef	__cplusplus
extern "C" {
#endif


#define L 1 //0.0001f // line inductance 
    
#define Kp_u 0.1
#define Ki_u 0  //0.1 
#define Kd_u 0
    
#define Kp_id 1
#define Ki_id 0 
#define Kd_id 0
    
#define Kp_iq 1
#define Ki_iq 0 
#define Kd_iq 0
    

#define Ts 0.0001 
#define FS 100

#ifdef	__cplusplus
}
#endif

#endif	/* PARAMETERS_H */

