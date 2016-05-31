/* Copyright 2016, XXXXXXXXX  
 * All rights reserved.
 *
 * This file is part of CIAA Firmware.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 */

/** \brief Blinking Bare Metal driver led
 **
 **
 **
 **/

/** \addtogroup CIAA_Firmware CIAA Firmware
 ** @{ */

/** \addtogroup Examples CIAA Firmware Examples
 ** @{ */
/** \addtogroup Baremetal Bare Metal LED Driver
 ** @{ */

/*
 * Initials     Name
 * ---------------------------
 *
 */

/*
 * modification history (new versions first)
 * -----------------------------------------------------------
 * yyyymmdd v0.0.1 initials initial version
 */

/*==================[inclusions]=============================================*/

#ifndef CPU
#error CPU shall be defined
#endif
#if (lpc4337 == CPU)
#include "chip.h"
#elif (mk60fx512vlq15 == CPU)
#else
#endif
#include "led.h"



/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/
/* Defino los LED a utilizar */
#define PB2	    2

#define MASCARALED1 1 << 14
#define MASCARALED2 1 << 11
#define MASCARALED3 1 << 12
#define PUERTO5	5
#define PUERTO0 0
#define PUERTO1 1

/* PINES CONECTADOS LOS LEDS */
#define PINLEDR	0
#define PINLEDG 1
#define PINLEDB 2
#define PINLED1 14
#define PINLED2 11
#define PINLED3 12



#define MASCARALEDRGB 1 << 0 | 1 << 1 | 1 << 2

#define SALIDA 1
#define ENTRADA 0


/*==================[internal functions declaration]=========================*/
void InicializarLed( void );



/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/
void InicializarLed( void )
{
	/* inicializo puerto */
	Chip_GPIO_Init(LPC_GPIO_PORT);

	Chip_SCU_PinMux(2, 0, MD_PUP, FUNC4 ); /* Mapea el P2_0 en GPIO5[0], LED0R y
	 	 	 	 	 	 	 	 	 	 	 	 	 habilita el pull up */
	Chip_SCU_PinMux(2, 1, MD_PUP, FUNC4 ); /* Mapea el P2_1 en GPIO5[1], LED0G y
		 	 	 	 	 	 	 	 	 	 	 	 	 habilita el pull up */
	Chip_SCU_PinMux(2, 2, MD_PUP, FUNC4 ); /* Mapea el P2_2 en GPIO5[2], LED0B y
		 	 	 	 	 	 	 	 	 	 	 	 	 habilita el pull up */
	Chip_SCU_PinMux(2, 10, MD_PUP, FUNC0 ); /* Mapea el P2_10 en GPIO0[14], LED1 y
		 	 	 	 	 	 	 	 	 	 	 	 	 habilita el pull up */
	Chip_SCU_PinMux(2, 11, MD_PUP, FUNC0 ); /* Mapea el P2_11 en GPIO1[11], LED2 y
		 	 	 	 	 	 	 	 	 	 	 	 	 habilita el pull up */
	Chip_SCU_PinMux(2, 12, MD_PUP, FUNC0 ); /* Mapea el P2_12 en GPIO1[12], LED3 y
		 	 	 	 	 	 	 	 	 	 	 	 	 habilita el pull up */

	Chip_GPIO_SetDir(LPC_GPIO_PORT, PUERTO5, MASCARALEDRGB, SALIDA);

	Chip_GPIO_SetDir(LPC_GPIO_PORT, PUERTO0, MASCARALED1 , SALIDA);

	Chip_GPIO_SetDir(LPC_GPIO_PORT, PUERTO1, MASCARALED2 | MASCARALED3 , SALIDA);

    Chip_GPIO_ClearValue( LPC_GPIO_PORT, PUERTO5, MASCARALEDRGB );
    Chip_GPIO_ClearValue( LPC_GPIO_PORT, PUERTO0, MASCARALED1 );
    Chip_GPIO_ClearValue( LPC_GPIO_PORT, PUERTO1, MASCARALED2 | MASCARALED3 );

}

void ToggleLed( uint8_t led)
{
	switch(led){
		case LEDR:
			Chip_GPIO_SetPinToggle( LPC_GPIO_PORT, PUERTO5, PINLEDR );
			break;
		case LEDG:
			Chip_GPIO_SetPinToggle( LPC_GPIO_PORT, PUERTO5, PINLEDG);
			break;
		case LEDB:
			Chip_GPIO_SetPinToggle( LPC_GPIO_PORT, PUERTO5, PINLEDB);
			break;
		case LED1:
			Chip_GPIO_SetPinToggle( LPC_GPIO_PORT, PUERTO0, PINLED1 );
			break;
		case LED2:
			Chip_GPIO_SetPinToggle( LPC_GPIO_PORT, PUERTO1, PINLED2);
			break;
		case LED3:
			Chip_GPIO_SetPinToggle( LPC_GPIO_PORT, PUERTO1, PINLED3 );
			break;
	}
}


void PrenderLed( uint8_t led)
{
	switch(led){
		case LEDR:
			Chip_GPIO_SetPinOutHigh(LPC_GPIO_PORT, PUERTO5, PINLEDR);
			break;
		case LEDG:
			Chip_GPIO_SetPinOutHigh(LPC_GPIO_PORT, PUERTO5, PINLEDG);
			break;
		case LEDB:
			Chip_GPIO_SetPinOutHigh( LPC_GPIO_PORT, PUERTO5, PINLEDB);
			break;
		case LED1:
			Chip_GPIO_SetPinOutHigh( LPC_GPIO_PORT, PUERTO0, PINLED1 );
			break;
		case LED2:
			Chip_GPIO_SetPinOutHigh( LPC_GPIO_PORT, PUERTO1, PINLED2 );
			break;
		case LED3:
			Chip_GPIO_SetPinOutHigh( LPC_GPIO_PORT, PUERTO1, PINLED3 );
			break;
	}

}

void ApagarLed( uint8_t led)
{
	switch(led){
			case LEDR:
				Chip_GPIO_SetPinOutLow(LPC_GPIO_PORT, PUERTO5, PINLEDR);
				break;
			case LEDG:
				Chip_GPIO_SetPinOutLow(LPC_GPIO_PORT, PUERTO5, PINLEDG);
				break;
			case LEDB:
				Chip_GPIO_SetPinOutLow( LPC_GPIO_PORT, PUERTO5, PINLEDB );
				break;
			case LED1:
				Chip_GPIO_SetPinOutLow( LPC_GPIO_PORT, PUERTO0, PINLED1 );
				break;
			case LED2:
				Chip_GPIO_SetPinOutLow( LPC_GPIO_PORT, PUERTO1, PINLED2 );
				break;
			case LED3:
				Chip_GPIO_SetPinOutLow( LPC_GPIO_PORT, PUERTO1, PINLED3 );
				break;
		}

}

//



/*==================[external functions definition]==========================*/
/** \brief Main function
 *
 * This is the main entry point of the software.
 *
 * \returns 0
 *
 * \remarks This function never returns. Return value is only to avoid compiler
 *          warnings or errors.
 */




/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/

