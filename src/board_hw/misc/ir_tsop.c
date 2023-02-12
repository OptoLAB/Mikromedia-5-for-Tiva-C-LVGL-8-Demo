/*
 * Author: J. Bajic, 2022.
 */

#include "board_hw/misc/nec_decoder.h"
#include "board_hw/misc/ir_tsop.h"
#include "board_hw/sys/sys_clk.h"
#include "board_hw/tivaware_c_lib.h"

void TSOP_Init(void)
{
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
    MAP_GPIOPinTypeGPIOInput(GPIO_PORTD_BASE, GPIO_INT_PIN_4);
    MAP_GPIOIntTypeSet(GPIO_PORTD_BASE, GPIO_INT_PIN_4, GPIO_FALLING_EDGE);
    MAP_IntEnable(INT_GPIOD);

    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
    MAP_TimerConfigure(TIMER0_BASE, TIMER_CFG_SPLIT_PAIR | TIMER_CFG_B_PERIODIC);
    MAP_TimerLoadSet(TIMER0_BASE, TIMER_B, SYSCLK_getClk() / 10000); //100us
    MAP_TimerEnable(TIMER0_BASE, TIMER_B);

    TSOP_NECdecoder_Start();
}

void TSOP_NECdecoder_Start(void)
{
    MAP_GPIOIntEnable(GPIO_PORTD_BASE, GPIO_INT_PIN_4);
    MAP_IntEnable(INT_TIMER0B);
    MAP_TimerIntEnable(TIMER0_BASE, TIMER_TIMB_TIMEOUT);
}

void TSOP_NECdecoder_Stop(void)
{
    MAP_GPIOIntDisable(GPIO_PORTD_BASE, GPIO_INT_PIN_4);
    MAP_IntDisable(INT_TIMER0B);
    MAP_TimerIntDisable(TIMER0_BASE, TIMER_TIMB_TIMEOUT);
    MAP_TimerIntClear(TIMER0_BASE, TIMER_TIMB_TIMEOUT);
}

void Timer0BIntHandler(void)
{
    MAP_TimerIntClear(TIMER0_BASE, TIMER_TIMB_TIMEOUT);
    NEC_TickInc(100);
}
void GPIODIntHandler(void)
{
    unsigned long intStatus;
    intStatus = MAP_GPIOIntStatus(GPIO_PORTD_BASE, 0);
    MAP_GPIOIntClear(GPIO_PORTD_BASE,intStatus);

    if(intStatus & GPIO_PIN_4)
    {
        if(NEC_Capture(NEC_GetTimer()))
            NEC_Decode();
        NEC_ResetTimer();
    }
}
