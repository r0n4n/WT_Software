/* 
 * File:   serialData.h
 * Author: rblan
 *
 * Created on April 26, 2018, 5:01 PM
 */

#ifndef SERIALDATA_H
#define	SERIALDATA_H

#ifdef	__cplusplus
extern "C" {
#endif


union u
{
    unsigned int i; /**< acesso a peda�o de m�m�ria de 32 bits atrav�s de tipo inteiro sem sinal. */
    float f; 
    double d ; 
    uint8_t s[4]; /**< acesso a peda�o de m�m�ria de 32 bits peda�os correspondentes a caract�res. */
};

void sendData(float data) ; 


#ifdef	__cplusplus
}
#endif

#endif	/* SERIALDATA_H */

