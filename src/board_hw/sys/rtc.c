/*
 * rtc.c
 *
 *  Created on: Jan 18, 2023
 *      Author: Jovan
 */
#include "board_hw/sys/rtc.h"
#include "board_hw/tivaware_c_lib.h"


void SYSRTC_Init(void)
{
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_HIBERNATE);
    //MAP_HibernateEnableExpClk(0);
    MAP_HibernateClockConfig(HIBERNATE_OSC_LOWDRIVE);
    MAP_HibernateRTCEnable();
    MAP_HibernateCounterMode(HIBERNATE_COUNTER_24HR);
}

int SYSRTC_GetDateTime(struct tm *psTime)
{
    return MAP_HibernateCalendarGet(psTime);
}

void SYSRTC_SetDateTime(struct tm *psTime)
{
    MAP_HibernateCalendarSet(psTime);
}
