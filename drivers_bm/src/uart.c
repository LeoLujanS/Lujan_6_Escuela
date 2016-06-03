/*
 * uart.c
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


#include "uart.h"


void inicializar_uart(){
	Chip_SCU_PinMux( 7, TX, MD_PDN, FUNC6 ); /* TXD */
	Chip_SCU_PinMux( 7, RX, MD_PLN | MD_EZI | MD_ZI, FUNC6 ); /* RXD */

	Chip_UART_Init(LPC_USART2);

}

void setup_uart(){
	Chip_UART_SetBaud(LPC_USART2, 115200);
	Chip_UART_SetupFIFOS(LPC_USART2, UART_FCR_FIFO_EN | UART_FCR_TRG_LEV0);
}

void habilitar_uart()
{
	Chip_UART_TXEnable(LPC_USART2);
}

uint8_t leerByte_uart( )
{
	return Chip_UART_ReadByte(LPC_USART2);
}

void Send_uart( char data ){

	Chip_UART_SendByte(	LPC_USART2, data);
}
/*
uint8_t uart_status( void )
{
	return Chip_UART_Read_LineStatus(LPC_USART2 & UART_LSR_THRE);
}
*/
