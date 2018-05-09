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

typedef struct  {
        long int a; // R branch value 
        long int b; // S branch value 
        long int c; // T branch value 
    }abc;
    
typedef struct  {
        long int alpha;
        long int beta;
    }alphabeta;
    
typedef struct  {
        long int d;
        long int q;
    }dq;
    
typedef struct  {
        abc iabc ; 
        abc vabc ; 
        long int rpm;
        long int vout;
    }sensor;

#ifdef	__cplusplus
}
#endif

#endif	/* TYPEDEF_H */

