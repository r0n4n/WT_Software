#include "serialData.h"

union u
{
    unsigned int i; /**< acesso a pedaço de mémória de 32 bits através de tipo inteiro sem sinal. */
    float f; 
    double d ; 
    uint8_t s[4]; /**< acesso a pedaço de mémória de 32 bits pedaços correspondentes a caractéres. */
};


void sendData(float data){
      union u number ;
      number.f = data ; 
      int i ; 
      //float x = data ; 
      for( i=0 ; i<4 ; i++){
          UART1_Write(number.s[i]) ;
      }
}

void ReceiveData(float data){
    
}