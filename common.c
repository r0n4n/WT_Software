#include "common.h"

int saturation(int min, int max, int value){
    if (value>max)  return max ; 
    else if (value<min) return min ; 
    else return value ; 
}

/**
 * 
 * @param before
 * @param after
 * @param ts
 * @return 
 */
int derivate(int before, int after, int ts){
    return (after - before)*10/ts ;
}


/**
 * This function return the product of a signed integer and a fractionnal  
 * @param integer
 * @param fract
 * @return 
 */
_Q15 multi_integ_frac(int integer,  int fract){
    _Q16 x = _Q16shl(integer,16) ;
//    _Q16 y = (unsigned int)(fract<<1) ; 
    _Q16 y = _Q16reciprocalQ15( fract )/2 ; 
    _Q15 z = _Q16mpy(x,y)>>16 ; 
    return z ; 
}