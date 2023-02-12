/*
 * Author: J. Bajic, 2022.
 */


#ifndef BOARD_HW_SYS_UDMA_SW_H_
#define BOARD_HW_SYS_UDMA_SW_H_

#include <stdint.h>
#include <stdbool.h>

void uDMA_Init(void);
void uDMA_Transfer(uint16_t *src, uint16_t *dest, uint32_t size);


#endif /* BOARD_HW_SYS_UDAM_SW_H_ */
