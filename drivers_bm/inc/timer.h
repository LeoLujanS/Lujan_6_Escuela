/*
 * timer.h
 *
 *  Created on: 31/5/2016
 *      Author: Usuario
 */

#ifndef TIMER_H_
#define TIMER_H_


/*==================[inclusions]=============================================*/
#include "stdint.h"

/*==================[macros]=================================================*/

void InicializarTimer( void );
void TimerConfig( uint32_t tp);
void HabilitarTimer( void );
void BorrarBandera( void );
void DeshabilitarTimer( void );

#endif /* TIMER_H_ */
