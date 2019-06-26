/*
 * ApplicationCode.h
 *
 *  Created on: 22 Jun 2019
 *      Author: Yahia
 */

#ifndef APPLICATIONCODE_H_
#define APPLICATIONCODE_H_

#include <avr/eeprom.h>
#include "micro_config.h"
#include "uart.h"
#include "DIO.h"
#include "TIMER.h"
#include "nodeMCU.h"

#ifndef LowDistance
#define LowDistance 0
#endif

#ifndef MediumDistance
#define MediumDistance 1
#endif

#ifndef HighDistance
#define HighDistance 2
#endif

static void GetPhoneNum(uint8 PhoneNum[]);
void EnterNumberOfUser(void);
void GSM_sendmessage(uint8 message[]);
void GetDataFromServer(uint8 URL[]);
void EnableFirstUseMode(uint8 *FirstUseFlagPointer);
void FirstUseMode(uint8 *FirstUseFlagPointer);
void CloseValve(void);
void OpenValve(void);
void SystemInitiation(void);
static void nodeMCUInit(void);

#endif /* APPLICATIONCODE_H_ */
