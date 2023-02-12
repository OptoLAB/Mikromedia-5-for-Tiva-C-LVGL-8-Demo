/*
 * Author: J. Bajic, 2022.
 */

#ifndef BOARD_HW_BOARD_HW_H_
#define BOARD_HW_BOARD_HW_H_

#include "board_hw/sys/sys_clk.h"
#include "board_hw/common/i2c2.h"
#include "board_hw/common/ssi1.h"
#include "board_hw/misc/rgb_led.h"
#include "board_hw/misc/sensors_adc.h"
#include "board_hw/comm/serial.h"
#include "board_hw/comm/rw_json.h"
#include "board_hw/accel/ADXL345.h"
#include "board_hw/display/display.h"
#include "board_hw/touch/TSC2006.h"
#include "board_hw/comm/nrf24.h"
#include "board_hw/comm/radio.h"
#include "board_hw/misc/ir_tsop.h"
#include "board_hw/misc/nec_decoder.h"
#include "board_hw/misc/buzzer.h"
#include "board_hw/sys/rtc.h"
#include "board_hw/wifi/CC3100.h"
#include "board_hw/wifi/wifi_weather_demo.h"
#include "board_hw/sd/fatfs_sd.h"
#include "board_hw/mp3/VS1053.h"
#include "board_hw/mp3/MP3.h"
#include "board_hw/misc/pwr.h"
#include "board_hw/sys/udma_sw.h"

void BOARD_HW_Init(void);

#endif /* BOARD_HW_BOARD_HW_H_ */
