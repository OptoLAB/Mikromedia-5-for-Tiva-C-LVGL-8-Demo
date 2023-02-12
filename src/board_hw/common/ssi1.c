/*
 * Author: J. Bajic, 2022.
 */
#include "board_hw/common/ssi1.h"
#include "board_hw/tivaware_c_lib.h"
#include "board_hw/sys/sys_clk.h"

uint8_t ssi1_init=0;
uint32_t ssi1_speed=1000000;

void SSI1_Init(uint32_t speed)
{
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_SSI1);
    while(!MAP_SysCtlPeripheralReady(SYSCTL_PERIPH_SSI1));

    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);

    MAP_GPIOPinConfigure(GPIO_PE4_SSI1XDAT0);               // Configure the GPIO Pin Mux for PE4 for SSI1XDAT0 - SPI MOSI
    MAP_GPIOPinTypeSSI(GPIO_PORTE_BASE, GPIO_PIN_4);

    MAP_GPIOPinConfigure(GPIO_PE5_SSI1XDAT1);               // Configure the GPIO Pin Mux for PE5 for SSI1XDAT1 - SPI MISO
    MAP_GPIOPinTypeSSI(GPIO_PORTE_BASE, GPIO_PIN_5);

    MAP_GPIOPinConfigure(GPIO_PB5_SSI1CLK);                 // Configure the GPIO Pin Mux for PB5 for SSI1CLK   - SPI CLK
    MAP_GPIOPinTypeSSI(GPIO_PORTB_BASE, GPIO_PIN_5);

    ssi1_init=1;//initialized
    //CS (SS) is configured within each peripheral separatelly
    ssi1_speed=speed;
    MAP_SSIConfigSetExpClk(SSI1_BASE, SYSCLK_getClk(), SSI_FRF_MOTO_MODE_0, SSI_MODE_MASTER, ssi1_speed, 8);//SysCtlClockGet()
    MAP_SSIEnable(SSI1_BASE);
}

uint8_t SSI1_isInit(void)
{
    return ssi1_init;
}

uint32_t SSI1_GetSpeed(void)
{
    return ssi1_speed;
}
void SSI1_SetSpeed(uint32_t speed)
{
    MAP_SSIDisable(SSI1_BASE);
    ssi1_speed=speed;
    MAP_SSIConfigSetExpClk(SSI1_BASE, SYSCLK_getClk(), SSI_FRF_MOTO_MODE_0, SSI_MODE_MASTER, ssi1_speed, 8);
    MAP_SSIEnable(SSI1_BASE);
}

void SSI1_PutData(uint32_t data)
{
    MAP_SSIDataPut(SSI1_BASE, data);
}

uint32_t SSI1_GetData(void)
{
   uint32_t data;

   MAP_SSIDataGet(SSI1_BASE, &data);

   return data;
}

bool SSI1_Busy(void)
{
    return MAP_SSIBusy(SSI1_BASE);
}

int32_t SSI1_Flush(void)
{
    uint32_t data;
    return MAP_SSIDataGetNonBlocking(SSI1_BASE,&data);
}

uint8_t SSI1_WR(uint8_t data)
{
    SSI1_PutData(data);
    data=SSI1_GetData();
    while(SSI1_Busy());

    return data;
}

