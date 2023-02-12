/*
 * Author: J. Bajic, 2022.
 */

#ifndef BOARD_HW_ACCEL_I2C2_H_
#define BOARD_HW_ACCEL_I2C2_H_

#include <stdint.h>
#include <stdbool.h>

#define I2C_STANDARD    false
#define I2C_FAST        true

void I2C2_Init(bool speed_mode);
uint8_t I2C2_isInit(void);
void I2C2_BusyWait(void);
void I2C2_Write(uint8_t slave_addr, uint8_t reg, uint8_t val);
uint8_t I2C2_Read1(uint8_t slave_addr, uint8_t reg);
void I2C2_Read(uint8_t slave_addr, uint8_t reg, uint8_t *data, uint16_t len);


#endif /* BOARD_HW_ACCEL_I2C2_H_ */
