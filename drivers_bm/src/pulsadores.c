/*
 * pulsadores.c
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

#include "pulsadores.h"
#include "stdbool.h"





void InicializarTeclas(void)
{
	Chip_GPIO_Init(LPC_GPIO_PORT);

	Chip_SCU_PinMux(1,0,MD_PUP|MD_EZI|MD_ZI,FUNC0); /* mapea P1 0 en GPIO 0[4], SW1 */
	Chip_SCU_PinMux(1,1,MD_PUP|MD_EZI|MD_ZI,FUNC0); /* mapea P1 1 en GPIO 0[8], SW2 */
	Chip_SCU_PinMux(1,2,MD_PUP|MD_EZI|MD_ZI,FUNC0); /* mapea P1 2 en GPIO 0[9], SW3 */
	Chip_SCU_PinMux(1,6,MD_PUP|MD_EZI|MD_ZI,FUNC0); /* mapea P1 6 en GPIO 1[9], SW4 */

	Chip_GPIO_SetDir(LPC_GPIO_PORT, 0, MASCARAPULSADOR1 | MASCARAPULSADOR2 |MASCARAPULSADOR3, ENTRADA);
	Chip_GPIO_SetDir(LPC_GPIO_PORT, 1, MASCARAPULSADOR3, ENTRADA);
}

bool leerPulsador(uint8_t pulsador)
{
	bool a;
	switch(pulsador){
		case SW1:
			a = Chip_GPIO_ReadPortBit( LPC_GPIO_PORT, 0, 4);
			break;
		case SW2:
			a = Chip_GPIO_ReadPortBit( LPC_GPIO_PORT, 0, 8 );
			break;
		case SW3:
			a = Chip_GPIO_ReadPortBit( LPC_GPIO_PORT, 0, 9 );
			break;
		case SW4:
			a = Chip_GPIO_ReadPortBit( LPC_GPIO_PORT, 1, 9 );
			break;
	}
	return a;
}

uint8_t leerPuerto( void )
{
	uint32_t valor1, valor2;
	uint8_t result;

	valor1 = Chip_GPIO_ReadValue( LPC_GPIO_PORT, 0);
	valor2 = Chip_GPIO_ReadValue( LPC_GPIO_PORT, 1);

	if (valor1 & MASCARAPULSADOR1)
	{
		result = 1 << 0;
	}else{
		result = 0 << 0;
	}
	if (valor1 & MASCARAPULSADOR2 )
	{
		result = 1 << 1;
	}else{
		result = 0 << 1;
	}
	if( valor1 & MASCARAPULSADOR3 )
	{
		result = 1 << 2;
	}else{
		result = 0 << 2;
	}
	if( valor2 & MASCARAPULSADOR3 )
	{
		result = 1 << 3;
	}else{
		result = 0 << 3;
	}
	return result;
}
