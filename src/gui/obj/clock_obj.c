/*
 * Author: J. Bajic, 2022.
 */
#include "board_hw/misc/buzzer.h"
#include "gui/obj/clock_obj.h"
#include <stdio.h>

extern uint8_t buzzer_audio_enable;
extern lv_font_t ni7seg_36;

const lv_obj_class_t lv_clock_class = {
    .width_def = LV_SIZE_CONTENT,
    .height_def = LV_SIZE_CONTENT,
    .instance_size = sizeof(lv_clock_t),
    .base_class = &lv_obj_class
};

static void clock_sec_min_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_current_target(e);
    lv_indev_t * indev = lv_indev_get_act();

    lv_opa_t opa=LV_OPA_0;
    if(indev != NULL)
    {
        lv_indev_type_t indev_type = lv_indev_get_type(indev);
        if(indev_type == LV_INDEV_TYPE_KEYPAD)
            opa=LV_OPA_50;
    }
    if(code == LV_EVENT_PRESSING)
    {
        lv_obj_set_style_bg_opa(obj, LV_OPA_50, LV_PART_CURSOR);
    }
    if(code == LV_EVENT_RELEASED)
    {
        if(buzzer_audio_enable)BUZZER_ClickSound();

        if(lv_spinbox_get_value(obj)==59)
        {
            lv_spinbox_set_value(obj,0);
        }

        else
            lv_spinbox_increment(obj);

        lv_obj_set_style_bg_opa(obj, opa, LV_PART_CURSOR);
    }
}

static void clock_hour_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_current_target(e);
    lv_indev_t * indev = lv_indev_get_act();

    lv_opa_t opa=LV_OPA_0;
    if(indev != NULL)
    {
        lv_indev_type_t indev_type = lv_indev_get_type(indev);
        if(indev_type == LV_INDEV_TYPE_KEYPAD)
            opa=LV_OPA_50;
    }

    if(code == LV_EVENT_PRESSING)
    {
        lv_obj_set_style_bg_opa(obj, LV_OPA_50, LV_PART_CURSOR);
    }
    if(code == LV_EVENT_RELEASED)
    {
        if(buzzer_audio_enable)BUZZER_ClickSound();

        if(lv_spinbox_get_value(obj)==23)
        {
            lv_spinbox_set_value(obj,0);
        }

        else
            lv_spinbox_increment(obj);

        lv_obj_set_style_bg_opa(obj, opa, LV_PART_CURSOR);
    }
}

lv_obj_t *lv_clock_create(lv_obj_t *parent)
{
    lv_obj_t * obj = lv_obj_class_create_obj(&lv_clock_class, parent);
    lv_obj_class_init_obj(obj);

    lv_clock_t * clock = (lv_clock_t *)obj;

    static lv_style_t style_cont_clk;
    lv_style_init(&style_cont_clk);
    lv_style_set_pad_all(&style_cont_clk, 5);

    clock->cont=lv_obj_create(obj);
    lv_obj_set_width(clock->cont, 260);
    lv_obj_set_height(clock->cont, 72);
    lv_obj_add_style(clock->cont, &style_cont_clk, LV_STATE_DEFAULT);

    static lv_style_t style_spinbox;
    lv_style_init(&style_spinbox);
    lv_style_set_text_font(&style_spinbox, &ni7seg_36);

    clock->hour = lv_spinbox_create(clock->cont);
    lv_spinbox_set_range(clock->hour,0,23);
    lv_spinbox_set_digit_format(clock->hour, 2, 0);
    lv_obj_set_width(clock->hour, 78);
    lv_obj_set_pos(clock->hour,0,0);
    lv_obj_add_event_cb(clock->hour, clock_hour_event_handler, LV_EVENT_ALL,  NULL);
    lv_obj_add_style(clock->hour, &style_spinbox, LV_STATE_DEFAULT);

    clock->min = lv_spinbox_create(clock->cont);
    lv_spinbox_set_range(clock->min,0,59);
    lv_spinbox_set_digit_format(clock->min, 2, 0);
    lv_obj_set_width(clock->min, 78);
    lv_obj_set_pos(clock->min,73+10,0);
    lv_obj_add_event_cb(clock->min, clock_sec_min_event_handler, LV_EVENT_ALL,  NULL);
    lv_obj_add_style(clock->min, &style_spinbox, LV_STATE_DEFAULT);

    clock->sec = lv_spinbox_create(clock->cont);
    lv_spinbox_set_range(clock->sec,0,59);
    lv_spinbox_set_digit_format(clock->sec, 2, 0);
    lv_obj_set_width(clock->sec, 78);
    lv_obj_set_pos(clock->sec,146+20,0);
    lv_obj_add_event_cb(clock->sec, clock_sec_min_event_handler, LV_EVENT_ALL,  NULL);
    lv_obj_add_style(clock->sec, &style_spinbox, LV_STATE_DEFAULT);

    lv_obj_t * sep1 = lv_label_create(clock->cont);
    lv_label_set_text(sep1, ":");
    lv_obj_align_to(sep1, clock->min, LV_ALIGN_OUT_LEFT_MID, 0, 0);
    lv_obj_t * sep2 = lv_label_create(clock->cont);
    lv_label_set_text(sep2, ":");
    lv_obj_align_to(sep2, clock->min, LV_ALIGN_OUT_RIGHT_MID, 0, 0);

    lv_color_t color=lv_obj_get_style_text_color(clock->hour, LV_PART_MAIN);

    lv_indev_t * indev = lv_indev_get_act();

    lv_opa_t opa=LV_OPA_0;
    if(indev != NULL)
    {
        lv_indev_type_t indev_type = lv_indev_get_type(indev);
        if(indev_type == LV_INDEV_TYPE_KEYPAD)
            opa=LV_OPA_50;
    }

    lv_obj_set_style_bg_opa(clock->hour, opa, LV_PART_CURSOR);
    lv_obj_set_style_text_color(clock->hour, color, LV_PART_CURSOR);

    lv_obj_set_style_bg_opa(clock->min, opa, LV_PART_CURSOR);
    lv_obj_set_style_text_color(clock->min, color, LV_PART_CURSOR);

    lv_obj_set_style_bg_opa(clock->sec, opa, LV_PART_CURSOR);
    lv_obj_set_style_text_color(clock->sec, color, LV_PART_CURSOR);

    lv_spinbox_set_value(clock->hour,0);
    lv_spinbox_set_value(clock->min,0);
    lv_spinbox_set_value(clock->sec,0);

    return obj;
}


void lv_clock_set_time(lv_obj_t * obj, lv_clock_time_t *time)
{
    lv_clock_t * clock = (lv_clock_t *)obj;

    lv_spinbox_set_value(clock->hour,time->hour);
    lv_spinbox_set_value(clock->min,time->min);
    lv_spinbox_set_value(clock->sec,time->sec);
}

lv_clock_time_t lv_clock_get_time(lv_obj_t * obj)
{
    lv_clock_time_t time;
    lv_clock_t * clock = (lv_clock_t *)obj;

    time.hour=lv_spinbox_get_value(clock->hour);
    time.min=lv_spinbox_get_value(clock->min);
    time.sec=lv_spinbox_get_value(clock->sec);

    return time;
}




