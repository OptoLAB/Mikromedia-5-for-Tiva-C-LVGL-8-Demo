/*
 * Author: J. Bajic, 2022.
 */

#include "board_hw/comm/serial.h"
#include "board_hw/tivaware_c_lib.h"
#include "board_hw/sys/sys_clk.h"

#define RX_BUFFER_SIZE  128
#define RX_TERMINATION_CHAR 0x0A

uint8_t rx_buffer[RX_BUFFER_SIZE]={};
uint32_t rx_buffer_ptr=0;
uint32_t num_of_rx_bytes=0;

void SERIAL_Init(uint32_t baud_rate)
{

    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOK);
    MAP_GPIOPinConfigure(GPIO_PK0_U4RX);
    MAP_GPIOPinTypeUART(GPIO_PORTK_BASE, GPIO_PIN_0);   // Configure the GPIO Pin Mux for PK0 for U4RX
    MAP_GPIOPinConfigure(GPIO_PK1_U4TX);                // Configure the GPIO Pin Mux for PK1 for U4TX
    MAP_GPIOPinTypeUART(GPIO_PORTK_BASE, GPIO_PIN_1);

    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_UART4);
    MAP_UARTConfigSetExpClk(UART4_BASE, SYSCLK_getClk(), baud_rate, (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));

    MAP_UARTIntEnable(UART4_BASE, UART_INT_RX | UART_INT_RT);
    MAP_IntPrioritySet(INT_UART4, 5);
    MAP_IntEnable(INT_UART4);

    MAP_UARTEnable(UART4_BASE);
}

void SERIAL_Write(const uint8_t *data, uint32_t ui32Count)
{
    while(ui32Count--)
    {
        while(MAP_UARTBusy(UART4_BASE));
        MAP_UARTCharPut(UART4_BASE, *data++);


    }
}

uint32_t SERIAL_Read(uint8_t *data)
{
    uint32_t ui32Count=0;

    for(ui32Count=0; ui32Count<num_of_rx_bytes; ui32Count++)
    {
        data[ui32Count]=rx_buffer[ui32Count];
    }
    num_of_rx_bytes=0;

    return ui32Count;
}

void UART4IntHandler(void)
{
    uint32_t ui32Status;

    ui32Status = MAP_UARTIntStatus(UART4_BASE, false);
    MAP_UARTIntClear(UART4_BASE, ui32Status);

    if(!num_of_rx_bytes)
    {
        while(MAP_UARTCharsAvail(UART4_BASE))
        {
            rx_buffer[rx_buffer_ptr]=MAP_UARTCharGetNonBlocking(UART4_BASE);
            if(rx_buffer[rx_buffer_ptr]==RX_TERMINATION_CHAR)
            {
                num_of_rx_bytes=rx_buffer_ptr+1;
                rx_buffer_ptr=0;
            }
            else rx_buffer_ptr++;
        }
    }
}



