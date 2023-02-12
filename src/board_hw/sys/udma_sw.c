/*
 * Author: J. Bajic, 2022.
 */

#include "board_hw/sys/udma_sw.h"
#include "board_hw/tivaware_c_lib.h"

uint8_t pui8ControlTable[1024] __attribute__ ((aligned(1024)));

void uDMA_Init(void)
{
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_UDMA);
    MAP_SysCtlPeripheralSleepEnable(SYSCTL_PERIPH_UDMA);
    MAP_IntEnable(INT_UDMAERR);
    MAP_uDMAEnable();
    MAP_uDMAControlBaseSet(pui8ControlTable);
    MAP_IntEnable(INT_UDMA);
    MAP_uDMAChannelAttributeDisable(UDMA_CHANNEL_SW, UDMA_ATTR_USEBURST | UDMA_ATTR_ALTSELECT |(UDMA_ATTR_HIGH_PRIORITY | UDMA_ATTR_REQMASK));
    MAP_uDMAChannelControlSet(UDMA_CHANNEL_SW | UDMA_PRI_SELECT, UDMA_SIZE_16 | UDMA_SRC_INC_16 | UDMA_DST_INC_16 | UDMA_NEXT_USEBURST);
}

void uDMA_Transfer(uint16_t *src, uint16_t *dest, uint32_t size)
{
    MAP_uDMAChannelTransferSet(UDMA_CHANNEL_SW, UDMA_MODE_AUTO, src, dest, size);
    MAP_uDMAChannelEnable(UDMA_CHANNEL_SW);
    MAP_uDMAChannelRequest(UDMA_CHANNEL_SW);
}

void uDMAErrorHandler(void)
{
    uint32_t ui32Status;

    // Check for uDMA error bit
    ui32Status = MAP_uDMAErrorStatusGet();
    // If there is a uDMA error, then clear the error
    if(ui32Status)
    {
        MAP_uDMAErrorStatusClear();

    }
}
