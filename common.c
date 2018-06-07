#include "common.h"

int saturation(int min, int max, int value){
    if (value>max)  return max ; 
    else if (value<min) return min ; 
    else return value ; 
}

int derivate(int before, int after, int fs){
    return (after - before)*fs  ;
}