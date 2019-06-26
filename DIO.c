/*
 * DIO.c
 *
 *  Created on: 12 Oct 2018
 *      Author: Yahia
 */


#include"DIO.h"

uint8 DIO_ReadChannel(volatile const uint8 a_PIN){
	uint8 a_Data = 0;
	if(a_PIN/8 == 0){
		a_Data = (PORTA_input & (1 << a_PIN));
		a_Data = a_Data >> a_PIN;
	}
	else if(a_PIN/8 == 1)
		a_Data = ((PORTB_input&(1 << (a_PIN-8))) >> (a_PIN-8));
	else if(a_PIN/8 == 2)
		a_Data = ((PORTC_input&(1 << (a_PIN-16))) >> (a_PIN-16));
	else
		a_Data = ((PORTD_input&(1 << (a_PIN-24))) >> (a_PIN-24));

	return a_Data;
}

void DIO_WriteChannel(volatile const uint8 a_PIN){
	if(a_PIN/8 == 0){
		PORTA_output |= (1<<a_PIN);
	}
	else if(a_PIN/8 == 1){
		PORTB_output |= (1<<(a_PIN-8));
	}
	else if(a_PIN/8 == 2){
		PORTC_output |= (1<<(a_PIN-16));
	}
	else{
		PORTD_output |= (1<<(a_PIN-24));
	}
}

void DIO_ClearChannel(volatile const uint8 a_PIN){
	if(a_PIN/8 == 0)
		PORTA_output &= ~(1 << a_PIN);
	else if(a_PIN/8 == 1)
		PORTB_output &= ~(1 << (a_PIN - 8));
	else if(a_PIN/8 == 2)
		PORTC_output &= ~(1 << (a_PIN - 16));
	else
		PORTD_output &= ~(1 << (a_PIN - 24));
}

void DIO_MakeInput(volatile const uint8 a_PIN){
	if(a_PIN/8 == 0)
		PORTA_direction &= ~(1 << a_PIN);
	else if(a_PIN/8 == 1)
		PORTB_direction &= ~(1 << (a_PIN - 8));
	else if(a_PIN/8 == 2)
		PORTC_direction &= ~(1 << (a_PIN - 16));
	else
		PORTD_direction &= ~(1 << (a_PIN - 24));
}

void DIO_MakeOutput(volatile const uint8 a_PIN){
	if(a_PIN/8 == 0)
		PORTA_direction |= (1 << a_PIN);
	else if(a_PIN/8 == 1)
		PORTB_direction |= (1 << (a_PIN - 8));
	else if(a_PIN/8 == 2)
		PORTC_direction |= (1 << (a_PIN - 16));
	else
		PORTD_direction |= (1 << (a_PIN - 24));
}

void DIO_ToggleChannel(volatile const uint8 a_PIN){
	if(a_PIN/8 == 0)
		PORTA_output ^= (1 << a_PIN);
	else if(a_PIN/8 == 1)
		PORTB_output ^= (1 << (a_PIN - 8));
	else if(a_PIN/8 == 2)
		PORTC_output ^= (1 << (a_PIN - 16));
	else
		PORTD_output ^= (1 << (a_PIN - 24));
}

void DIO_PortInput(volatile const uint8 a_PORT){
	/*You can also use DIO_PORTA, DIO_PORTB, DIO_PORTC, DIO_PORTD
	 * */
	switch(a_PORT){
	case 0:
		PORTA_direction = 0;
		break;
	case 1:
		PORTB_direction = 0;
		break;
	case 2:
		PORTC_direction = 0;
		break;
	case 3:
		PORTD_direction = 0;
		break;
	}
}

void DIO_PortOutput(volatile const uint8 a_PORT){
	/*You can also use DIO_PORTA, DIO_PORTB, DIO_PORTC, DIO_PORTD
	 * */
	switch(a_PORT){
	case 0:
		PORTA_direction = 0xFF;
		break;
	case 1:
		PORTB_direction = 0xFF;
		break;
	case 2:
		PORTC_direction = 0xFF;
		break;
	case 3:
		PORTD_direction = 0xFF;
		break;
	}
}

void DIO_WritePort(volatile const uint8 a_PORT, volatile const uint8 a_Data){
	switch(a_PORT){
	case 0:
		PORTA_output = a_Data;
		break;
	case 1:
		PORTB_output = a_Data;
		break;
	case 2:
		PORTC_output = a_Data;
		break;
	case 3:
		PORTD_output = a_Data;
		break;
	}
}

void DIO_ClearPort(volatile const uint8 a_PORT){
	switch(a_PORT){
	case 0:
		PORTA_output = 0;
		break;
	case 1:
		PORTB_output = 0;
		break;
	case 2:
		PORTC_output = 0;
		break;
	case 3:
		PORTD_output = 0;
		break;
	}
}
