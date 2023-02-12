/*
 * Author: J. Bajic, 2022.
 */

#ifndef GUI_CLOCK_OBJ_H_
#define GUI_CLOCK_OBJ_H_


#include "lvgl/lvgl.h"

typedef struct
{
    uint8_t hour;
    uint8_t min;
    uint8_t sec;
} lv_clock_time_t;

typedef struct
{
    lv_obj_t obj;
    lv_obj_t *cont;
    lv_obj_t *hour;
    lv_obj_t *min;
    lv_obj_t *sec;
} lv_clock_t;

lv_obj_t *lv_clock_create(lv_obj_t *parent);
void lv_clock_set_time(lv_obj_t *obj, lv_clock_time_t *time);
lv_clock_time_t lv_clock_get_time(lv_obj_t *obj);

#endif /* GUI_CLOCK_OBJ_H_ */
