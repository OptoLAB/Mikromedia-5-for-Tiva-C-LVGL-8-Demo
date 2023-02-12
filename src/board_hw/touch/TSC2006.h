/*
 * Author: J. Bajic, 2022.
 */

#ifndef BOARD_HW_DISPLAY_TOUCH_CONTROLLER_H_
#define BOARD_HW_DISPLAY_TOUCH_CONTROLLER_H_

#include <stdint.h>
#include <stdbool.h>

#define TSC2006_CMD             0x80
#define TSC2006_CMD_NORMAL      0x00
#define TSC2006_CMD_STOP        0x01
#define TSC2006_CMD_SWRST       0x02
#define TSC2006_CMD_12BIT       0x04
#define TSC2006_CMD_XYZ1Z2_SCAN 0x00
#define TSC2006_CMD_XY_SCAN     0x08

#define TSC2006_REG_WRITE       0x02
#define TSC2006_REG_READ        0x01
#define TSC2006_REG_PND0        0x02
#define TSC2006_REG_CFR0        0x60
#define TSC2006_REG_CFR1        0x68
#define TSC2006_REG_CFR2        0x70
#define TSC2006_REG_X           0x00
#define TSC2006_REG_Y           0x08
#define TSC2006_REG_Z1          0x10
#define TSC2006_REG_Z2          0x18

void TSC2006_Init(void);
uint16_t TSC2006_readX(void);
uint16_t TSC2006_readY(void);
uint16_t TSC2006_readCFR0(void);
uint16_t TSC2006_isPressed();
void TSC2006_readXYCalibrated(uint16_t *x_coord, uint16_t *y_coord);

#endif /* BOARD_HW_DISPLAY_TOUCH_CONTROLLER_H_ */
