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
        float a; // R branch value 
        float b; // S branch value 
        float c; // T branch value 
    }abc;
    
typedef struct  {
        float alpha;
        float beta;
    }alphabeta;
    
typedef struct  {
        float d;
        float q;
    }dq;
    
typedef struct  {
        abc iabc ; 
        abc vabc ; 
        float rpm;
        float vout;
    }sensor;

#ifdef	__cplusplus
}
#endif

#endif	/* TYPEDEF_H */

