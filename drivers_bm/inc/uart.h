/*
 * uart.h
 *
 *  Created on: 2/6/2016
 *      Author: Usuario
 */

#ifndef UART_H_
#define UART_H_
#define TX 1
#define RX 2


void inicializar_uart( void );
void setup_uart( void );
void habilitar_uart( void );
uint8_t leerByte_uart( void );
void Send_uart( char data );
/*uint8_t uart_status( void );*/
#endif /* UART_H_ */
