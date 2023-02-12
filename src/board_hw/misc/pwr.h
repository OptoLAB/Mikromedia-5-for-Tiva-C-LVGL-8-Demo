/*
 * pwr.h
 *
 *  Created on: Jan 21, 2023
 *      Author: Jovan
 */

#ifndef BOARD_HW_PWR_PWR_H_
#define BOARD_HW_PWR_PWR_H_


#include <stdint.h>
#include <stdbool.h>

//  LM3658
//  Table 1. Status Pins Summary
//  STAT1   STAT2
//  1       1   Power-Down, charging is suspended
//  0       1   CC and CV charging
//  1       0   Charge is completed
//  0       0   Bad battery (Safety timer expired) or LDO mode

typedef enum {
    PWR_DC,
    PWR_USB,
    PWR_BAT,
    PWR_BAT_CHRG,
    PWR_BAT_FLT,
} pwr_status;

#define USB_PWR_LO      MAP_GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_6, 0);
#define USB_PWR_HI      MAP_GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_6, GPIO_PIN_6);
#define USB_VBUS        MAP_GPIOPinRead(GPIO_PORTB_BASE, GPIO_PIN_1)
#define DC_VBUS         MAP_GPIOPinRead(GPIO_PORTN_BASE, GPIO_PIN_4)
#define BAT_STAT1       MAP_GPIOPinRead(GPIO_PORTQ_BASE, GPIO_PIN_6)
#define BAT_STAT2       MAP_GPIOPinRead(GPIO_PORTQ_BASE, GPIO_PIN_7)

void PWR_Init(void);
void PWR_USBEnable(void);
void PWR_USBDisable(void);
pwr_status PWR_GetStatus(uint16_t *bat_mV);

#endif /* BOARD_HW_PWR_PWR_H_ */
