/*
 * Author: J. Bajic, 2022.
 */

// Intended for use with TI GUI Composer

#ifndef BOARD_HW_SERIAL_JSON_H_
#define BOARD_HW_SERIAL_JSON_H_

#include <stdint.h>

typedef struct{
    char name[10];
    int value;
}JSONobj_t;

#define RXTX_USB 0
#define RXTX_NRF 1

void JSON_SetPort(uint8_t port);
void JSON_Write(JSONobj_t *jdata, unsigned char num_of_vars);
unsigned char JSON_Read(JSONobj_t *jdata);


#endif /* BOARD_HW_SERIAL_JSON_H_ */
