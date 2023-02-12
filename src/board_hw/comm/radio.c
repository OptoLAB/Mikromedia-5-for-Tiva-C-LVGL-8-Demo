/*
 * Author: J. Bajic, 2022.
 */

#include "board_hw/comm/radio.h"
#include "board_hw/comm/nrf24.h"
#include "board_hw/misc/rgb_led.h"

#define PAYLOAD_LENGTH  32

const uint8_t nRF24_TX_ADDR[] = "00001";
const uint8_t nRF24_RX_ADDR[] = "00002";

void RADIO_Init(void)
{
    nRF24_Init();

    nRF24_LowerSpiSpeed();

    nRF24_DisableAA(0xFF);
    nRF24_SetRFChannel(115);
    nRF24_SetDataRate(nRF24_DR_1Mbps);
    nRF24_SetCRCScheme(nRF24_CRC_1byte);
    nRF24_SetAddrWidth(5);
    nRF24_SetAddr(nRF24_PIPETX, nRF24_TX_ADDR); // program TX address
    nRF24_SetAddr(nRF24_PIPE1, nRF24_RX_ADDR); // program address for RX pipe #1
    nRF24_SetRXPipe(nRF24_PIPE1, nRF24_AA_OFF, PAYLOAD_LENGTH); // Auto-ACK: disabled, payload length: 5 bytes
    nRF24_SetTXPower(nRF24_TXPWR_0dBm);
    nRF24_SetOperationalMode(nRF24_MODE_RX);
    nRF24_ClearIRQFlags();
    nRF24_SetPowerMode(nRF24_PWR_UP);
    nRF24_CE_HI();

    nRF24_ReturnSpiSpeed();
}

uint8_t RADIO_Transmit(uint8_t *data, uint32_t ui32Count)
{
   uint8_t i, n, status=0;

   n=ui32Count/PAYLOAD_LENGTH;
   if(ui32Count%PAYLOAD_LENGTH)n+=1;

   nRF24_SetOperationalMode(nRF24_MODE_TX); //switch tx mode
   nRF24_CE_LO();

   for(i=0;i<n;i++)
   {
       status=nRF24_TransmitPacket(data+(i<<5), PAYLOAD_LENGTH);
   }

   nRF24_SetOperationalMode(nRF24_MODE_RX); //switch back to rx mode
   nRF24_CE_HI();

   return status;
}

uint32_t RADIO_Receive(uint8_t *data)
{
    uint8_t len=0;

    if (nRF24_GetStatus_RXFIFO() != nRF24_STATUS_RXFIFO_EMPTY)
    {
        nRF24_ReadPayloadDpl(data, &len);
        nRF24_ClearIRQFlags();

        return len;
    }
    else return 0;

}
