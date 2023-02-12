/*
 * Author: J. Bajic, 2022.
 */

#ifndef BOARD_HW_DISPLAY_DISPLAY_H_
#define BOARD_HW_DISPLAY_DISPLAY_H_

#include <stdint.h>
#include <stdbool.h>

#define DISPLAY_EN_PINGPONG     0
#define DISPLAY_EN_INTERRUPT    0

uint32_t *DISPLAY_getFrameBufferAddress(void);
void DISPLAY_Init(void);

#endif /* BOARD_HW_DISPLAY_DISPLAY_H_ */
