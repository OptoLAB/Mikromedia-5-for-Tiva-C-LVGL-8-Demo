/*
 * Author: J. Bajic, 2022.
 */
#include "board_hw/misc/buzzer.h"
#include "gui/template/template_win.h"
#include <stdio.h>

lv_timer_t *_refresh_task;

extern uint8_t buzzer_audio_enable;

static void close_win__cb(lv_event_t *e)
{

    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *btn = lv_event_get_current_target(e);
    lv_obj_t *win = lv_obj_get_parent(lv_obj_get_parent(btn));

    if(code == LV_EVENT_RELEASED)
    {
        if(buzzer_audio_enable)BUZZER_ClickSound();
        lv_timer_del(_refresh_task);
        lv_obj_del(win);
    }
}

void lv_create_win_(void)
{
    /*Create a window*/
    lv_obj_t *win = lv_win_create(lv_scr_act(), 50);
    lv_win_add_title(win, "Window name");

    /*Add control button to the header*/
    lv_obj_t * close_btn = lv_win_add_btn(win, LV_SYMBOL_CLOSE,45);
    lv_obj_add_event_cb(close_btn, close_win__cb, LV_EVENT_ALL, NULL);
    lv_obj_set_style_bg_color(close_btn, lv_palette_main(LV_PALETTE_RED), LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(close_btn, lv_palette_darken(LV_PALETTE_RED, 4), LV_STATE_PRESSED);


    _refresh_task=lv_timer_create((lv_timer_cb_t) lv_update_win_, 100, NULL);
}

void lv_update_win_(void)
{

}
