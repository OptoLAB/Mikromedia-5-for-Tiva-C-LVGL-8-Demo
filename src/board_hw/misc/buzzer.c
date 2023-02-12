/*
 * buzzer.c
 *
 *  Created on: Jan 16, 2023
 *      Author: Jovan
 */

#include "board_hw/misc/buzzer.h"
#include "board_hw/tivaware_c_lib.h"
#include "board_hw/sys/sys_clk.h"


void BUZZER_Init(void)
{
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOM);
    MAP_GPIOPinConfigure(GPIO_PM7_T5CCP1);
    MAP_GPIOPinTypeTimer(GPIO_PORTM_BASE, GPIO_PIN_7);

    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER5);
    MAP_TimerConfigure(TIMER5_BASE, TIMER_CFG_SPLIT_PAIR | TIMER_CFG_B_PWM);
    MAP_TimerUpdateMode(TIMER5_BASE,TIMER_B,TIMER_UP_LOAD_IMMEDIATE | TIMER_UP_MATCH_IMMEDIATE);
}
void BUZZER_Start(void)
{
    MAP_TimerEnable(TIMER5_BASE, TIMER_B);
}

void BUZZER_Stop(void)
{
    MAP_TimerDisable(TIMER5_BASE, TIMER_B);
}

void BUZZER_SetVolume(uint8_t vol)
{
    uint32_t prd=MAP_TimerLoadGet(TIMER5_BASE,TIMER_B);
    MAP_TimerMatchSet(TIMER5_BASE,TIMER_B,prd*vol/100);
}
void BUZZER_SetFreq(uint32_t freq)
{
    uint32_t period=SYSCLK_getClk()/freq;
    MAP_TimerLoadSet(TIMER5_BASE,TIMER_B,period);
    MAP_TimerPrescaleSet(TIMER5_BASE, TIMER_B, period>>16); //prescaler acts as a timer extension and holds the most-significant bits
}

void BUZZER_ClickSound(void)
{
    BUZZER_SetFreq(2000);
    BUZZER_SetVolume(90);
    BUZZER_Start();
    delayMS(30);
    BUZZER_Stop();
}
