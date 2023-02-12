/*
 * Author: J. Bajic, 2022.
 */


#include "board_hw/common/ssi0.h"
#include "board_hw/tivaware_c_lib.h"
#include "board_hw/sys/sys_clk.h"

uint8_t ssi0_init=0;
uint32_t ssi0_speed=1000000;

void SSI0_Init(uint32_t speed)
{
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_SSI0);
    while(!MAP_SysCtlPeripheralReady(SYSCTL_PERIPH_SSI0));

    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

    MAP_GPIOPinConfigure(GPIO_PA4_SSI0XDAT0);               // Configure the GPIO Pin Mux for PA4 for SSI0XDAT0 - SPI MOSI
    MAP_GPIOPinTypeSSI(GPIO_PORTA_BASE, GPIO_PIN_4);

    MAP_GPIOPinConfigure(GPIO_PA5_SSI0XDAT1);               // Configure the GPIO Pin Mux for PA5 for SSI0XDAT1 - SPI MISO
    MAP_GPIOPinTypeSSI(GPIO_PORTA_BASE, GPIO_PIN_5);

    MAP_GPIOPinConfigure(GPIO_PA2_SSI0CLK);                 // Configure the GPIO Pin Mux for PA2 for SSI0CLK - SPI CLK
    MAP_GPIOPinTypeSSI(GPIO_PORTA_BASE, GPIO_PIN_2);

    ssi0_init=1;//initialized
    //CS (SS) is configured within each peripheral separatelly
    ssi0_speed=speed;
    MAP_SSIConfigSetExpClk(SSI0_BASE, SYSCLK_getClk(), SSI_FRF_MOTO_MODE_0, SSI_MODE_MASTER, ssi0_speed, 8);//SysCtlClockGet()
    MAP_SSIEnable(SSI0_BASE);
}

uint8_t SSI0_isInit(void)
{
    return ssi0_init;
}

uint32_t SSI0_GetSpeed(void)
{
    return ssi0_speed;
}
void SSI0_SetSpeed(uint32_t speed)
{
    unsigned long tmp;

    MAP_SSIDisable(SSI0_BASE);
    ssi0_speed=speed;
    MAP_SSIConfigSetExpClk(SSI0_BASE, SYSCLK_getClk(), SSI_FRF_MOTO_MODE_0, SSI_MODE_MASTER, ssi0_speed, 8);
    MAP_SSIEnable(SSI0_BASE);
    while(SSIDataGetNonBlocking(SSI0_BASE, &tmp) != 0);
}

void SSI0_PutData(uint32_t data)
{
    MAP_SSIDataPut(SSI0_BASE, data);
}

uint32_t SSI0_GetData(void)
{
   uint32_t data;

   MAP_SSIDataGet(SSI0_BASE, &data);

   return data;
}

bool SSI0_Busy(void)
{
    return MAP_SSIBusy(SSI0_BASE);
}

int32_t SSI0_Flush(void)
{
    uint32_t data;
    return MAP_SSIDataGetNonBlocking(SSI0_BASE,&data);
}

uint8_t SSI0_WR(uint8_t data)
{
    SSI0_PutData(data);
    data=SSI0_GetData();
    while(SSI0_Busy());

    return data;
}

