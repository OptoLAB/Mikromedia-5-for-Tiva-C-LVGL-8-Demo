/*
 * Author: J. Bajic, 2022.
 */

// Intended for use with TI GUI Composer

#include "board_hw/comm/serial.h"
#include "board_hw/comm/radio.h"
#include "board_hw/comm/rw_json.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char string[256]={};

uint8_t transciever_port=RXTX_USB; //default

static void write(uint8_t *data, uint32_t ui32Count)
{
    if(transciever_port==RXTX_USB)
        SERIAL_Write(data, ui32Count);
    else
        RADIO_Transmit(data, ui32Count);
}
static uint32_t read(uint8_t *data)
{
    if(transciever_port==RXTX_USB)
        return SERIAL_Read(data);
    else
        return RADIO_Receive(data);
}

/*****************************************************************
 *  Sets write/read port
 *  Transfer data over serial or over nRF24:
 *      RXTX_USB or RXTX_NRF
 *****************************************************************/
void JSON_SetPort(uint8_t port)
{
    transciever_port=port;
}
/*****************************************************************
 *  Writes JSONobj_t array over serial in format:
 *      {"name0":value0,"name1":value1,...,"nameN":valueN}\n,
 *  N=num_of_obj
 *****************************************************************/
void JSON_Write(JSONobj_t *jdata, unsigned char num_of_obj)
{
    int i=0;
    unsigned char cptr=0;
    char value[10];

    strcpy(&string[cptr],"{");
    cptr+=1;
    for(i=0;i<num_of_obj;i++)
    {
        sprintf(&string[cptr],"\"%s\":",jdata[i].name);
        cptr+=strlen(jdata[i].name)+3;

        itoa((long)(jdata[i].value),value,10);
        strcpy(&string[cptr],value);
        cptr+=strlen(value);

        if(i!=(num_of_obj-1))
        {
            strcpy(&string[cptr],",");
            cptr+=1;
        }
    }
    strcpy(&string[cptr],"}\n");
    cptr+=2;

    write((uint8_t *)string,cptr);
}

/*****************************************************************
 *  Reads and parses JSON formated string into jdata variable
 *  Returns 1 if JSON format is received:
 *      {"name":value}\n
 *  Otherwise returns 0
 *****************************************************************/
unsigned char JSON_Read(JSONobj_t *jdata)
{
    char name[10]={}, value[10]={};
    unsigned char cptr=0, status=0, i=0;
    uint32_t len=0;

    status=0;
    len=read((uint8_t*)string);
    if(len)
    {
        if(string[cptr]=='{'&&string[cptr+1]=='\"')//start of JSON stream
        {
            cptr+=2;
            for(i=cptr;i<len;i++) //extract name
            {
                if(string[i]=='\"') break;
                else name[i-cptr]=string[i];
            }

            cptr=i+1;
            if(string[cptr]==':') //separator
            {
                cptr+=1;
                for(i=cptr;i<len;i++) //extract value
                {
                    if(string[i]=='}') break;
                    else value[i-cptr]=string[i];
                }

                cptr=i+1;
                if(string[cptr]=='\n')//end of JSON stream
                {
                    strcpy(jdata->name,name);
                    jdata->value=(float)atoi(value);
                    status=1;
                }
            }
        }
    }
    return status;
}
