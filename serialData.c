#include "serialData.h"

union u
{
    unsigned int i; /**< acesso a pedaço de mémória de 32 bits através de tipo inteiro sem sinal. */
    float f; 
    double d ; 
    uint8_t s[4]; /**< acesso a pedaço de mémória de 32 bits pedaços correspondentes a caractéres. */
};

 union u2
{
    int i; /**< acesso a pedaço de mémória de 32 bits através de tipo inteiro sem sinal. */
    float f; 
    char s[4]; /**< acesso a pedaço de mémória de 32 bits pedaços correspondentes a caractéres. */
};


 union u2 chariot ;
 
 

void serialInit() {
    chariot.s[0] = '\n' ; 
    chariot.s[1] = 0 ; 
    chariot.s[2] = 0 ; 
    chariot.s[3] = 0 ;
}

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

void sendVect(float *vect, int length ){
    int i ; 
    
    for(i=0;i<length;i++){
        sendData(vect[i]) ; 
    } 
    sendData(chariot.f) ; 
}