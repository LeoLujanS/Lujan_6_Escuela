/* Copyright 2016, XXXXXX
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

/** \brief Blinking Bare Metal example source file
 **
 ** This is a mini example of the CIAA Firmware.
 **
 **/

/** \addtogroup CIAA_Firmware CIAA Firmware
 ** @{ */

/** \addtogroup Examples CIAA Firmware Examples
 ** @{ */
/** \addtogroup Baremetal Bare Metal example source file
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
#include "examen.h"
#include "stdbool.h"
#include "dac.h"
#include "led.h"
#include "adc.h"
#include "uart.h"
#include "timer.h"
#include "pulsadores.h"

/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/
#define RETARDO 25000
#define CUENTAMAXIMA 1000
#define LIMITEINFERIOR	10
#define LIMITESUPERIOR	1000

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

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

uint32_t periodo;
uint32_t periodo2 = 100;
uint32_t periodo3 = 100;
uint32_t counter=0;
uint32_t cuenta = 0;
uint32_t contador = 0;

double Amplitud = 2;
double ganancia=1;
double offset = 0;
double valorAD[10] = {0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0};

char msj[12];

int main(void)
{
   /* perform the needed initialization here */
	bool tecla1, tecla2, tecla3, tecla4;
	uint16_t i;

	msj[0] ='o';
	msj[1] ='f';
	msj[2] ='f';
	msj[3] ='s';
	msj[4] ='e';
	msj[5] ='t';
	msj[6] ='=';

	InicializarTimer();
	InicializarTeclas();
	periodo = 10;
	InicializarDAC();
	inicializar_adc();
	InicializarLed();
	inicializar_uart();
	setup_uart();


	TimerConfig( periodo );


	/*led = LED3;*/

	habilitar_uart();
	HabilitarTimer();
	for(;;)
	{
		tecla1 = leerPulsador(SW1);
		tecla2 = leerPulsador(SW2);
		tecla3 = leerPulsador(SW3);
		tecla4 = leerPulsador(SW4);

		if(!tecla1)
		{
			for(i=RETARDO;i != 0; i--);
			if(!(tecla1 = leerPulsador(SW1)))
			{
				ganancia -= 0.1;
			}
			while(!(leerPulsador(SW1)));
		}

		if(!tecla2)
		{
			for(i=RETARDO;i != 0; i--);
			if(!(tecla2 = leerPulsador(SW2)))
			{
				ganancia += 0.1;
			}
			while(!(leerPulsador(SW2)));
		}
		if(ganancia > 1.2 )
		{
			ganancia = 1.2;
			msj[7]='1';
			msj[8]='.';
			msj[9]='2';
		}else if(ganancia < 0.8){
			ganancia = 0.8;
			msj[7]='0';
			msj[8]='.';
			msj[9]='8';
		}else if((0.8 < ganancia)&& (ganancia < 1)){
			msj[7]='0';
			msj[8]='.';
			msj[9]='9';
		}else if((0.9 < ganancia) && (ganancia < 1.1)){
			msj[7]='1';
			msj[8]='.';
			msj[9]='0';
		}else if(( 1 < ganancia) && (ganancia< 1.2)){
			msj[7]='1';
			msj[8]='.';
			msj[9]='1';
		}
		msj[10]='\r';

		if(!tecla3)
		{
			for(i=RETARDO;i != 0; i--);
			if(!(tecla3 = leerPulsador(SW3)))
			{
				offset -= 0.1;
			}
			while(!(leerPulsador(SW3)));
		}

		if(!tecla4)
		{
			for(i=RETARDO;i != 0; i--);
			if(!(tecla4 = leerPulsador(SW4)))
			{
				offset += 0.1;
			}
			while(!(leerPulsador(SW4)));
		}

		if(offset > 0.2)
		{
			offset = 0.2;
		}else if(offset < -0.2  ){
			offset = -0.2;
		}
		if( cuenta >= periodo3 ){
			cuenta = 0;
			for(i=0; i < 11; i++ ){
				Send_uart( msj[i] );
			}
		}



	}

}



uint32_t funcion_calibracion( uint32_t val1)
{
	double result;
	uint32_t Valordig;
	if( val1 >= (periodo2/2)){
		val1 = 100;
	}else{
		val1 = 50;
	}
	result = ganancia * Amplitud * ((double)val1/ (double) periodo2) + offset;
	Valordig = (uint32_t)((result*(double)(MAX_RESOLUCION-1))/(double)MAX_DAC_OUTPUT);
	return Valordig;
}


double encuentraMAX (double b[], uint32_t tam )
{
	uint8_t i;
	double auxiliar, maximo;

	b[0]= maximo;
	for(i=1; i<tam; i++){
		if(b(i)>b(i-1)){
			maximo = b(i);

		}


	}


}



void ISR_TIMER(void)
{
	uint32_t Valordigital;
	uint32_t ValorAnalog;

	DeshabilitarTimer();
	Valordigital = funcion_calibracion( counter );
	if(counter >= periodo2){
		counter = 0;
	}else{
		counter += 10;
	}
	if(contador >= periodo ){
		contador = 0;
	}else{
		contador++;
	}
	ValorAnalog = leer_adc();
	valorAD[contador]= (double)ValorAnalog*3.3/(double)1023;
	cuenta++;
	ValorDAC( Valordigital );
	BorrarBandera();
	TimerConfig( periodo );
	HabilitarTimer();

}
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/

