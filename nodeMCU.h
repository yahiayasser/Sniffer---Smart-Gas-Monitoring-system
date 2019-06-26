/*
 * nodeMCU.h
 *
 *  Created on: 22 Jun 2019
 *      Author: Yahia
 */

#ifndef NODEMCU_H_
#define NODEMCU_H_

#include <avr/eeprom.h>
#include "micro_config.h"
#include "UART.h"
#include "DIO.h"
#include "TIMER.h"

#ifndef YES
#define YES 1
#endif

#ifndef NO
#define NO 0
#endif

#ifndef SUCCESS
#define SUCCESS 1
#endif

#ifndef ERROR
#define ERROR 0
#endif

typedef enum{
	ESP_BAUD_57600, ESP_BAUD_115200
}ESP_BAUD_RATE;

typedef enum{
	ESP_PARITY_DISABLE, ESP_EVEN_PARITY, ESP_ODD_PARITY
}ESP_PARITY;

typedef enum{
	ESP_ONE_StopBit, ESP_TWO_StopBit
}ESP_StopBit;

typedef enum{
	ESP_STA, ESP_AP, ESP_STA_AP
}ESP_WIFI_MODE;

typedef enum{
	Disable_DHCP, Enable_DHCP
}ESP_DHCP;

typedef enum{
	Dis_AutoConnect, En_AutoConnect
}ESP_AutoConnect;

typedef enum{
	Disable_Multiple_Connections, Enable_Multiple_connections
}ESP_Multiple_Connections;

#ifndef FirstPhoneNumberAddress
#define FirstPhoneNumberAddress (uint8*)0x0A   /*defining the first address will be used in the eeprom(0x0A)*/
#endif

#ifndef DistanceThresholdAddress
#define DistanceThresholdAddress (uint8*)0x15 /*end of the mobile number of user address in eeprom*/
#endif

#ifndef FirstUseFlagAddress
#define FirstUseFlagAddress (uint8*)0x08
#endif

uint8 string_length(uint8 str[]);
void string_cat(uint8 str1[],uint8 str2[]);
void string_to_char_cat(uint8 str1[],uint8 ch);
void NUM_TO_ASCII(uint32 NUMBER, uint8 string_num[]);
uint8 Strings_Is_Equal(uint8 Str1[], uint8 Str2[]);
uint8 WaitForOk(void);
void TestModule(void);
void DisableEcho(void);
void UARTConfig(uint8 baud_rate, uint8 Parity, uint8 NUM_stop_bits);
void AntennaPower(uint8 Power[]);
void WiFiMode(uint8 MODE);
void WiFiAutoConnect(uint8 AutoConnect);
void ESP_CONNECT_TO_AP(const uint8 SSID[], const uint8 PASSWAORD);
void ConnectToWebsite(uint8 URL[]);
void SMSTextMode(void);

#endif /* NODEMCU_H_ */
