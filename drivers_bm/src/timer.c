/*
 * timer.c
 *
 *  Created on: 31/5/2016
 *      Author: Usuario
 */
#ifndef CPU
#error CPU shall be defined
#endif
#if (lpc4337 == CPU)
#include "chip.h"
#elif (mk60fx512vlq15 == CPU)
#else
#endif
#include "timer.h"


/*==================[inclusions]=============================================*/

void InicializarTimer( void )
{
	Chip_RIT_Init( LPC_RITIMER );
	NVIC_EnableIRQ( 11 );
}


void TimerConfig( uint32_t tp)
{
	Chip_RIT_SetTimerInterval( LPC_RITIMER, tp );	/* CONFIGURA EL PERIODO EN ms del TIMER */
}

void HabilitarTimer( void)
{
	Chip_RIT_Enable( LPC_RITIMER );
}

void DeshabilitarTimer(void)
{
	Chip_RIT_Disable( LPC_RITIMER );
}


void BorrarBandera( void )
{
	Chip_RIT_ClearInt( LPC_RITIMER );
}
