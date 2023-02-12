/*
 * Author: J. Bajic, 2022.
 */

#ifndef BOARD_HW_SYS_CLK_H_
#define BOARD_HW_SYS_CLK_H_

#include <stdint.h>
#include <stdbool.h>

void SYSCLK_Config(uint32_t clk_freq);
uint32_t SYSCLK_getClk(void);
void SYSTICK_Init(uint32_t period);
void enableInterrupts(void);
void disableInterrupts(void);
void delayMS(uint16_t delay);
void delayUS(uint16_t delay);

#endif /* BOARD_HW_SYS_CLK_H_ */
