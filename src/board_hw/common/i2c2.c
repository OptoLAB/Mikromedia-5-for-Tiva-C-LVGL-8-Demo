/*
 * Author: J. Bajic, 2022.
 */

#include "board_hw/common/i2c2.h"
#include "board_hw/sys/sys_clk.h"
#include "board_hw/tivaware_c_lib.h"

uint8_t i2c2_init=0;

void I2C2_Init(bool speed_mode)
{

    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_I2C2);
    while(!MAP_SysCtlPeripheralReady(SYSCTL_PERIPH_I2C2));

    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOP);
    MAP_GPIOPinConfigure(GPIO_PP5_I2C2SCL);
    MAP_GPIOPinTypeI2CSCL(GPIO_PORTP_BASE, GPIO_PIN_5);
    MAP_GPIOPinConfigure(GPIO_PP6_I2C2SDA);
    MAP_GPIOPinTypeI2C(GPIO_PORTP_BASE, GPIO_PIN_6);

    MAP_I2CMasterInitExpClk(I2C2_BASE, SYSCLK_getClk(), speed_mode);
    MAP_I2CMasterEnable(I2C2_BASE);

    i2c2_init=1;
}
uint8_t I2C2_isInit(void)
{
    return i2c2_init;
}

void I2C2_BusyWait(void)
{
    while(!(MAP_I2CMasterBusy(I2C2_BASE)));
    while(MAP_I2CMasterBusy(I2C2_BASE));
}

void I2C2_Write(uint8_t slave_addr, uint8_t reg, uint8_t val)
{
    MAP_I2CMasterSlaveAddrSet(I2C2_BASE, slave_addr, false); //write

    MAP_I2CMasterDataPut(I2C2_BASE, reg);
    MAP_I2CMasterControl(I2C2_BASE, I2C_MASTER_CMD_BURST_SEND_START);
    I2C2_BusyWait();

    MAP_I2CMasterDataPut(I2C2_BASE, val);
    MAP_I2CMasterControl(I2C2_BASE, I2C_MASTER_CMD_BURST_SEND_FINISH);
    I2C2_BusyWait();
}

void I2C2_Read(uint8_t slave_addr, uint8_t reg, uint8_t *data, uint16_t len)
{
    uint8_t i=0;

    MAP_I2CMasterSlaveAddrSet(I2C2_BASE, slave_addr, false); //write

    MAP_I2CMasterDataPut(I2C2_BASE, reg);
    MAP_I2CMasterControl(I2C2_BASE, I2C_MASTER_CMD_SINGLE_SEND);
    I2C2_BusyWait();

    MAP_I2CMasterSlaveAddrSet(I2C2_BASE, slave_addr, true); //read

    if(len>1)//burst
    {
        MAP_I2CMasterControl(I2C2_BASE, I2C_MASTER_CMD_BURST_RECEIVE_START);
        I2C2_BusyWait();
        data[0]=MAP_I2CMasterDataGet(I2C2_BASE);

        for(i=1;i<(len-1);i++)
        {
            MAP_I2CMasterControl(I2C2_BASE, I2C_MASTER_CMD_BURST_RECEIVE_CONT);
            I2C2_BusyWait();
            data[i]=MAP_I2CMasterDataGet(I2C2_BASE);
        }

        MAP_I2CMasterControl(I2C2_BASE, I2C_MASTER_CMD_BURST_RECEIVE_FINISH);
        I2C2_BusyWait();
        data[len-1]=MAP_I2CMasterDataGet(I2C2_BASE);
    }
    else//single
    {
        MAP_I2CMasterControl(I2C2_BASE, I2C_MASTER_CMD_SINGLE_RECEIVE);
        I2C2_BusyWait();
        data[0] = MAP_I2CMasterDataGet(I2C2_BASE);
    }
}
