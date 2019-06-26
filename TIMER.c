/*
 * TIMER.c
 *
 *  Created on: 13 Oct 2018
 *      Author: Yahia
 */


#include "TIMER.h"
#include "DIO.h"

void TIMER0_InitNM(uint8 a_Prescaler, uint8 a_TIMER0_Bottom){
	/*  This function is set to initialize Timer0 for the normal mode.
	    a_Prescaler is the frequency prescaler.
	    a_TIMER0_Bottom the value that the timer will start count from,
	    it varies from 0 to 255.
	    clock period = 1 / (operating frequency*Prescaler).
	    Tick equation = clock period * ((255 - a_TIMER0_Bottom) + 1).
		You can also use T0_NO_CLOCK, T0_F_CPU_, T0_F_CPU_8,
		T0_F_CPU_64, T0_F_CPU_256, T0_F_CPU_1024 for a_Prescaler.

		*/
	SREG  |= (1<<7);    // global interrupt bit.
	TCNT0 = a_TIMER0_Bottom;  // the value that the timer will start count from.
	TIMSK |= (1<<TOIE0);    // interrupt enable bit for Timer0 in normal mode.
	TCCR0 = (1<<FOC0);    // this bit is set to one for any non-PWM mode.
	TCCR0 = (TCCR0 & 0xF8) | (a_Prescaler & 0x07);  // Prescaler.
}

void TIMER0_InitCM(uint8 a_Prescaler, uint8 a_TIMER0_Bottom, uint8 a_TIMER0_Top){
	/*  This function is set to initialize Timer0 for the compare mode.
	    a_Prescaler is the frequency prescaler.
	    a_TIMER0_Bottom the value that the timer will start count from,
	    it varies from 0 to 255.
	    a_TIMER0_Top the value that the timer will count to,
	    it varies from 0 to 255.
	    clock period = 1 / (operating frequency*Prescaler).
	    Tick equation = clock period * ((a_TIMER0_Top - a_TIMER0_Bottom) + 1).
	    You can also use T0_NO_CLOCK, T0_F_CPU_, T0_F_CPU_8,
		T0_F_CPU_64, T0_F_CPU_256, T0_F_CPU_1024 for a_Prescaler.
	     */
	SREG  |= (1<<7);  // global interrupt bit.
	TCNT0 = a_TIMER0_Bottom;  // the value that the timer will start count from.
	OCR0 = a_TIMER0_Top;  // the value that the timer will count to.
	TIMSK |= (1<<OCIE0);  // interrupt enable bit for Timer0 in compare mode.
	TCCR0 = (1<<FOC0) | (1<<WGM01);  //  enable compare mode.
	TCCR0 = (TCCR0 & 0xF8) | (a_Prescaler & 0x07);  // Prescaler.
}

void TIMER0_InitFPWM(uint8 a_DutyCycle, uint8 a_InvertingOrNon, uint8 a_Prescaler){
	/*  This function is set to initialize Timer0 to generate PWM signal.
	    a_Prescaler is the frequency prescaler.
	    a_InvertingOrNon is either 1 or 0, 0 for non-inverting, 1 for inverting mode.
	    You can also use Non_Inverting_Mode for 0, Inverting_Mode for 1.
	    a_DutyCycle is the value of OCR0 that the signal will vary.
	    OCR0 varies from 0 to 255.
	    To calculate the duty cycle percentage,(OCR0(a_DutyCycle)/255)*100.
	    This value will be the percentage of High in non-inverting mode,
	    and percentage of low in inverting mode.
	    You can also use T0_NO_CLOCK, T0_F_CPU_, T0_F_CPU_8,
		T0_F_CPU_64, T0_F_CPU_256, T0_F_CPU_1024 for a_Prescaler.
	    */
	uint8 temp;
	DIO_MakeOutput(11); //The pin where the PWM signal will be generated.
	TCNT0 = 0; //the value that the timer will start count from.
	temp = (float32)(((float32)a_DutyCycle/100)*255);
	OCR0 = temp; //the value that the signal will be reversed.
	TCCR0 |= (1<<WGM00) | (1<<WGM01) | (1<<COM01); //enable Fast-PWM.
	TCCR0 = (TCCR0 & 0xEF) | (a_InvertingOrNon<<COM00); //Either inverting or non inverting mode.
	TCCR0 = (TCCR0 & 0xF8) | (a_Prescaler & 0x07); // Prescaler.
}

