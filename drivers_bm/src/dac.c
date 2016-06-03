/*
 * dac.c
 *
 *  Created on: 1/6/2016
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

#include "dac.h"


void InicializarDAC(void){

	/* Configuracion de los pines del DAC */
	Chip_SCU_DAC_Analog_Config();

	Chip_DAC_Init( LPC_DAC);
	Chip_DAC_ConfigDAConverterControl(LPC_DAC, DAC_DMA_ENA);
}



void ValorDAC(uint32_t valor)
{
	Chip_DAC_UpdateValue(LPC_DAC,valor);
}
