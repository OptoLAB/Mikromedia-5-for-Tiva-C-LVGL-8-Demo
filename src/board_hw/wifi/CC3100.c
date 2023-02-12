/*
 * CC3100.c
 *
 *  Created on: Dec 6, 2020
 *      Author: Jovan
 */

#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>

#include "CC3100.h"
#include "simplelink/include/simplelink.h"
#include "board_hw/comm/serial.h"
#include "board_hw/common/ssi1.h"
#include "board_hw/sys/sys_clk.h"
#include "board_hw/tivaware_c_lib.h"

char Buff[256];
char Temp[512];
P_EVENT_HANDLER     pIrqEventHandler = 0;
static volatile unsigned long cc3100_time_counter = 0;
uint8_t cc3100_timer_is_enabled=0;

void CC3100_Init(void)
{
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);

    MAP_GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE, GPIO_PIN_4);     // SPI CS
    MAP_GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_5);     // HIB/PWR
    MAP_GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_5, 0);            // HIB set low
    MAP_GPIOPinWrite(GPIO_PORTB_BASE,GPIO_PIN_4, GPIO_PIN_4);   // CS set high

    //CC3100 External Interrupt
    MAP_GPIOPinTypeGPIOInput(GPIO_PORTB_BASE, GPIO_INT_PIN_2);// INT
    MAP_GPIOIntTypeSet(GPIO_PORTB_BASE, GPIO_INT_PIN_2, GPIO_RISING_EDGE);
    MAP_IntEnable(INT_GPIOB);

    //CC3100 Timer
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER1);
    MAP_TimerConfigure(TIMER1_BASE, TIMER_CFG_SPLIT_PAIR | TIMER_CFG_B_PERIODIC);
    MAP_TimerLoadSet(TIMER1_BASE, TIMER_B, TIMER_PRESCALAR); //500us
    MAP_TimerEnable(TIMER1_BASE, TIMER_B);

    if(!SPI1_isInit())SPI1_Init(10000000);

    CLR_WIFI_RST;
    Delay(3);
    SET_WIFI_RST;
    Delay(1500);
}

// Timer interrupt handler
void Timer1BIntHandler(void)
{
    MAP_TimerIntClear(TIMER1_BASE, TIMER_TIMB_TIMEOUT);
    if (CC3100_GetCurrentTimestamp() < MAX_TIMER_TICKS)
    {
        CC3100_TimerInc();
    }
    else
    {
        CC3100_TimerReset();
    }
}

// External interrupt handler
void GPIOBIntHandler(void)
{
    unsigned long intStatus;
    intStatus = MAP_GPIOIntStatus(GPIO_PORTB_BASE, 0);
    MAP_GPIOIntClear(GPIO_PORTB_BASE,intStatus);

    if(intStatus & GPIO_PIN_2)
    {
        if(CC3100_GetInterruptHandler())
        {
           CC3100_ResetInterruptHandler();
        }
    }
}
// This function disables CC3100 device
void CC3100_Disable(void)
{
	CLR_WIFI_nHIB;
}

// This function enables CC3100 device
void CC3100_Enable(void)
{
	SET_WIFI_nHIB;
}

// This function enables IrQ pin
void CC3100_InterruptEnable(void)
{
    MAP_GPIOIntEnable(GPIO_PORTB_BASE,GPIO_PIN_2);
}

// This function disables IrQ pin
void CC3100_InterruptDisable(void)
{
    MAP_GPIOIntDisable(GPIO_PORTB_BASE,GPIO_PIN_2);
}

// Register interrupt handler
int CC3100_RegisterInterruptHandler(P_EVENT_HANDLER InterruptHdl , void* pValue)
{
    pIrqEventHandler = InterruptHdl;
    return 0;
}

// Get interrupt handler
P_EVENT_HANDLER CC3100_GetInterruptHandler(void)
{
    return pIrqEventHandler;
}

// Reset interrupt handler
void CC3100_ResetInterruptHandler(void)
{
	pIrqEventHandler(0);
}

// Start timer
void CC3100_StartTimer(void)
{
    cc3100_timer_is_enabled=1;          //Start CC3100 timer
    MAP_IntEnable(INT_TIMER1B);
    MAP_TimerIntEnable(TIMER1_BASE, TIMER_TIMB_TIMEOUT);
}
// Increment timer
void CC3100_TimerInc(void)
{
    cc3100_time_counter++;
}

// Reset timer
void CC3100_TimerReset(void)
{
    cc3100_time_counter=0;
}


// Returns the time stamp value for the SL host driver, should not be used by the application
unsigned long CC3100_GetCurrentTimestamp(void)
{
    if(!cc3100_timer_is_enabled) CC3100_StartTimer();

    return cc3100_time_counter;
}

// Open spi communication port to be used for communicating with a SimpleLink device
Fd_t CC3100_SpiOpen(char *ifName, unsigned long flags)
{
	// SPI initialized in CC3100_Init()
    SET_WIFI_CS;                // Set SPI CS
    CC3100_InterruptEnable();   // Enable CC3100 interrupt
    CC3100_Disable();           // disable the nHIB line
    Delay(50);

    return 0;
}

// Closes an opened spi communication port
int CC3100_SpiClose(Fd_t fd)
{
    CC3100_InterruptDisable();  // Disable CC3100 interrupt
    // Deinitialize SPI if needed
    return 0;
}

// Attempts to write up to len bytes to the SPI channel
int CC3100_SpiWrite(Fd_t fd, unsigned char *pBuff, int len)
{
    int len_to_return = len;

	CLR_WIFI_CS;
    while(len)
    {
        SPI1_WR(*pBuff);
        pBuff++;
        len--;
    }
    SET_WIFI_CS;

    return len_to_return;
}

// Attempts to read up to len bytes from SPI channel into a buffer starting at pBuff.
int CC3100_SpiRead(Fd_t fd, unsigned char *pBuff, int len)
{
    int len_to_return = len;

	CLR_WIFI_CS;
    while(len)
    {
        *pBuff=SPI1_WR(0xFF);
        pBuff++;
        len--;
    }
    SET_WIFI_CS;

    return len_to_return;
}


//command line (UART/CDC) interface configure
void CLI_Configure(void)
{
	//Initialize externally
}

//command line (UART/CDC) write data
void CLI_Write(unsigned char *pcFormat, ...)
{
    char *pcBuff = &Buff[0];
    char *pcTemp = &Temp[0];

    int iSize = 256;
    int iRet;

    memset(pcBuff, 0, 252);
    memset(pcTemp, 0, 512);

    va_list list;
    while(1)
    {
        va_start(list,pcFormat);
        iRet = vsnprintf(pcBuff,iSize,(char const *)pcFormat,list);
        va_end(list);
        if(iRet > -1 && iRet < iSize)
        {
          	WIFI_CLI_Write((uint8_t*)pcBuff, strlen((const char *)pcBuff));
            break;
        }
        else
        {
            iSize*=2;
            pcBuff=pcTemp;
        }
    }
}

//command line (UART/CDC) read data
int CLI_Read(unsigned char *pBuff)
{
	// Not implemented
    return 0;
}

//command line (UART/CDC) write file
int fputc(int ch, FILE *f)
{
	// Not implemented
    return 0;
}

// Induce delay in ms
void Delay(unsigned long delay)
{
    delayMS(delay);
}






