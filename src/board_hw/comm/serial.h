/*
 * Author: J. Bajic, 2022.
 */

#ifndef BOARD_HW_SERIAL_H_
#define BOARD_HW_SERIAL_H_

#include <stdint.h>
#include <stdbool.h>

void SERIAL_Init(uint32_t baud_rate);
void SERIAL_Write(const uint8_t *data, uint32_t ui32Count);
uint32_t SERIAL_Read(uint8_t *data);

#endif /* BOARD_HW_SERIAL_H_ */
