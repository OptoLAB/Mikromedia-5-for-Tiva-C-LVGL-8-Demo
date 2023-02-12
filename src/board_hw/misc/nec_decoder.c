#include "board_hw/misc/nec_decoder.h"

static uint8_t bit_counter=0;
static uint32_t capture_timmings[34];
static uint8_t NEC_addr=0;
static uint8_t NEC_cmd=0;
static uint8_t NEC_stat=0;
static uint32_t nec_tick=0;

uint32_t NEC_GetTimer(void)
{
    return nec_tick;
}

void NEC_ResetTimer(void)
{
    nec_tick=0;
}

void NEC_TickInc(uint8_t inc)
{
    nec_tick+=inc;
}

uint8_t NEC_Capture(uint32_t time)
{
	if(time<12500)
	{
		capture_timmings[bit_counter]=NEC_GetTimer();
		bit_counter++;
	}
	else
		bit_counter=0;

	if(bit_counter==32)
		return 1;
	else
		return 0;
}

void NEC_Decode(void)
{
	uint8_t decoded_data[4];

    for (int i=0; i<32; i++)
    {
        if (capture_timmings[i] > 1680)
        	decoded_data[i/8]|=1<<(i%8);
        else
        	decoded_data[i/8]&=~(1<<(i%8));
    }

	if((decoded_data[0]==(uint8_t)(~decoded_data[1]))&&(decoded_data[2]==(uint8_t)(~decoded_data[3])))
	{
		NEC_addr=decoded_data[1];
		NEC_cmd=decoded_data[3];
		NEC_stat=1;
	}
	else
	{
		NEC_addr=0;
		NEC_cmd=0;
		NEC_stat=0;
	}
}

uint8_t NEC_GetCommand(void)
{
	return NEC_cmd;
}

uint8_t NEC_GetAddress(void)
{
	return NEC_addr;
}

uint8_t NEC_GetStatus(void)
{
	return NEC_stat;
}

void NEC_ClearStatus(void)
{
	NEC_stat=0;
}
