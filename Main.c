/*
 * sniffer_1.c
 *
 *  Created on: Jun 18, 2019
 *      Author: YAHIA
 */



#include "Main.h"

//uint8 *add = e1_address;
uint8 FirstUseFlag;
uint8 TIMER0_Tick = 0;
uint8 MessageFlag = 0;
uint8 Website[30];
uint8 SSID[20];
uint8 Password[15];
uint8 DistanceThreshold;
uint8 UserPhoneNumber[12];
uint8 URL[] = "Enter URL";

ISR (INT0_vect){   /*interrupt for reset button*/
	EnableFirstUseMode(&FirstUseFlag);
}

ISR (INT1_vect){
	CloseValve();/*close the valve the */
}

ISR (INT2_vect){
	OpenValve();/*open the valve the */
}

int main(void){
	/*most of the next data declerations are temporary to continue coding(th_c,MediumDistance,HighDistance which are the DistanceThresholds for each distance, and GasLevels)*/
	uint16 GasLevel;
	//_delay_ms(2000);
	SystemInitiation();
	FirstUseFlag = eeprom_read_byte(FirstUseFlagAddress);

	while(1)
	{
		/*receive ip,number from the user via uart working with mcu*/
		/*function and pooling to get the mcu data(ip,distance) needed{}*/
		if(FirstUseFlag == 0){
			FirstUseMode(&FirstUseFlag);
		}

		while(FirstUseFlag){
			/*function to track sensor's readings incorporating ADC{}*/
			if(DistanceThreshold == LowDistance)
			{
				if(GasLevel > LowDistance){
					CloseValve();
					GSM_sendmessage("You have a gas leakage and the valve is closed.");
					TIMER1_InitCM_ChannelB(T1_F_CPU_1024, 0, 31250);
					while(GasLevel > LowDistance){
						if(TIMER0_Tick == 300){
							if(MessageFlag == 0){
								GSM_sendmessage("It has been 60 seconds since the leakage has occurred \nand the situation needs your presence.");
								MessageFlag = 1;
								TIMER0_Tick = 0;
							}
							else{
								GSM_sendmessage("The situation is dangerous.");
								TIMER0_Tick = 0;
							}
						}
					}
					TIMER0_Tick = 0;
					MessageFlag = 0;
					TIMER1_DeInit();
					GSM_sendmessage("The situation is under control. It's safe now.");
				}
			}
			else if(DistanceThreshold == MediumDistance){
				if(GasLevel > MediumDistance){
					CloseValve();
					GSM_sendmessage("You have a gas leakage and the valve is closed.");
					TIMER1_InitCM_ChannelB(T1_F_CPU_1024, 0, 31250);
					while(GasLevel > MediumDistance){
						if(TIMER0_Tick == 300){
							if(MessageFlag == 0){
								GSM_sendmessage("It has been 60 seconds since the leakage has occurred \nand the situation needs your presence.");
								MessageFlag = 1;
								TIMER0_Tick = 0;
							}
							else{
								GSM_sendmessage("The situation is dangerous.");
								TIMER0_Tick = 0;
							}
						}
					}
					TIMER0_Tick = 0;
					MessageFlag = 0;
					TIMER1_DeInit();
					GSM_sendmessage("The situation is under control. It's safe now.");
				}
			}
			else{
				if(GasLevel > HighDistance){
					CloseValve();
					GSM_sendmessage("You have a gas leakage and the valve is closed.");
					TIMER1_InitCM_ChannelB(T1_F_CPU_1024, 0, 31250);
					while(GasLevel > HighDistance){
						if(TIMER0_Tick == 300){
							if(MessageFlag == 0){
								GSM_sendmessage("It has been 60 seconds since the leakage has occurred \nand the situation needs your presence.");
								MessageFlag = 1;
								TIMER0_Tick = 0;
							}
							else{
								GSM_sendmessage("The situation is dangerous.");
								TIMER0_Tick = 0;
							}
						}
					}
					TIMER0_Tick = 0;
					MessageFlag = 0;
					TIMER1_DeInit();
					GSM_sendmessage("The situation is under control. It's safe now.");
				}
			}
		}
	}
}
