/**
 * \file main.c
 * \brief Programme de tests.
 * \author Franck.H
 * \version 0.1
 * \date 11 septembre 2007
 *
 * Programme de test pour l'objet de gestion des chaînes de caractères Str_t.
 *
 */

#include "serialData.h"

#define SEND_NUMBER 20000
#define FUNCTION_NUMBER 13





void (*functions_array[FUNCTION_NUMBER])(); 

 union u2 chariot ;
 unsigned int sendCounter ; 
 bool sending ; 
 char ReceivedChar; 
  
 
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
    
    sendCounter = 0 ;
    
    functions_array[0] = send_measurements ; 
    functions_array[1] = send_ul_abc_to_alphabeta ;
    functions_array[2] = send_omega ; 
    functions_array[3] = send_ul_alphabeta_to_dq ; 
    
    functions_array[4] = send_il_abc_to_alphabeta ; 
    functions_array[5] = send_il_alphabeta_to_dq ; 
    
    functions_array[6] = send_id_controller ; 
    functions_array[7] = send_iq_controller ; 
    functions_array[8] = send_usq_decoupler_controller ; 
    functions_array[9] = send_usd_decoupler_controller ; 
    
    functions_array[10] = send_us_dq_to_alphabeta ; 
    functions_array[11] = send_us_alphabeta_to_abc ;
    functions_array[12] = send_dc_voltage ; 
    U1STAbits.OERR = 0;
    sending = false ; 
    
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

void send_int(int data_int){
    union u number ;
    number.i = data_int ; 
     //RA2_Toggle() ; 
    int i ; 
    //float x = data ; 
    for( i=0 ; i<2 ; i++){
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

void send_measurements(){
        vect[0] = (float)state_vector.ul.abc.a ; 
        vect[1] = (float)state_vector.ul.abc.b ; 
        vect[2] = (float)state_vector.ul.abc.c ; 
        vect[3] = (float)state_vector.il.abc.a; 
        vect[4] = (float)state_vector.il.abc.b; 
        sendVect(vect,5) ;
}

void send_dc_voltage() {
    vect[0] = (float)state_vector.vout ; 
    sendVect(vect,5) ; 
}
void send_ul_abc_to_alphabeta(){
        vect[0] = (float)state_vector.ul.abc.a ; 
        vect[1] = (float)state_vector.ul.abc.b ; 
        vect[2] = (float)state_vector.ul.abc.c ; 
        vect[3] = (float)state_vector.ul.alphabeta.alpha; 
        vect[4] = (float)state_vector.ul.alphabeta.beta; 
        sendVect(vect,5) ;
}

//void send_theta_estimation(state state){
//    vect[0] =(float)state.ul.alphabeta.alpha ; 
//    vect[1] = (float)state.ul.alphabeta.beta ;
//    
//}


//void send_theta_cos_theta(  trigo_type cos_theta, trigo_type sin_theta ){
//    vect[0] = (float)state_vector.ul.theta ;
//    vect[1] = (float)cos_theta ; 
//    vect[2] = (float)sin_theta; 
//    sendVect(vect,5) ;
//}

void send_omega() {
    vect[0] = state_vector.ul.theta ; 
    vect[1] = omega ; 
    
    
    sendVect(vect,5) ; 
}


void send_ul_alphabeta_to_dq( ){
        vect[0] = (float)state_vector.ul.alphabeta.alpha ;
        vect[1] = (float)state_vector.ul.alphabeta.beta ; 
        vect[2] = (float)state_vector.ul.dq.d; 
        vect[3] = (float)state_vector.ul.dq.q ; 
        vect[4] = (float)state_vector.ul.theta ;   
        sendVect(vect,5) ;
}

void send_il_abc_to_alphabeta( ){
        vect[0] = (float)state_vector.il.abc.a ; 
        vect[1] = (float)state_vector.il.abc.b  ; 
        vect[2] = (float)state_vector.il.abc.c ; 
        vect[3] = (float)state_vector.il.alphabeta.alpha; 
        vect[4] = (float)state_vector.il.alphabeta.beta; 
        sendVect(vect,5) ;
} 

void send_il_alphabeta_to_dq( ){
        vect[0] = (float)state_vector.il.alphabeta.alpha ;
        vect[1] = (float)state_vector.il.alphabeta.beta ; 
        vect[2] = (float)state_vector.il.dq.d; 
        vect[3] = (float)state_vector.il.dq.q ; 
        vect[4] = state_vector.ul.theta ;   
        sendVect(vect,5) ;
}

void send_id_controller( ){
        int id_err = id_controler.controlHistory[0] ; 
        int id_out = id_controler.controlOutput;  
        vect[0] = (float)id_err; 
        vect[1] = (float)id_out ;     
        sendVect(vect,5) ;
}

void send_iq_controller( ){
//    RA2_Toggle() ;
        vect[0] = (float)iq_controler.controlReference; 
        vect[1] = (float)iq_controler.measuredOutput ;  
        vect[2] = (float)iq_controler.controlOutput;       
        sendVect(vect,5) ;
//    RA2_Toggle() ;
}

void send_usd_decoupler_controller(  ){
        vect[0] = (float)id_controler.controlOutput ; 
        vect[1] = (float)state_vector.ul.dq.d; 
        vect[2] = (float)state_vector.il.dq.q; 
        vect[3] = (float)us.dq.d ;
        sendVect(vect,5) ;
}

void send_usq_decoupler_controller(   ){
        vect[0] = (float)iq_controler.controlOutput ; 
        vect[1] = (float)state_vector.ul.dq.q; 
        vect[2] = (float)state_vector.il.dq.d; 
        vect[3] = (float)us.dq.q ;
        sendVect(vect,5) ;
}

void send_us_dq_to_alphabeta( ){
    vect[0] = (float)us_sat.dq.d; 
    vect[1] = (float)us_sat.dq.q ;
    vect[2] = (float)us_sat.alphabeta.alpha ; 
    vect[3] = (float)us_sat.alphabeta.beta ;
    //vect[4] = (float) us_abc->c ;
    sendVect(vect,5) ;
}

void send_us_alphabeta_to_abc( ){
    vect[0] = (float)us_sat.alphabeta.alpha ; 
    vect[1] = (float)us_sat.alphabeta.beta ;
    vect[2] = (float)us_sat.abc.a; 
    vect[3] = (float)us_sat.abc.b ;
    vect[4] = (float)us_sat.abc.c ;
    sendVect(vect,5) ;
}



void limited_counter(){
    sendCounter++ ; 
    if (sendCounter == SEND_NUMBER) {
//                RA2_SetHigh();
        sending = false ; 
        sendCounter =0 ; 
//        __delay_us(10);
//                RA2_SetLow() ; 
    }
}

void listen_RS485(){
    setReceiverMode() ; 
    if(U1STAbits.URXDA == 1 && sending ==false)
    {
//        RA2_SetHigh() ;
//        __delay_us(100);
        ReceivedChar = U1RXREG;
//        RA2_SetLow() ; 
        U1STAbits.OERR = 0; // empty the receiving buffer 

    }
}

void send_if_required(){
     
     if (ReceivedChar>=0 && ReceivedChar<FUNCTION_NUMBER ) {
            sending = true ; 
            limited_counter() ; 
//            RA2_SetHigh();
            setTransmitterMode() ;
//            send_theta_cos_theta( state_vector,  cos_theta,  sin_theta ) ; 
//            send_measurements( state_vector) ; 
            (*functions_array[(int)ReceivedChar])() ; 
//            RA2_SetLow() ; 
        }
}