void TIMER1_InitNM(uint8 a_Prescaler, uint16 a_TIMER1_Bottom){
	/*  This function is set to initialize Timer1 for the normal mode.
	    a_Prescaler is the frequency prescaler.
	    a_TIMER1_Bottom the value that the timer will start count from,
	    it varies from 0 to 65535.
	    clock period = 1 / (operating frequency*Prescaler).
	    Tick equation = clock period * ((65535 - a_TIMER0_Bottom) + 1).
	    You can also use T1_NO_CLOCK, T1_F_CPU_, T1_F_CPU_8, T1_F_CPU_64,
	    T1_F_CPU_256, T1_F_CPU_1024 for a_Prescaler.
	 */
	TCNT1 = a_TIMER1_Bottom; // the value that the timer will start count from.
	TIMSK |= (1<<TOIE1); // interrupt enable bit for Timer1 in normal mode.
	SREG  |= (1<<7); // global interrupt bit.
	TCCR1B = (TCCR1B & 0xF8) | (a_Prescaler & 0x07); // Prescaler.
}

void TIMER1_InitCM_ChannelA(uint8 a_Prescaler, uint16 a_TIMER1_Bottom, uint16 a_TIMER1_Top){
	/*  This function is set to initialize Timer1 for the compare mode,
	 	for channel A.
	    a_Prescaler is the frequency prescaler.
	    a_TIMER1_Bottom the value that the timer will start count from,
	    it varies from 0 to 65535.
	    a_TIMER1_Top the value that the timer will count to,
	    it varies from 0 to 65535.
	    clock period = 1 / (operating frequency*Prescaler).
	    Tick equation = clock period * ((a_TIMER1_Top - a_TIMER1_Bottom) + 1).
	    You can also use T1_NO_CLOCK, T1_F_CPU_, T1_F_CPU_8, T1_F_CPU_64,
	    T1_F_CPU_256, T1_F_CPU_1024 for a_Prescaler.
	     */
	SREG  |= (1<<7);// global interrupt bit.
	TCCR1A = (1 << FOC1A);// Enable output compare mode for channel A.
	TIMSK |= (1 << OCIE1A);// interrupt enable bit for Timer1 in compare mode for channel A.
	OCR1A = a_TIMER1_Top;// the value that the timer will count to.
	TCNT1 = a_TIMER1_Bottom;// the value that the timer will start count from.
	TCCR1B = (1 << WGM12);// Enable Compare mode.
	TCCR1B = (TCCR1B & 0xF8) | (a_Prescaler & 0x07);// Prescaler.
}

void TIMER1_InitCM_ChannelB(uint8 a_Prescaler, uint16 a_TIMER1_Bottom, uint16 a_TIMER1_Top){
	/*  This function is set to initialize Timer1 for the compare mode,
	 	for channel B.
	    a_Prescaler is the frequency prescaler.
	    a_TIMER1_Bottom the value that the timer will start count from,
	    it varies from 0 to 65535.
	    a_TIMER1_Top the value that the timer will count to,
	    it varies from 0 to 65535.
	    clock period = 1 / (operating frequency*Prescaler).
	    Tick equation = clock period * ((a_TIMER1_Top - a_TIMER1_Bottom) + 1).
	    You can also use T1_NO_CLOCK, T1_F_CPU_, T1_F_CPU_8, T1_F_CPU_64,
	    T1_F_CPU_256, T1_F_CPU_1024 for a_Prescaler.
	     */
	SREG  |= (1<<7);// global interrupt bit.
	TCCR1A = (1 << FOC1B);// Enable output compare mode for channel B.
	TIMSK |= (1 << OCIE1B);// interrupt enable bit for Timer1 in compare mode for channel B.
	OCR1A = a_TIMER1_Top;// the value that the timer will count to.
	TCNT1 = a_TIMER1_Bottom;// the value that the timer will start count from.
	TCCR1B = (1 << WGM12);// Enable Compare mode.
	TCCR1B = (TCCR1B & 0xF8) | (a_Prescaler & 0x07);// Prescaler.
}

void TIMER1_Init_MSeconds(uint8 a_Prescaler, uint16 MS, uint8 Channel){
	/*
	 * This function is set to start the timer in compare mode to count some seconds,
	   based on values that user will enter.
	 * This function uses Timer1.
	 * Channel for channelA or channelB, 0 for A and 1 for B.
	 * a_Prescaler is the frequency prescaler.
	 * MS the time chosen to count.
	 * You can also use T1_NO_CLOCK, T1_F_CPU_, T1_F_CPU_8, T1_F_CPU_64,
	   T1_F_CPU_256, T1_F_CPU_1024 for a_Prescaler.
	 */
	uint16 a_TIMER_Top;// the value that the timer will count to.
	uint32 Frequency;// Operating Frequency after prescaler.
	switch(a_Prescaler){
	case T1_F_CPU_:
		Frequency = (F_CPU)/256;
		break;

	case T1_F_CPU_8:
		Frequency = (F_CPU)/256;
		break;

	case T1_F_CPU_64:
		Frequency = (F_CPU)/64;
		break;

	case T1_F_CPU_256:
		Frequency = (F_CPU)/256;
		break;

	case T1_F_CPU_1024:
		Frequency = (F_CPU)/1024;
		break;

	default:
		return;
		break;
	}

	a_TIMER_Top = (float32)(((float32)MS/1000)) * Frequency;

	if(Channel){
		TIMER1_InitCM_ChannelB(a_Prescaler, 0, a_TIMER_Top);
	}
	else{
		TIMER1_InitCM_ChannelA(a_Prescaler, 0, a_TIMER_Top);
	}
}

