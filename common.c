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

long int module_square(complex complex){
    long int square = (long int)complex.real*(long int) complex.real + (long int)complex.imag*(long int)complex.imag ; 
    return square  ;  
}

int get_complex_angle(complex complex){
    return Atan2CORDIC(complex.imag, complex.real ) ; 
}

void complex_real_imag(complex *complex) {
    complex->real = (int)complex->module /inverse_trigo(_Q15cosPI(complex->angle)) ; 
    complex->imag = (int)complex->module /inverse_trigo(_Q15sinPI(complex->angle)) ;
}

int inverse_trigo(int trigo){
    if (trigo!=0){
        trigo = INT_MAX/(trigo) ; 
    }
    else trigo = INT_MAX ; 
    return trigo ; 
} 