#include "serialData.h"

union u
{
    unsigned int i; /**< acesso a peda�o de m�m�ria de 32 bits atrav�s de tipo inteiro sem sinal. */
    float f; 
    double d ; 
    uint8_t s[4]; /**< acesso a peda�o de m�m�ria de 32 bits peda�os correspondentes a caract�res. */
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