void TIMER0_Init_MSeconds(uint8 a_Prescaler, uint8 MS){
	/*
	 * This function is set to start the timer in compare mode to count some seconds,
	   based on values that user will enter.
	 * This function uses Timer0.
	 * a_Prescaler is the frequency prescaler.
	 * MS the time chosen to count.
	 * You can also use T1_NO_CLOCK, T1_F_CPU_, T1_F_CPU_8, T1_F_CPU_64,
	   T1_F_CPU_256, T1_F_CPU_1024 for a_Prescaler.
	 */

	uint8 a_TIMER0_Top;// the value that the timer will count to.
	uint32 Frequency;// Operating Frequency after prescaler.
	switch(a_Prescaler){
	case T0_F_CPU_:
		Frequency = (F_CPU)/256;
		break;

	case T0_F_CPU_8:
		Frequency = (F_CPU)/256;
		break;

	case T0_F_CPU_64:
		Frequency = (F_CPU)/64;
		break;

	case T0_F_CPU_256:
		Frequency = (F_CPU)/256;
		break;

	case T0_F_CPU_1024:
		Frequency = (F_CPU)/1024;
		break;

	default:
		return;
		break;
	}
	a_TIMER0_Top = (float32)(((float32)MS/1000)*Frequency);
	TIMER0_InitCM(a_Prescaler, 0, a_TIMER0_Top);
}


void TIMER0_DeInit(void){
	/*
	 * This function is set to Deinit(stop) Time0.
	 */
	TCCR0 = 0;
}


void TIMER1_DeInit(void){
	/*
	 * This function is set to Deinit(stop) Time1.
	 */

	TCCR1B = 0;

}


void TIMER1_InitFPWM_ChannelA(uint8 a_DutyCycle, uint8 a_InvertingOrNon, uint8 a_Prescaler){
	/*  This function is set to initialize Timer1 to generate PWM signal, using ChannelA.
	    PWM signal will be generated from PIN29.
	    a_Prescaler is the frequency prescaler.
	    a_InvertingOrNon is either 1 or 0, 0 for non-inverting, 1 for inverting mode.
	    You can also use Non_Inverting_Mode for 0, Inverting_Mode for 1.
	    OCR1A varies from 0 to 65535.
	    a_DutyCycle will be the percentage of High in non-inverting mode,
	    and percentage of low in inverting mode.
	    You can also use T1_NO_CLOCK, T1_F_CPU_, T1_F_CPU_8, T1_F_CPU_64,
	    T1_F_CPU_256, T1_F_CPU_1024 for a_Prescaler.
	    */
	uint16 temp; // This variable will be used to store the value of clocks.
	TCCR1A |= (1<<COM1A1) | (a_InvertingOrNon<<COM1A0) | (1<<WGM11);
	TCCR1B |= (1<<WGM12) | (1<<WGM13);
	ICR1 = 0xFFFF;
	temp = (float32)(((float32)a_DutyCycle/100)*65535);
	OCR1A = temp;
	TCCR1B = (TCCR1B & 0xF8) | (a_Prescaler & 0x07);
}


void TIMER1_InitFPWM_ChannelB(uint8 a_DutyCycle, uint8 a_InvertingOrNon, uint8 a_Prescaler){
	/*  This function is set to initialize Timer1 to generate PWM signal, using ChannelB.
	    PWM signal will be generated from PIN28.
	    a_Prescaler is the frequency prescaler.
	    a_InvertingOrNon is either 1 or 0, 0 for non-inverting, 1 for inverting mode.
	    You can also use Non_Inverting_Mode for 0, Inverting_Mode for 1.
	    OCR1B varies from 0 to 65535.
	    a_DutyCycle will be the percentage of High in non-inverting mode,
	    and percentage of low in inverting mode.
	    You can also use T1_NO_CLOCK, T1_F_CPU_, T1_F_CPU_8, T1_F_CPU_64,
	   T1_F_CPU_256, T1_F_CPU_1024 for a_Prescaler.
	    */
	uint16 temp; // This variable will be used to store the value of clocks.
	TCCR1A |= (1<<COM1B1) | (a_InvertingOrNon<<COM1A0) | (1<<WGM11);
	TCCR1B |= (1<<WGM12) | (1<<WGM13);
	ICR1 = 0xFFFF;
	temp = (float32)(((float32)a_DutyCycle/100)*65535);
	OCR1B = temp;
	TCCR1B = (TCCR1B & 0xF8) | (a_Prescaler & 0x07);
}
