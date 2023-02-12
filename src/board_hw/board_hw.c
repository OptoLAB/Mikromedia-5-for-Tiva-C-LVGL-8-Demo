/*
 * Author: J. Bajic, 2022.
 */

#include "board_hw/board_hw.h"
#include "board_hw/tivaware_c_lib.h"
#include <string.h>


void BOARD_HW_Init(void)
{
    disableInterrupts();

    SYSCLK_Config(120000000);
    SYSTICK_Init(1000);
    LEDs_Init();
    ADCSensors_Init();
    SERIAL_Init(115200);
    ADXL345_Init();
    DISPLAY_Init();
    TSC2006_Init();
    uDMA_Init();
    RADIO_Init();
    TSOP_Init();
    BUZZER_Init();
    SYSRTC_Init();
    CC3100_Init();
    SD_Init();
    VS1053_Init();
    PWR_Init();

    enableInterrupts();
}
