/*
 * Author: J. Bajic, 2022.
 */

#ifndef LV_PORT_H
#define LV_PORT_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#if defined(LV_LVGL_H_INCLUDE_SIMPLE)
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif

/*********************
 *      DEFINES
 *********************/
#define MY_DISP_HOR_RES     800
#define MY_DISP_VER_RES     480
#define MY_DISP_ROTATION    0   //0-none, 1-90 deg rotation, 2-180 deg rotation, 3-270 deg rotation (software rotation)

#define FLUSH_SIMPLE    0   //simple pixel by pixel copy, if USE_EPI is set to 1 EPIWorkaroundHWordWrite is used
#define FLUSH_MEMCPY    1   //uses lv_memcpy
#define FLUSH_DMA       2   //uses uDMA
#define FLUSH_CUSTOM    3   //implement something else

#define USE_EPI         0   //applies in FLUSH_SIMPLE mode

#define SINGLE_BUF      0
#define DUAL_BUF        1

#define RAM_INT         0
#define RAM_EXT         1

#define INT_BUF_SIZE    (MY_DISP_HOR_RES*32)
#define EXT_BUF_SIZE    (MY_DISP_HOR_RES*MY_DISP_VER_RES)
#define EXT_BUF1_ADR    (0x10000000+EXT_BUF_SIZE*2)
#define EXT_BUF2_ADR    (EXT_BUF1_ADR+EXT_BUF_SIZE*2)

#define FLUSH_MODE      FLUSH_DMA   //FLUSH_SIMPLE, FLUSH_MEMCPY, FLUSH_DMA
#define BUFFERING_MODE  DUAL_BUF
#define BUFFER_RAM      RAM_INT

#define USE_IR_REMOTE_AS_CURSOR     0   //0-keypad, 1-cursor
/**********************
 *      TYPEDEFS
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/
/* Initialize low level display driver */
void lv_port_init(void);

/**********************
 *      MACROS
 **********************/

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif
