/*
 * pulsadores.h
 *
 *  Created on: 31/5/2016
 *      Author: Usuario
 */

#ifndef PULSADORES_H_
#define PULSADORES_H_
#include "stdbool.h"

#define SW1	1	/* tecla 1 */
#define SW2 2	/* tecla 2 */
#define SW3 3	/* tecla 3 */
#define SW4 4	/* tecla 4 */


#define MASCARAPULSADOR1 1 << 4
#define MASCARAPULSADOR2 1 << 8
#define MASCARAPULSADOR3 1 << 9	/* la misma para el pulsador 4 */
#define ENTRADA	0

void InicializarTeclas( void );
bool leerPulsador( uint8_t pulsador);
uint8_t leerPuerto( void );


#endif /* PULSADORES_H_ */
