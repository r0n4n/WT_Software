/**
 * \file main.c
 * \brief Programme de tests.
 * \author Franck.H
 * \version 0.1
 * \date 11 septembre 2007
 *
 * Programme de test pour l'objet de gestion des cha�nes de caract�res Str_t.
 *
 */

#include "serialData.h"

union u
{
    unsigned int i; /**< acesso a peda�o de m�m�ria de 32 bits atrav�s de tipo inteiro sem sinal. */
    float f; 
    double d ; 
    uint8_t s[4]; /**< acesso a peda�o de m�m�ria de 32 bits peda�os correspondentes a caract�res. */
};

 union u2
{
    int i; /**< acesso a peda�o de m�m�ria de 32 bits atrav�s de tipo inteiro sem sinal. */
    float f; 
    char s[4]; /**< acesso a peda�o de m�m�ria de 32 bits peda�os correspondentes a caract�res. */
};


 union u2 chariot ;
 
 float vect[5] ;
/**
 * 
 * 
 * \fn void serialInit()
 * \brief Initialize the communication parameters. 
 *
 * \param NONE.
 * \return NONE.
 */
void serialInit() {
    chariot.s[0] = '\n' ; 
    chariot.s[1] = 0 ; 
    chariot.s[2] = 0 ; 
    chariot.s[3] = 0 ;
}

void sendData(float data){
      union u number ;
      number.f = data ; 
       //RA2_Toggle() ; 
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
         //__delay32(600);
    } 
    sendData(chariot.f) ; 
    
}

void setTransmitterMode(){
    RB5_SetHigh() ; 
}

void setReceiverMode(){
    RB5_SetLow() ; 
}

void send_measurements(state state){
        vect[0] = (float)state.ul.abc.a ; 
        vect[1] = (float)state.ul.abc.b ; 
        vect[2] = (float)state.ul.abc.c ; 
        vect[3] = (float)state.il.abc.a; 
        vect[4] = (float)state.il.abc.b; 
        sendVect(vect,5) ;
}

void send_ul_abc_to_alphabeta(state state){
        vect[0] = (float)state.ul.abc.a ; 
        vect[1] = (float)state.ul.abc.b ; 
        vect[2] = (float)state.ul.abc.c ; 
        vect[3] = (float)state.ul.alphabeta.alpha; 
        vect[4] = (float)state.ul.alphabeta.beta; 
        sendVect(vect,5) ;
}

//void send_theta_estimation(state state){
//    vect[0] =(float)state.ul.alphabeta.alpha ; 
//    vect[1] = (float)state.ul.alphabeta.beta ;
//    
//}


void send_theta_cos_theta(state state, trigo_type cos_theta, trigo_type sin_theta ){
    vect[0] = (float)state.ul.theta ;
    vect[1] = (float)cos_theta ; 
    vect[2] = (float)sin_theta; 
    sendVect(vect,3) ;
}


void send_ul_alphabeta_to_dq(state state){
        vect[0] = (float)state.ul.alphabeta.alpha ;
        vect[1] = (float)state.ul.alphabeta.beta ; 
        vect[2] = (float)state.ul.dq.d; 
        vect[3] = (float)state.ul.dq.q ; 
        vect[4] = (float)state.ul.theta ;   
        sendVect(vect,5) ;
}

void send_il_abc_to_alphabeta(state state){
        vect[0] = (float)state.il.abc.a ; 
        vect[1] = (float)state.il.abc.b  ; 
        vect[2] = (float)state.il.abc.c ; 
        vect[3] = (float)state.il.alphabeta.alpha; 
        vect[4] = (float)state.il.alphabeta.beta; 
        sendVect(vect,5) ;
} 

void send_il_alphabeta_to_dq(state state){
        vect[0] = (float)state.il.alphabeta.alpha ;
        vect[1] = (float)state.il.alphabeta.beta ; 
        vect[2] = (float)state.il.dq.d; 
        vect[3] = (float)state.il.dq.q ; 
        vect[4] = state.ul.theta ;   
        sendVect(vect,5) ;
}

void send_id_controller(tPID id_PID){
        vect[0] = (float)id_PID.controlReference; 
        vect[1] = (float)id_PID.measuredOutput ;  
        vect[2] = (float)id_PID.controlOutput;       
        sendVect(vect,3) ;
}

void send_iq_controller(tPID iq_PID){
        vect[0] = (float)iq_PID.controlReference; 
        vect[1] = (float)iq_PID.measuredOutput ;  
        vect[2] = (float)iq_PID.controlOutput;       
        sendVect(vect,3) ;
}

void send_usd_decoupler_controller(state state,signal us, tPID id_PID){
        vect[0] = (float)id_PID.controlOutput ; 
        vect[1] = (float)state.ul.dq.d; 
        vect[2] = (float)state.il.dq.q; 
        vect[3] = (float)us.dq.d ;
        sendVect(vect,4) ;
}

void send_usq_decoupler_controller(state state,signal us, tPID iq_PID){
        vect[0] = (float)iq_PID.controlOutput ; 
        vect[1] = (float)state.ul.dq.q; 
        vect[2] = (float)state.il.dq.d; 
        vect[3] = (float)us.dq.q ;
        sendVect(vect,4) ;
}

void send_us_dq_to_alphabeta(signal us){
    vect[0] = (float)us.dq.d; 
    vect[1] = (float)us.dq.q ;
    vect[2] = (float)us.alphabeta.alpha ; 
    vect[3] = (float)us.alphabeta.beta ;
    //vect[4] = (float) us_abc->c ;
    sendVect(vect,5) ;
}

void send_us_alphabeta_to_abc(signal us){
    vect[0] = (float)us.alphabeta.alpha ; 
    vect[1] = (float)us.alphabeta.beta ;
    vect[2] = (float)us.abc.a; 
    vect[3] = (float)us.abc.b ;
    vect[4] = (float)us.abc.c ;
    sendVect(vect,5) ;
}

void send_omega(int omega, float theta) {
    vect[0] = theta ; 
    vect[1] = (float)omega ; 
    sendVect(vect,2) ; 
}