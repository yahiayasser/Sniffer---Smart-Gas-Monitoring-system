/*
 * nodeMCU.c
 *
 *  Created on: 22 Jun 2019
 *      Author: Yahia
 */


#include "nodeMCU.h"

extern uint8 TIMER0_Tick;
extern uint8 Website[30];

ISR(TIMER0_OVF_vect){
	TIMER0_Tick ++;
}

uint8 string_length(uint8 str[]){
	uint8 count;
	/* count the string start from element 0 until the element before the NULL terminator */
	for(count = 0; str[count] != '\0'; ++count);
	return count;
}

uint8 Strings_Is_Equal(uint8 Str1[], uint8 Str2[]){
	uint8 count = 0;
	uint8 Str1_length = string_length(Str1);
	uint8 Str2_length = string_length(Str2);
	if(Str1_length == Str2_length){
		while(count < Str1_length){
			if(Str1[count] != Str2[count]){
				return NO;
			}
			count++;
		}
		return YES;
	}
	else{
		return NO;
	}
}

void string_cat(uint8 str1[],uint8 str2[])
{
	uint8 str1_length, count;
	/* This loop is to store the length of str1 in i
	 * It just counts the number of characters in str1
	 * You can also use strlen instead of this.
	 */
	str1_length = string_length(str1);

	/* This loop would concatenate the string str2 at
	 * the end of str1
	 */
	for(count=0; str2[count]!='\0'; ++count, ++str1_length)
	{
		str1[str1_length]=str2[count];
	}
	/* \0 represents end of string */
	str1[str1_length]='\0';
}

void NUM_TO_ASCII(uint32 NUMBER, uint8 string_num[]){
	uint8 count;
	uint8 reminder = 0;
	uint8 NUM_DIGITS = 0;
	if (NUMBER == 0){
		NUM_DIGITS = 1;
	}
	else{
		while(NUMBER != 0){
			NUM_DIGITS++;
			NUMBER = NUMBER/10;
		}
	}
	for(count = 0; count < NUM_DIGITS; count++){
		reminder = NUMBER % 10;
		string_num[NUM_DIGITS - count - 1] = reminder + 48;
		NUMBER = NUMBER/10;
	}
	string_num[count] = '\0';
}

uint8 WaitForOk(void){
	TIMER0_InitNM(T0_F_CPU_1024, 0);
	uint8 OK[3] = "00";
	uint8 Flag = 0;
	do{
		if(Flag == 2){
			OK[0] = OK[1];
			OK[1] = UART_recieveByteWithTimer();
		}
		else if(Flag == 0){
			OK[0] = UART_recieveByteWithTimer();
			Flag = 1;
		}
		else{
			OK[1] = UART_recieveByteWithTimer();
			Flag = 2;
		}
		if(TIMER0_Tick >= 46){
			TIMER0_DeInit();
			TIMER0_Tick = 0;
			return ERROR;
		}
	}
	while(!(Strings_Is_Equal(OK, "OK")));
	TIMER0_DeInit();
	TIMER0_Tick = 0;
	_delay_ms(10);
	return SUCCESS;
}

void TestModule(void){
	uint8 STRING[] = "AT\r\n";
	do{
		UART_sendString(STRING);
	}
	while(WaitForOk() == ERROR);
}

void DisableEcho(void){
	uint8 STRING[] = "ATE0\r\n";
	do{
		UART_sendString(STRING);
	}
	while(WaitForOk() == ERROR);
}

