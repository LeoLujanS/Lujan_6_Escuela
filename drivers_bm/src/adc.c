/*
 * adc.c
 *
 *  Created on: 2/6/2016
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

#include "adc.h"
uint32_t dato_convertido;

void inicializar_adc( void )
{
	LPC_ADC_T ADCSetup;
	Chip_SCU_ADC_Channel_Config( 0, ADC_CH1 );
	Chip_ADC_Init(LPC_ADC0, &ADCSetup);

	/* Habilito el adc */
	Chip_ADC_EnableChannel(LPC_ADC0, ADC_CH1, ENABLE);
}

uint32_t leer_adc()
{
	Chip_ADC_Set_StartMode(LPC_ADC0, ADC_START_NOW, ADC_TRIGGERMODE_RISING);

	while(Chip_ADC_Read_Status(LPC_ADC0, ADC_CH1, ADC_DR_DONE_STAT) != SET);
	Chip_ADC_Read_Value(LPC_ADC0, ADC_CH1, &dato_convertido);

	return dato_convertido;
}



