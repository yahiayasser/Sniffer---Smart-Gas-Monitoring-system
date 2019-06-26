/*
 * TIMER.h
 *
 *  Created on: 13 Oct 2018
 *      Author: Yahia
 */

#ifndef TIMER_H_
#define TIMER_H_

#include "common_macros.h"
#include "std_types.h"
#include "micro_config.h"

#ifndef Inverting_Mode
#define Inverting_Mode 1
#endif

#ifndef Non_Inverting_Mode
#define Non_Inverting_Mode 0
#endif

#ifndef ChannelA
#define ChannelA 0
#endif

#ifndef ChannelB
#define ChannelB 1
#endif

typedef enum{
	T0_NO_CLOCK, T0_F_CPU_, T0_F_CPU_8, T0_F_CPU_64, T0_F_CPU_256, T0_F_CPU_1024
}TIMER0_Prescaler;

typedef enum{
	T1_NO_CLOCK, T1_F_CPU_, T1_F_CPU_8, T1_F_CPU_64, T1_F_CPU_256, T1_F_CPU_1024
}TIMER1_Prescaler;

typedef enum{
	T2_NO_CLOCK, T2_F_CPU_, T2_F_CPU_8, T2_F_CPU_64, T2_F_CPU_256, T2_F_CPU_1024
}TIMER2_Prescaler;

typedef enum{
	T0_FALLING = 6, T0_RISING = 7
}TIMER0_Edge;

typedef enum{
	T1_FALLING = 6, T1_RISING = 7
}TIMER1_Edge;

typedef enum{
	T2_FALLING = 6, T2_RISING = 7
}TIMER2_Edge;

void TIMER0_InitNM(uint8 a_Prescaler, uint8 a_TIMER0_Bottom);
void TIMER0_InitCM(uint8 a_Prescaler, uint8 a_TIMER0_Bottom, uint8 a_TIMER0_Top);
void TIMER0_InitFPWM(uint8 a_DutyCycle, uint8 a_InvertingOrNon, uint8 a_Prescaler);
void TIMER1_InitNM(uint8 a_Prescaler, uint16 a_TIMER1_Bottom);
void TIMER1_InitCM_ChannelA(uint8 a_Prescaler, uint16 a_TIMER1_Bottom, uint16 a_TIMER1_Top);
void TIMER1_InitCM_ChannelB(uint8 a_Prescaler, uint16 a_TIMER1_Bottom, uint16 a_TIMER1_Top);
void TIMER1_Init_MSeconds(uint8 a_Prescaler, uint16 MS, uint8 Channel);
void TIMER0_Init_MSeconds(uint8 a_Prescaler, uint8 MS);
void TIMER0_DeInit(void);
void TIMER1_DeInit(void);
void TIMER1_InitFPWM_ChannelA(uint8 a_DutyCycle, uint8 a_InvertingOrNon, uint8 a_Prescaler);
void TIMER1_InitFPWM_ChannelB(uint8 a_DutyCycle, uint8 a_InvertingOrNon, uint8 a_Prescaler);

#endif /* TIMER_H_ */
