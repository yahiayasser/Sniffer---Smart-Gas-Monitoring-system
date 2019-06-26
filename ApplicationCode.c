/*
 * sniffer_1.c
 *
 *  Created on: Jun 18, 2019
 *      Author: YAHIA
 */



#include "ApplicationCode.h"

extern uint8 Website[30];
extern uint8 SSID[20];
extern uint8 Password[15];
extern uint8 DistanceThreshold;
extern uint8 UserPhoneNumber[12];
extern uint8 URL[];

static void GetPhoneNum(uint8 PhoneNum[]){
	uint8* count1 = FirstPhoneNumberAddress;
	uint8 count2 = 0;
	while(count2 < 11){
		PhoneNum[count2] = eeprom_read_byte((uint8*)count1);
		count1 ++;
		count2 ++;
	}
	PhoneNum[count2] = '\0';
}

void EnterNumberOfUser(void){
	uint8 STRING[40] = "AT+CMGS=\"";
	uint8 PhoneNum[12];
	GetPhoneNum(PhoneNum);
	string_cat(STRING, PhoneNum);
	string_cat(STRING, "\"\r\n");
	do{
		UART_sendString(STRING);
	}
	while(WaitForOk() == ERROR);
}

void GSM_sendmessage(uint8 message[]){
	SET_BIT(PORTA,PA0);
	SET_BIT(PORTA,PA1);
	TestModule();
	DisableEcho();
	SMSTextMode();
	EnterNumberOfUser();
	UART_sendString(message);
	UART_sendString(26);
	CLEAR_BIT(PORTA,PA0);
	CLEAR_BIT(PORTA,PA1);
}

void GetDataFromServer(uint8 URL[]){
	uint8 STRING1[120] = "GET ";
	uint8 STRING2[25] = "AT+CIPSEND=";
	uint8 WebsiteHeader[30];
	uint8 NumOfBytes[3];
	uint8 Distance[12];
	uint8 Bytes;
	uint8 count1 = 0;
	uint8 count2 = 0;
	while(URL[count1] != '/'){
		count1++;
	}
	while(URL[count1] != '\0'){
		WebsiteHeader[count2] = URL[count1];
		count1++;
		count2++;
	}
	WebsiteHeader[count2] = '\0';
	count1 = 0;
	count2 = 0;
	string_cat(STRING1, WebsiteHeader);
	string_cat(STRING1, " HTTP/1.1\r\nHost: ");
	string_cat(STRING1, Website);
	string_cat(STRING1, "\r\n\r\n");
	Bytes= string_length(URL) + 25;
	NUM_TO_ASCII(Bytes, NumOfBytes);
	string_cat(STRING2, NumOfBytes);
	string_cat(STRING2, "\r\n");
	do{
		UART_sendString(STRING2);
	}
	while(WaitForOk() == ERROR);
	_delay_ms(10);
	do{
		UART_sendString(STRING1);
	}
	while(WaitForOk() == ERROR);
	while(UART_recieveByte() != '?'){}
	while(SSID[count1] != '?'){
		SSID[count1] = UART_recieveByte();
		count1++;
	}
	count1 = 0;
	SSID[count1] = '\0';
	while(UART_recieveByte() != ' '){}
	while(Password[count1] != '?'){
		Password[count1] = UART_recieveByte();
		count1++;
	}
	count1 = 0;
	Password[count1] = '\0';
	while(UART_recieveByte() != ' '){}
	while(UserPhoneNumber[count1] != '?'){
		UserPhoneNumber[count1] = UART_recieveByte();
		count1++;
	}
	count1 = 0;
	UserPhoneNumber[count1] = '\0';
	while(UART_recieveByte() != ' '){}
	while(Distance[count1] != '?'){
		Distance[count1] = UART_recieveByte();
		count1++;
	}
	count1 = 0;
	Distance[count1] = '\0';
	if(string_length(Distance) == 3){
		DistanceThreshold = HighDistance;
	}
	else if(string_length(Distance) == 4){
		DistanceThreshold = LowDistance;
	}
	else{
		DistanceThreshold = MediumDistance;
	}
}

void EnableFirstUseMode(uint8 *FirstUseFlagPointer){
	eeprom_update_byte((uint8*)FirstUseFlagAddress, 0);
	*FirstUseFlagPointer = 0;
}

void FirstUseMode(uint8 *FirstUseFlagPointer){
	uint8 count = 0;
	uint8* count2 = FirstPhoneNumberAddress;
	ConnectToWebsite(URL);
	GetDataFromServer(URL);
	while(UserPhoneNumber[count] != '\0'){
		eeprom_update_byte(count2, UserPhoneNumber[count]);
		count ++;
		count2 ++;
	}
	eeprom_update_byte(DistanceThresholdAddress, DistanceThreshold);
	ESP_CONNECT_TO_AP(SSID, Password);
	eeprom_update_byte((uint8*)FirstUseFlagAddress, 1);
	*FirstUseFlagPointer = 1;
}

static void nodeMCUInit(void){
	//UARTConfig(ESP_BAUD_115200, ESP_PARITY_DISABLE, ESP_ONE_StopBit);
	TestModule();
	_delay_ms(100);
	DisableEcho();
	_delay_ms(100);
	AntennaPower("82");
	_delay_ms(100);
	WiFiMode(ESP_STA_AP);
	_delay_ms(100);
	WiFiAutoConnect(En_AutoConnect);
	_delay_ms(100);
}

void SystemInitiation(void){
	SET_BIT(DDRA,PA0);/*output control pin pin for Rxs relay(0 for MCU,1 for GSM)*/
	SET_BIT(DDRA,PA1);/*output control pin pin for Txs relay(0 for MCU,1 for GSM)*/
	SET_BIT(DDRA,PA2);/*output control pin for motor relay(0 for stop,1 for move)*/
	CLEAR_BIT(DDRD,PD2);/*INT0 bit,for RESET*/
	CLEAR_BIT(DDRD,PD3);/*INT1 bit,for closing valve*/
	CLEAR_BIT(DDRB,PB2);/*INT2 bit,for opening valve*/
	/*Next, initiating all ports to 0*/
	CLEAR_BIT(PORTA,PA0);
	CLEAR_BIT(PORTA,PA1);
	CLEAR_BIT(PORTA,PA2);
	/*INT0,INT1, and INT2 configueration*/
	SET_BIT(SREG, 7);
	SET_BIT(GICR, 7);
	SET_BIT(GICR, 6);
	SET_BIT(GICR, 5);
	SET_BIT(MCUCR, 0);
	SET_BIT(MCUCR, 1);
	SET_BIT(MCUCR, 2);
	SET_BIT(MCUCR, 3);
	SET_BIT(MCUCR, 6);
	UART_init();
	_delay_ms(1000);
	nodeMCUInit();
}

void CloseValve(void){

}

void OpenValve(void){

}
