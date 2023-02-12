/*
 * rtc.h
 *
 *  Created on: Jan 18, 2023
 *      Author: Jovan
 */

#ifndef BOARD_HW_SYS_RTC_H_
#define BOARD_HW_SYS_RTC_H_

#include <stdint.h>
#include <stdbool.h>
#include <time.h>

void SYSRTC_Init(void);
int SYSRTC_GetDateTime(struct tm *psTime);
void SYSRTC_SetDateTime(struct tm *psTime);

#endif /* BOARD_HW_SYS_RTC_H_ */
