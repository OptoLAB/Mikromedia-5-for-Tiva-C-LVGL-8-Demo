/*
 * Author: J. Bajic, 2022.
 */

#include "board_hw/touch/TSC2006.h"
#include "board_hw/common/ssi1.h"
#include "board_hw/sys/sys_clk.h"
#include "board_hw/tivaware_c_lib.h"

//Check datasheet
#define TSC2006_CFR0_VALUE  0b1010110010010001
#define TSC2006_CFR1_VALUE  0b0000000000000010
#define TSC2006_CFR2_VALUE  0b0100000000000000

//CS
#define TSC2006_CS_LO()     MAP_GPIOPinWrite(GPIO_PORTJ_BASE, GPIO_PIN_7, 0)
#define TSC2006_CS_HI()     MAP_GPIOPinWrite(GPIO_PORTJ_BASE, GPIO_PIN_7, GPIO_PIN_7)

//RST
#define TSC2006_RST_LO()    MAP_GPIOPinWrite(GPIO_PORTH_BASE, GPIO_PIN_5, 0)
#define TSC2006_RST_HI()    MAP_GPIOPinWrite(GPIO_PORTH_BASE, GPIO_PIN_5, GPIO_PIN_5)

//display size
#define DISPLAY_WIDTH   800
#define DISPLAY_HEIGHT  480
//measured
#define TOUCH_X_MAX 3900
#define TOUCH_X_MIN 150
#define TOUCH_Y_MAX 3850
#define TOUCH_Y_MIN 260

static void TSC2006_InitGPIO(void)
{
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOH);
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOJ);

    MAP_GPIOPinTypeGPIOOutput(GPIO_PORTH_BASE, GPIO_PIN_5);     // Configure the GPIO Pin Mux for PH5 for GPIO_PH5 - TouchControler RST
    MAP_GPIOPinTypeGPIOOutput(GPIO_PORTJ_BASE, GPIO_PIN_7);     // Configure the GPIO Pin Mux for PJ7 for GPIO_PJ7  - TouchControler SPI CS

    MAP_GPIOPinWrite(GPIO_PORTH_BASE, GPIO_PIN_5, GPIO_PIN_5);  //RST pin High
    MAP_GPIOPinWrite(GPIO_PORTJ_BASE, GPIO_PIN_7, GPIO_PIN_7);  // CS High
}

static void TSC2006_HwReset(void)
{
    TSC2006_RST_LO();
    delayMS(10);
    TSC2006_RST_HI();
}
static void TSC2006_WriteCmd(uint8_t reg)
{
    TSC2006_CS_LO();

    SPI1_WR(TSC2006_CMD|reg);

    TSC2006_CS_HI();
}

static void TSC2006_WriteReg(uint8_t reg, uint16_t value)
{
    TSC2006_CS_LO();

    SPI1_WR(TSC2006_REG_WRITE|reg);
    SPI1_WR(value>>8);
    SPI1_WR(value);

    TSC2006_CS_HI();
}

static uint16_t TSC2006_ReadReg(uint8_t reg)
{
    uint32_t rx_data[2]={};

    TSC2006_CS_LO();

    SPI1_WR(TSC2006_REG_READ|reg);
    rx_data[0]=SPI1_WR(0);
    rx_data[1]=SPI1_WR(0);

    TSC2006_CS_HI();

    return ((rx_data[0]<<8)+rx_data[1]);
}

void TSC2006_Init(void)
{

    TSC2006_InitGPIO();
    if(!SPI1_isInit())SPI1_Init(10000000);

    delayMS(10);
    TSC2006_HwReset();
    delayMS(10);

    TSC2006_WriteCmd(TSC2006_CMD_SWRST);
    TSC2006_WriteCmd(TSC2006_CMD_STOP);
    TSC2006_WriteReg(TSC2006_REG_CFR0, TSC2006_CFR0_VALUE);
    TSC2006_WriteReg(TSC2006_REG_CFR1, TSC2006_CFR1_VALUE);
    TSC2006_WriteReg(TSC2006_REG_CFR2, TSC2006_CFR2_VALUE);
    TSC2006_WriteCmd(TSC2006_CMD_12BIT|TSC2006_CMD_XY_SCAN);
}

uint16_t TSC2006_readX(void)
{
    return TSC2006_ReadReg(TSC2006_REG_X);

}

uint16_t TSC2006_readY(void)
{
    return TSC2006_ReadReg(TSC2006_REG_Y);

}

uint16_t TSC2006_readCFR0(void)
{
    return TSC2006_ReadReg(TSC2006_REG_CFR0);

}

uint16_t TSC2006_isPressed()
{
    if(TSC2006_readCFR0()&0x8000)
        return 1;
    else
        return 0;
}

void TSC2006_readXYCalibrated(uint16_t *x_coord, uint16_t *y_coord)
{
    *x_coord=TSC2006_readX();
    *y_coord=TSC2006_readY();

    *x_coord=DISPLAY_WIDTH*(*x_coord-TOUCH_X_MIN)/(TOUCH_X_MAX-TOUCH_X_MIN);
    *y_coord=DISPLAY_HEIGHT*(*y_coord-TOUCH_Y_MIN)/(TOUCH_Y_MAX-TOUCH_Y_MIN);
}

