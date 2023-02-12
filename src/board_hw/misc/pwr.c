/*
 * pwr.c
 *
 *  Created on: Jan 21, 2023
 *      Author: Jovan
 */



#include "board_hw/misc/pwr.h"
#include "board_hw/misc/sensors_adc.h"
#include "board_hw/tivaware_c_lib.h"

uint8_t usb_pwr_stat=0;

void PWR_Init(void)
{
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOQ);
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPION);
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);


    MAP_GPIOPinTypeGPIOOutput(GPIO_PORTD_BASE, GPIO_PIN_6); //USB-PWR

    MAP_GPIOPinTypeGPIOInput(GPIO_PORTB_BASE, GPIO_PIN_1);  //USB-VBUS, always ON if USB_PWR_LO
    MAP_GPIOPinTypeGPIOInput(GPIO_PORTN_BASE, GPIO_PIN_4);  //DC-VBUS
    MAP_GPIOPinTypeGPIOInput(GPIO_PORTQ_BASE, GPIO_PIN_6|GPIO_PIN_7); //BAT-STAT1, BAT-STAT2, BAT-STAT1 changes only upon power reset

    PWR_USBDisable();
}

//Enables power on USB connector
void PWR_USBEnable(void)
{
    usb_pwr_stat=1;
    USB_PWR_LO;
}

//Disables power on USB connector
void PWR_USBDisable(void)
{
    usb_pwr_stat=0;
    USB_PWR_HI;
}

//Returns power source (DC, USB, BAT) and battery sense voltage
pwr_status PWR_GetStatus(uint16_t *bat_mV)
{
    pwr_status stat;

    ADCSensors_Read();
    *bat_mV=(uint16_t)(ADCSensors_getBatteryV()*1000);

    if(!DC_VBUS)
    {
        if(*bat_mV>4500)               //>4.5V
            stat=PWR_DC;                //only DC bus
        else
            stat=PWR_BAT_CHRG;            //battery present and charging over DC
    }
    else
    {
        if(usb_pwr_stat)
        {
            if(!BAT_STAT1)
            {
                if(*bat_mV>4500)        //>4.5V
                    stat=PWR_USB;       //only USB
                else
                    stat=PWR_BAT_CHRG;   //battery present and charging over USB
            }
            else
                stat=PWR_BAT;           //only battery present
        }
        else
        {
            if(USB_VBUS)
            {
                if(*bat_mV>4500)        //>4.5V
                    stat=PWR_USB;       //only USB
                else
                    stat=PWR_BAT_CHRG;   //battery present and charging over USB
            }
            else
                stat=PWR_BAT;           //only battery present
        }

    }

    if(!BAT_STAT1 && !BAT_STAT2)stat=PWR_BAT_FLT;

    return stat;
}
