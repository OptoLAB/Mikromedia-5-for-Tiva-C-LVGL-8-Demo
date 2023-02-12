/*
 * Author: J. Bajic, 2022.
 */

#include "board_hw/sys/sys_clk.h"
#include "board_hw/tivaware_c_lib.h"

uint32_t ui32SysClock=120000000;

void SYSCLK_Config(uint32_t clk_freq)
{
    ui32SysClock = MAP_SysCtlClockFreqSet((SYSCTL_XTAL_25MHZ | SYSCTL_OSC_MAIN | SYSCTL_USE_PLL | SYSCTL_CFG_VCO_240), clk_freq);
}

uint32_t SYSCLK_getClk(void)
{
    return ui32SysClock;
}

void SYSTICK_Init(uint32_t period)
{
    MAP_SysTickPeriodSet(SYSCLK_getClk()/period);
    MAP_SysTickIntEnable();
    MAP_SysTickEnable();
}

void enableInterrupts(void)
{
    MAP_IntMasterEnable();
}

void disableInterrupts(void)
{
    MAP_IntMasterDisable();
}

void delayMS(uint16_t delay)
{
    while(delay--)
    {
        MAP_SysCtlDelay((ui32SysClock/1000)/3);
    }
}

void delayUS(uint16_t delay)
{
    while(delay--)
    {
        MAP_SysCtlDelay((ui32SysClock/1000000)/3);
    }
}
