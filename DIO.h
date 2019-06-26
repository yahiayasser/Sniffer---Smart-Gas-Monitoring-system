/*
 * DIO.h
 *
 *  Created on: 12 Oct 2018
 *      Author: Yahia
 */

#ifndef DIO_H_
#define DIO_H_

#include "std_types.h"
#include "common_macros.h"
#include "micro_config.h"

typedef enum{
	DIO_PORTA, DIO_PORTB, DIO_PORTC, DIO_PORTD
}DIO_PORT;

#define PORTA_direction DDRA
#define PORTB_direction DDRB
#define PORTC_direction DDRC
#define PORTD_direction DDRD

#define PORTA_input PINA
#define PORTB_input PINB
#define PORTC_input PINC
#define PORTD_input PIND

#define PORTA_output PORTA
#define PORTB_output PORTB
#define PORTC_output PORTC
#define PORTD_output PORTD

uint8 DIO_ReadChannel(volatile const uint8 a_PIN);
void DIO_WriteChannel(volatile const uint8 a_PIN);
void DIO_ToggleChannel(volatile const uint8 a_PIN);
void DIO_ClearChannel(volatile const uint8 a_PIN);
void DIO_MakeInput(volatile const uint8 a_PIN);
void DIO_MakeOutput(volatile const uint8 a_PIN);
void DIO_PortOutput(volatile const uint8 a_PORT);
void DIO_PortInput(volatile const uint8 a_PORT);
void DIO_WritePort(volatile const uint8 a_PORT, volatile const uint8 a_Data);
void DIO_ClearPort(volatile const uint8 a_PORT);

#endif /* DIO_H_ */
