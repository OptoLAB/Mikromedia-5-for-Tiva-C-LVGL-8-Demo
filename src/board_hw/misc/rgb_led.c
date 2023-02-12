/*
 * Author: J. Bajic, 2022.
 */

#include "board_hw/misc/rgb_led.h"
#include "board_hw/tivaware_c_lib.h"

void LEDs_Init(void)
{
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);        // Enable Peripheral Clocks
    MAP_GPIOPinTypeGPIOOutput(GPIO_PORTD_BASE, GPIO_PIN_2); // Configure the GPIO Pin Mux for PD2---------------------->RED
    MAP_GPIOPinTypeGPIOOutput(GPIO_PORTD_BASE, GPIO_PIN_3); // Configure the GPIO Pin Mux for PD3---------------------->GREEN
    MAP_GPIOPinTypeGPIOOutput(GPIO_PORTD_BASE, GPIO_PIN_5); // Configure the GPIO Pin Mux for PD5---------------------->BLUE
    //All OFF
    MAP_GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_2, 0x0);
    MAP_GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_3, 0x0);
    MAP_GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_3, 0x0);
}

void LEDs_Set(uint8_t rgb_led, uint8_t state)
{
    switch(rgb_led)
    {
        case RLED:
            if(state) MAP_GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_2, GPIO_PIN_2);
            else MAP_GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_2, 0x0);
            break;
        case GLED:
            if(state) MAP_GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_3, GPIO_PIN_3);
            else MAP_GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_3, 0x0);
            break;
        case BLED:
            if(state) MAP_GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_5, GPIO_PIN_5);
            else MAP_GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_5, 0x0);
            break;
    }
}
