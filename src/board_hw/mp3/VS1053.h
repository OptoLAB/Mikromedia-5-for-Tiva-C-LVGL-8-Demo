/*
J. Bajic - 2018.
*/

#ifndef VS1053_H
#define VS1053_H

#include <stdio.h>
#include <stdbool.h>

#define MP3_CS_PORT				GPIO_PORTN_BASE
#define MP3_CS_PIN				GPIO_PIN_0

#define MP3_RST_PORT			GPIO_PORTN_BASE
#define MP3_RST_PIN				GPIO_PIN_2

#define MP3_DREQ_PORT			GPIO_PORTN_BASE
#define MP3_DREQ_PIN			GPIO_PIN_1

#define MP3_DCS_PORT			GPIO_PORTN_BASE
#define MP3_DCS_PIN				GPIO_PIN_3

#define VS1053_TIMEOUT			1000

#define VS1053_WRITE_CODE           0x02
#define VS1053_READ_CODE            0x03

#define VS1053_BASE_ADDR        	0x00
#define VS1053_MODE_ADDR        	0x00
#define VS1053_STATUS_ADDR     		0x01
#define VS1053_BASS_ADDR        	0x02
#define VS1053_CLOCKF_ADDR      	0x03
#define VS1053_DECODE_TIME_ADDR 	0x04
#define VS1053_AUDATA_ADDR      	0x05
#define VS1053_WRAM_ADDR        	0x06
#define VS1053_WRAMADDR_ADDR    	0x07
#define VS1053_HDAT0_ADDR       	0x08
#define VS1053_HDAT1_ADDR       	0x09
#define VS1053_AIADDR_ADDR      	0x0A
#define VS1053_VOL_ADDR        	 	0x0B
#define VS1053_AICTRL0_ADDR     	0x0C
#define VS1053_AICTRL1_ADDR     	0x0D
#define VS1053_AICTRL2_ADDR     	0x0E
#define VS1053_AICTRL3_ADDR     	0x0F

#define SET_MP3_CS              MAP_GPIOPinWrite(MP3_CS_PORT, MP3_CS_PIN, MP3_CS_PIN)
#define CLR_MP3_CS              MAP_GPIOPinWrite(MP3_CS_PORT, MP3_CS_PIN, 0)

#define SET_MP3_RST             MAP_GPIOPinWrite(MP3_RST_PORT, MP3_RST_PIN, MP3_RST_PIN)
#define CLR_MP3_RST             MAP_GPIOPinWrite(MP3_RST_PORT, MP3_RST_PIN, 0)

#define SET_MP3_BSYNC           MAP_GPIOPinWrite(MP3_DCS_PORT, MP3_DCS_PIN, MP3_DCS_PIN)
#define CLR_MP3_BSYNC           MAP_GPIOPinWrite(MP3_DCS_PORT, MP3_DCS_PIN, 0)

#define DREQ                    MAP_GPIOPinRead(MP3_DREQ_PORT, MP3_DREQ_PIN)

#define Hi(x) 			(x >> 8)
#define Lo(x) 			(x & 0xFF)


void SPI_Write(uint8_t data);
uint8_t SPI_Read(void);

void VS1053_Init(void);

void VS1053_SCI_Write(uint8_t address, uint16_t data_in);
void VS1053_SCI_Read(uint8_t start_address, uint8_t words_count, uint16_t *data_buffer);

void VS1053_SDI_Write(char data_);
void VS1053_SDI_Write_32(uint8_t *data_);

void VS1053_ResetTime(void);
void VS1053_GetDecodeTime(uint16_t *time);
void VS1053_SetVolume(uint8_t left, uint8_t right);
void VS1053_SetDefaultMode(void);


#endif /* VS1053_H */

/*************************** End of file ****************************/
