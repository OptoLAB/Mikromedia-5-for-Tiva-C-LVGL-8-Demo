/*
 * CC3100.h
 *
 *  Created on: Dec 6, 2020
 *      Author: Jovan
 */

#ifndef CC3100_H
#define CC3100_H

#include <stdio.h>
#include <string.h>

#define SET_WIFI_CS			MAP_GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_4, GPIO_PIN_4)
#define CLR_WIFI_CS 		MAP_GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_4, 0)
#define SET_WIFI_nHIB		MAP_GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_5, GPIO_PIN_5)
#define CLR_WIFI_nHIB		MAP_GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_5, 0)
#define SET_WIFI_RST		//RST not wired
#define CLR_WIFI_RST		//RST not wired

#define WIFI_CLI_Write(x,y) SERIAL_Write(x,y)

typedef unsigned int Fd_t;

typedef void (*P_EVENT_HANDLER)(void* pValue);

#define ACLOCK_FREQ                     120000000                       // set to 120 [MHz]
#define TIMER_PRESCALAR		        	60000                           // value between 0 and 0xFFFF
#define TIMER_CLK                       (ACLOCK_FREQ/TIMER_PRESCALAR)   // timer frequency [Hz] or ticks/sec

#define MILLISECONDS_TO_TICKS(ms)       ((TIMER_CLK * ms)/1000)         // input: number of ms, output: number of ticks at given timer frequency
#define TICKS_TO_MILLISECONDS(ticks)    ((ticks)/(TIMER_CLK/1000))      // input: number of ticks, output: number of ms at given timer frequency
#define MAX_TIMER_TICKS                 0xFFFF                          // timer max count value OR timer period

void CC3100_Init(void);
void CC3100_Enable(void);
void CC3100_Disable(void);
void CC3100_InterruptEnable(void);
void CC3100_InterruptDisable(void);
//Timer
void CC3100_StartTimer(void);
void CC3100_TimerInc(void);
void CC3100_TimerReset(void);
unsigned long CC3100_GetCurrentTimestamp(void);
//Interrupt handler
int CC3100_RegisterInterruptHandler(P_EVENT_HANDLER InterruptHdl, void* pValue);
P_EVENT_HANDLER CC3100_GetInterruptHandler(void);
void CC3100_ResetInterruptHandler(void);
//SPI
Fd_t CC3100_SpiOpen(char *ifName, unsigned long flags);
int CC3100_SpiClose(Fd_t fd);
int CC3100_SpiWrite(Fd_t fd, unsigned char *pBuff, int len);
int CC3100_SpiRead(Fd_t fd, unsigned char *pBuff, int len);
//Command line interface
void CLI_Configure(void);
void CLI_Write(unsigned char *inBuff, ...);
int CLI_Read(unsigned char *pBuff);
int fputc(int ch, FILE *f);
// Delay function
void Delay(unsigned long delay);


#endif /* WIFI_CC3100_H_ */
