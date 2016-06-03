/*
 * dac.h
 *
 *  Created on: 1/6/2016
 *      Author: Usuario
 */

#ifndef DAC_H_
#define DAC_H_

#define MAX_DAC_OUTPUT 3.3
#define MAX_RESOLUCION 1024

void InicializarDAC( void );

void ValorDAC( uint32_t valor );


#endif /* DAC_H_ */
