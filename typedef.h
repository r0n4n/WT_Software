/* 
 * File:   typedef.h
 * Author: JAL
 *
 * Created on 2 mai 2018, 19:02
 */

#ifndef TYPEDEF_H
#define	TYPEDEF_H

#ifdef	__cplusplus
extern "C" {
#endif
    
#include <dsp.h>
#include <libq.h>
    
//#define FRACT
#define INTEG 
//#define LONGINT
  
typedef float trigo_type ;  
//typedef _Q15 trigo_type ;
    
typedef struct  {
#ifdef LONGINT 
    long int a; // R branch value 
    long int b; // S branch value 
    long int c; // T branch value 
#elif defined FRACT
    fractional a; // R branch value 
    fractional b; // S branch value 
    fractional c; // T branch value 
#elif defined INTEG 
    signed int a; // R branch value 
    signed int b; // S branch value 
    signed int c; // T branch value 
#endif
    }abc;
    
typedef struct  {
#ifdef LONGINT
    long int alpha;
    long int beta;
#elif defined FRACT 
    fractional alpha;
    fractional beta;
#elif defined INTEG
    int alpha;
    int beta;
#endif
}alphabeta;
    
    
    
typedef struct  {
#ifdef LONGINT
    long int d;
    long int q;
#elif defined FRACT 
    fractional  d;
    fractional q;
#elif defined INTEG
        int  d;
        int q;
#endif 
}dq;
    
typedef struct  {
        abc iabc ; 
        abc vabc ; 
#ifdef LONGINT
        long int rpm;
        long int vout;
#elif defined FRACT
        fractional rpm ; 
        fractional vout ; 
#elif defined INTEG
        int rpm ; 
        int vout ; 
#endif
    }sensor;

#ifdef	__cplusplus
}
#endif

#endif	/* TYPEDEF_H */

