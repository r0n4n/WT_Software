#include "test_functions.h"


#define MAX_THETA 314 // 3.14 * 100 
#define MIN_THETA -314
void three_phase(abc *abc){
    
//    static float angle ;
}

int generate_theta() {
    static int theta = INT_MIN ; 
    theta += 2  ; 
    if (theta>INT_MAX){
        theta = INT_MAX ; 
    }
    return theta ; 
}