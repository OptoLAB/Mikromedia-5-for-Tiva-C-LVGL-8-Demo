/*
 * Author: J. Bajic, 2022.
 */

#ifndef BOARD_HW_ACCEL_ADXL345_H_
#define BOARD_HW_ACCEL_ADXL345_H_

#include <stdint.h>
#include <stdbool.h>

//ADXL345 I2C address
#define ADXL345_ADDR           0x1D
//ADXL345 Register Definition
#define ADXL345_POWER_CTL      0x2D
#define ADXL345_DATA_FORMAT    0x31
#define ADXL345_BW_RATE        0x2C
#define ADXL345_DATAX0         0x32
#define ADXL345_DATAX1         0x33
#define ADXL345_DATAY0         0x34
#define ADXL345_DATAY1         0x35
#define ADXL345_DATAZ0         0x36
#define ADXL345_DATAZ1         0x37
#define ADXL345_FIFO_CTL       0x38
#define ADXL345_SPEED          0x0F

uint8_t ADXL345_Init(void);
uint16_t ADXL345_ReadX(void);
uint16_t ADXL345_ReadY(void);
uint16_t ADXL345_ReadZ(void);
void ADXL345_ReadXYZ(uint16_t *ax, uint16_t *ay, uint16_t *az);

#endif /* BOARD_HW_ACCEL_ADXL345_H_ */
