/*
 * Author: J. Bajic, 2022.
 */

#ifndef BOARD_HW_COMM_SSI0_H_
#define BOARD_HW_COMM_SSI0_H_

#include <stdbool.h>
#include <stdint.h>

//SPI methods
#define SPI0_isInit()       SSI0_isInit()
#define SPI0_Init(x)        SSI0_Init(x)
#define SPI0_WR(x)          SSI0_WR(x)
#define SPI0_GetSpeed()     SSI0_GetSpeed()
#define SPI0_SetSpeed(x)    SSI0_SetSpeed(x)

void SSI0_Init(uint32_t speed);
uint8_t SSI0_isInit(void);
uint32_t SSI0_GetSpeed(void);
void SSI0_SetSpeed(uint32_t speed);
void SSI0_PutData(uint32_t data);
uint32_t SSI0_GetData(void);
bool SSI0_Busy(void);
int32_t SSI0_Flush(void);
uint8_t SSI0_WR(uint8_t data);

#endif /* BOARD_HW_COMM_SSI0_H_ */
