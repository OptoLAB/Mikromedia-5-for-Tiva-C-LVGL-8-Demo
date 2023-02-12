/*
 * Author: J. Bajic, 2022.
 */

#ifndef BOARD_HW_COMM_SSI1_H_
#define BOARD_HW_COMM_SSI1_H_

#include <stdbool.h>
#include <stdint.h>

//SPI methods
#define SPI1_isInit()       SSI1_isInit()
#define SPI1_Init(x)        SSI1_Init(x)
#define SPI1_WR(x)          SSI1_WR(x)
#define SPI1_GetSpeed()     SSI1_GetSpeed()
#define SPI1_SetSpeed(x)    SSI1_SetSpeed(x)

void SSI1_Init(uint32_t speed);
uint8_t SSI1_isInit(void);
uint32_t SSI1_GetSpeed(void);
void SSI1_SetSpeed(uint32_t speed);
void SSI1_PutData(uint32_t data);
uint32_t SSI1_GetData(void);
bool SSI1_Busy(void);
int32_t SSI1_Flush(void);
uint8_t SSI1_WR(uint8_t data);

#endif /* BOARD_HW_COMM_SSI1_H_ */
