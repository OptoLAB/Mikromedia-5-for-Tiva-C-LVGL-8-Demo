/*
 * Author: J. Bajic, 2022.
 */

#include "board_hw/accel/ADXL345.h"
#include "board_hw/common/i2c2.h"
#include "board_hw/sys/sys_clk.h"

uint8_t ADXL345_Init(void)
{
    uint8_t id=0;
    if(!I2C2_isInit())I2C2_Init(I2C_FAST);
    delayMS(100);
    I2C2_Write(ADXL345_ADDR, ADXL345_POWER_CTL,0x00);
    I2C2_Read(ADXL345_ADDR,0x00,&id,1);

    I2C2_Write(ADXL345_ADDR,ADXL345_DATA_FORMAT,0x08);       // Full resolution, +/-2g, 4mg/LSB, right justified
    I2C2_Write(ADXL345_ADDR,ADXL345_BW_RATE,0x0A);           // Set 100 Hz data rate
    I2C2_Write(ADXL345_ADDR,ADXL345_FIFO_CTL,0x80);          // stream mode
    I2C2_Write(ADXL345_ADDR,ADXL345_POWER_CTL,0x08);         // POWER_CTL reg: measurement mode

    if(id==0xE5)
      return id;
    else
      return 0;
}

uint16_t ADXL345_ReadX(void)
{
    uint8_t data[2]={};

    I2C2_Read(ADXL345_ADDR, ADXL345_DATAX0, data, 2);

    return (data[0] + (data[1] << 8));
}

uint16_t ADXL345_ReadY(void)
{
    uint8_t data[2]={};

    I2C2_Read(ADXL345_ADDR, ADXL345_DATAY0, data, 2);

    return (data[0] + (data[1] << 8));
}

uint16_t ADXL345_ReadZ(void)
{
    uint8_t data[2]={};

    I2C2_Read(ADXL345_ADDR, ADXL345_DATAZ0, data, 2);

    return (data[0] + (data[1] << 8));
}

void ADXL345_ReadXYZ(uint16_t *ax, uint16_t *ay, uint16_t *az)
{
    uint8_t data[6]={};

    I2C2_Read(ADXL345_ADDR, ADXL345_DATAX0, data, 6);

    *ax = data[0] + (data[1] << 8);
    *ay = data[2] + (data[3] << 8);
    *az = data[4] + (data[5] << 8);
}