void UARTConfig(uint8 baud_rate, uint8 Parity, uint8 NUM_stop_bits){
	/* baud_rate ===> 115200 OR 57600, YOU CAN USE ESP_BAUD_57600, ESP_BAUD_115200
	 * Parity ===> Even, Odd OR Disabled, YOU CAN USE ESP_PARITY_DISABLE, ESP_EVEN_PARITY, ESP_ODD_PARITY
	 * NUM_stop_bits ===> One OR Two BITS, YOU CAN USE ESP_ONE_StopBit, ESP_TWO_StopBit
	 * */
	if (baud_rate == 0){
		if (NUM_stop_bits == 0){
			if(Parity == 0){
				do{
					UART_sendString("AT+UART_CUR=57600,8,1,0,0\r\n");
				}
				while(WaitForOk() == ERROR);
			}
			else if(Parity == 1){
				do{
					UART_sendString("AT+UART_CUR=57600,8,1,1,0\r\n");
				}
				while(WaitForOk() == ERROR);
			}
			else{
				do{
					UART_sendString("AT+UART_CUR=57600,8,1,2,0\r\n");
				}
				while(WaitForOk() == ERROR);
			}
		}
		else {
			if(Parity == 0){
				do{
					UART_sendString("AT+UART_CUR=57600,8,3,0,0\r\n");
				}
				while(WaitForOk() == ERROR);
			}
			else if(Parity == 1){
				do{
					UART_sendString("AT+UART_CUR=57600,8,3,1,0\r\n");
				}
				while(WaitForOk() == ERROR);
			}
			else{
				do{
					UART_sendString("AT+UART_CUR=57600,8,3,2,0\r\n");
				}
				while(WaitForOk() == ERROR);
			}
		}
	}
	else{
		if (NUM_stop_bits == 0){
			if(Parity == 0){
				do{
					UART_sendString("AT+UART_CUR=115200,8,1,0,0\r\n");
				}
				while(WaitForOk() == ERROR);
			}
			else if(Parity == 1){
				do{
					UART_sendString("AT+UART_CUR=115200,8,1,1,0\r\n");
				}
				while(WaitForOk() == ERROR);
			}
			else{
				do{
					UART_sendString("AT+UART_CUR=115200,8,1,2,0\r\n");
				}
				while(WaitForOk() == ERROR);
			}
		}
		else {
			if(Parity == 0){
				do{
					UART_sendString("AT+UART_CUR=115200,8,3,0,0\r\n");
				}
				while(WaitForOk() == ERROR);
			}
			else if(Parity == 1){
				do{
					UART_sendString("AT+UART_CUR=115200,8,3,1,0\r\n");
				}
				while(WaitForOk() == ERROR);
			}
			else{
				do{
					UART_sendString("AT+UART_CUR=115200,8,3,2,0\r\n");
				}
				while(WaitForOk() == ERROR);
			}
		}
	}
}

void AntennaPower(uint8 Power[]){
	uint8 STRING[22] = "AT+RFPOWER=";
	string_cat(STRING, Power);
	string_cat(STRING, "\r\n");
	do{
		UART_sendString(STRING);
	}
	while(WaitForOk() == ERROR);
}

void WiFiMode(uint8 MODE){
	/* * There are three WiFi working modes:
	    Station mode, softAP mode, and the co-existence of Station mode and softAP mode.
	 * YOU CAN ALSO USE, ESP_STA, ESP_AP, ESP_STA_AP, AS A FUNCTION ARGUMENT.
	 * */
	uint8 STRING[22] = "AT+CWMODE_CUR";
	switch(MODE){
	case(0):
		string_cat(STRING, "=1");
	break;
	case(1):
		string_cat(STRING, "=2");
	break;
	case(2):
		string_cat(STRING, "=3");
	break;
	}
	string_cat(STRING, "\r\n");
	do{
		UART_sendString(STRING);
	}
	while(WaitForOk() == ERROR);
}

void WiFiAutoConnect(uint8 AutoConnect){
	/* Default is enable, ESP8266 station will connect to AP automatically when power on.
	 * YOU CAN ALSO USE Dis_AutoConnect AND En_AutoConnect
	 * */
	uint8 STRING[20] = "AT+CWAUTOCONN";
	switch(AutoConnect){
	case(0):
				string_cat(STRING, "=0");
	break;
	case(1):
				string_cat(STRING, "=1");
	break;
	}
	string_cat(STRING, "\r\n");
	do{
		UART_sendString(STRING);
	}
	while(WaitForOk() == ERROR);
}

void ESP_CONNECT_TO_AP(const uint8 SSID[], const uint8 PASSWAORD){
	uint8 STRING[50] = "AT+CWJAP_CUR=\"";
	string_cat(STRING, SSID);
	string_cat(STRING, "\",\"");
	string_cat(STRING, PASSWAORD);
	string_cat(STRING, "\"\r\n");
	do{
		UART_sendString(STRING);
	}
	while(WaitForOk() == ERROR);
}

void ConnectToWebsite(uint8 URL[]){
	uint8 STRING1[60] = "AT+CIPSTART=\"TCP\",\"";
	uint8 count = 0;
	while(URL[count] != '/'){
		Website[count] = URL[count];
		count++;
	}
	Website[count] = '\0';
	string_cat(STRING1, Website);
	string_cat(STRING1, "\",80\r\n");
	do{
		UART_sendString(STRING1);
	}
	while(WaitForOk() == ERROR);
}

void SMSTextMode(void){
	uint8 STRING[] = "AT+CMGF=1\r\n";
	do{
		UART_sendString(STRING);
	}
	while(WaitForOk() == ERROR);
}
