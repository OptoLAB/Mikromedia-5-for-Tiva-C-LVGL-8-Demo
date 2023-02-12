/*
 * Author: J. Bajic, 2022.
 */

#ifndef BOARD_HW_NRF_RADIO_H_
#define BOARD_HW_NRF_RADIO_H_

#include <stdbool.h>
#include <stdint.h>

void RADIO_Init(void);
uint8_t RADIO_Transmit(uint8_t *data, uint32_t ui32Count);
uint32_t RADIO_Receive(uint8_t *data);

#endif /* BOARD_HW_NRF_RADIO_H_ */
