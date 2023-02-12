/*
 * Author: J. Bajic, 2022.
 */

#ifndef BOARD_HW_RGB_LED_H_
#define BOARD_HW_RGB_LED_H_

#include <stdint.h>
#include <stdbool.h>

#define RLED 0
#define GLED 1
#define BLED 2

#define ON  1
#define OFF 0


void LEDs_Init(void);
void LEDs_Set(uint8_t rgb_led, uint8_t state);

#endif /* BOARD_HW_RGB_LED_H_ */
