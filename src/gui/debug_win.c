/*
 * Author: J. Bajic, 2022.
 */

#include "gui/debug_win.h"
#include "gui/main_win.h"
#include "board_hw/board_hw.h"
#include "board_hw/misc/buzzer.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

lv_timer_t *debug_refresh_task;
lv_obj_t *txt_comm;
lv_obj_t *led_red, *led_green, *led_blue;
lv_obj_t *sw_rled, *sw_gled, *sw_bled;
lv_obj_t *img_debug;

JSONobj_t ADC[3]={{"ADC0",0},{"ADC1",0},{"ADC2",0}};
JSONobj_t LED[3]={{"RLED",0},{"GLED",0},{"BLED",0}};
JSONobj_t ACCEL[3]={{"ax",0},{"ay",0},{"az",0}};
JSONobj_t menu={"tab",0};
uint8_t delay_count=0;
uint8_t transmit_enable=1;
extern uint8_t buzzer_audio_enable;
extern const lv_img_dsc_t nRF_debug;
extern const lv_img_dsc_t usb_debug;

static void close_win_debug_cb(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *btn = lv_event_get_current_target(e);
    lv_obj_t *win = lv_obj_get_parent(lv_obj_get_parent(btn));

    if(code == LV_EVENT_RELEASED)
    {
        if(buzzer_audio_enable)BUZZER_ClickSound();
        lv_timer_del(debug_refresh_task);
        lv_obj_del(win);
        lv_create_win_main();
    }
}
static void cb_comm_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *obj = lv_event_get_current_target(e);

    if(code == LV_EVENT_VALUE_CHANGED)
    {
        if(buzzer_audio_enable)BUZZER_ClickSound();
        if(lv_obj_get_state(obj) & LV_STATE_CHECKED)
        {
            transmit_enable=1;
            lv_checkbox_set_text(obj, "Transmitter enabled");
        }
        else
        {
            transmit_enable=0;
            lv_checkbox_set_text(obj, "Transmitter disabled");
        }
    }
}
static void dd_comm_event_handler(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_target(e);

    if(code == LV_EVENT_CLICKED)
    {
        if(buzzer_audio_enable)BUZZER_ClickSound();
    }
    if(code == LV_EVENT_VALUE_CHANGED)
    {
        if(buzzer_audio_enable)BUZZER_ClickSound();
        if(lv_dropdown_get_selected(obj))
        {
            JSON_SetPort(RXTX_NRF);
            lv_img_set_src(img_debug, &nRF_debug);
        }
        else
        {
            JSON_SetPort(RXTX_USB);
            lv_img_set_src(img_debug, &usb_debug);
        }
    }
}

static void sw_rled_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *obj = lv_event_get_current_target(e);

    if(code == LV_EVENT_VALUE_CHANGED)
    {
        if(buzzer_audio_enable)BUZZER_ClickSound();
        if(lv_obj_get_state(obj) & LV_STATE_CHECKED)LED[0].value=1;
        else LED[0].value=0;
    }
}
static void sw_gled_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *obj = lv_event_get_current_target(e);

    if(code == LV_EVENT_VALUE_CHANGED)
    {
        if(buzzer_audio_enable)BUZZER_ClickSound();
        if(lv_obj_get_state(obj) & LV_STATE_CHECKED)LED[1].value=1;
        else LED[1].value=0;
    }
}
static void sw_bled_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *obj = lv_event_get_current_target(e);

    if(code == LV_EVENT_VALUE_CHANGED)
    {
        if(buzzer_audio_enable)BUZZER_ClickSound();
        if(lv_obj_get_state(obj) & LV_STATE_CHECKED)LED[2].value=1;
        else LED[2].value=0;
    }
}
static void lv_create_switches(lv_obj_t * par)
{
    sw_rled = lv_switch_create(par);
    lv_obj_align(sw_rled, LV_ALIGN_CENTER, -200, 70);
    lv_obj_add_event_cb(sw_rled, sw_rled_event_handler, LV_EVENT_ALL, NULL);

    sw_gled = lv_switch_create(par);
    lv_obj_align(sw_gled, LV_ALIGN_CENTER, 0, 70);
    lv_obj_add_event_cb(sw_gled, sw_gled_event_handler, LV_EVENT_ALL, NULL);

    sw_bled = lv_switch_create(par);
    lv_obj_align(sw_bled, LV_ALIGN_CENTER, 200, 70);
    lv_obj_add_event_cb(sw_bled, sw_bled_event_handler, LV_EVENT_ALL, NULL);
}

static void lv_create_leds(lv_obj_t * par)
{
    //Red LED
    led_red  = lv_led_create(par);
    lv_obj_align(led_red, LV_ALIGN_CENTER, -200, 0);
    lv_led_set_color(led_red, lv_palette_main(LV_PALETTE_RED));
    lv_led_off(led_red);

    //Green LED
    led_green = lv_led_create(par);
    lv_obj_align(led_green, LV_ALIGN_CENTER, 0, 0);
    lv_led_set_color(led_green, lv_palette_main(LV_PALETTE_GREEN));
    lv_led_off(led_green);

    //Blue LED
    led_blue  = lv_led_create(par);
    lv_obj_align(led_blue, LV_ALIGN_CENTER, 200, 0);
    lv_led_set_color(led_blue, lv_palette_main(LV_PALETTE_BLUE));
    lv_led_off(led_blue);
}

void lv_create_win_debug(void)
{
    lv_disp_t * disp = lv_disp_get_default();
    lv_theme_t * th = lv_disp_get_theme(disp);
    lv_color_t prim_color=th->color_primary;

    /*Create a window*/
    lv_obj_t * win = lv_win_create(lv_scr_act(), 50);
    lv_win_add_title(win, "Debug (Serial or nRF24)");
    lv_obj_t * cont = lv_win_get_content(win);

    /*Add control button to the header*/
    lv_obj_t * close_btn = lv_win_add_btn(win, LV_SYMBOL_CLOSE, 45);
    lv_obj_add_event_cb(close_btn, close_win_debug_cb, LV_EVENT_ALL, NULL);
    lv_obj_set_style_bg_color(close_btn, lv_palette_main(LV_PALETTE_RED), LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(close_btn, lv_palette_darken(LV_PALETTE_RED, 4), LV_STATE_PRESSED);

    lv_obj_t * txt = lv_label_create(cont);
    lv_label_set_text(txt, "Select communication port:");
    lv_obj_align(txt, LV_ALIGN_LEFT_MID, 0, -90);

    lv_color_t color=lv_obj_get_style_text_color(txt,0);

    lv_obj_t * spans = lv_spangroup_create(cont);
    lv_obj_set_width(spans, 760);

    lv_spangroup_set_align(spans, LV_TEXT_ALIGN_LEFT);
    lv_spangroup_set_overflow(spans, LV_SPAN_OVERFLOW_CLIP);
    lv_spangroup_set_mode(spans, LV_SPAN_MODE_BREAK);

    lv_span_t * span = lv_spangroup_new_span(spans);
    lv_span_set_text(span, "Connect to PC via ");
    lv_style_set_text_color(&span->style, color);

    span = lv_spangroup_new_span(spans);
    lv_span_set_text(span, "USB");
    lv_style_set_text_color(&span->style, prim_color);
    lv_style_set_text_decor(&span->style, LV_TEXT_DECOR_UNDERLINE);

    span = lv_spangroup_new_span(spans);
    lv_span_set_text(span, " connector marked ICDI or ");
    lv_style_set_text_color(&span->style, color);

    span = lv_spangroup_new_span(spans);
    lv_span_set_text(span, "nRF24");
    lv_style_set_text_color(&span->style, prim_color);
    lv_style_set_text_decor(&span->style, LV_TEXT_DECOR_UNDERLINE);

    span = lv_spangroup_new_span(spans);
    lv_span_set_text(span, " wireless module and run TI GUI Composer app");
    lv_style_set_text_color(&span->style, color);

    lv_spangroup_refr_mode(spans);

    lv_obj_t *cb_comm = lv_checkbox_create(cont);
    if(transmit_enable)
    {
        lv_obj_add_state(cb_comm, LV_STATE_CHECKED);
        lv_checkbox_set_text(cb_comm, "Transmitter enabled");
    }
    else
    {
        lv_obj_clear_state(cb_comm, LV_STATE_CHECKED);
        lv_checkbox_set_text(cb_comm, "Transmitter disabled");
    }
    lv_obj_align(cb_comm, LV_ALIGN_LEFT_MID, 50, 170);
    lv_obj_add_event_cb(cb_comm, cb_comm_event_handler, LV_EVENT_ALL, NULL);


    lv_obj_t * dd_comm = lv_dropdown_create(cont);
    lv_dropdown_set_options(dd_comm, "USB\nnRF24");
    lv_obj_align(dd_comm, LV_ALIGN_LEFT_MID, 330, -90);
    lv_obj_add_event_cb(dd_comm, dd_comm_event_handler, LV_EVENT_ALL, NULL);

    lv_create_leds(cont);
    lv_create_switches(cont);

    img_debug = lv_img_create(cont);
    lv_obj_align(img_debug, LV_ALIGN_CENTER, 200, -100);
    lv_img_set_src(img_debug, &usb_debug);
    lv_obj_set_style_img_recolor_opa(img_debug, LV_OPA_COVER, 0);
    lv_obj_set_style_img_recolor(img_debug, prim_color, 0);

    debug_refresh_task=lv_timer_create((lv_timer_cb_t) lv_update_win_debug, 20, NULL);
}

void lv_update_win_debug(void)
{
    JSONobj_t temp={"none",0};

    ADCSensors_Read();
    ADC[0].value=ADCSensors_getPINDiodeV()*100;
    ADC[1].value=ADCSensors_getTempExternalC()*100;
    ADC[2].value=ADCSensors_getTempInternalC()*100;
    LEDs_Set(RLED,LED[0].value);
    LEDs_Set(GLED,LED[1].value);
    LEDs_Set(BLED,LED[2].value);
    if(LED[0].value)
    {
        lv_led_on(led_red);
        lv_obj_add_state(sw_rled, LV_STATE_CHECKED);
    }
    else
    {
        lv_led_off(led_red);
        lv_obj_clear_state(sw_rled, LV_STATE_CHECKED);
    }
    if(LED[1].value)
    {
        lv_led_on(led_green);
        lv_obj_add_state(sw_gled, LV_STATE_CHECKED);
    }
    else
    {
        lv_led_off(led_green);
        lv_obj_clear_state(sw_gled, LV_STATE_CHECKED);
    }
    if(LED[2].value)
    {
        lv_led_on(led_blue);
        lv_obj_add_state(sw_bled, LV_STATE_CHECKED);
    }
    else
    {
        lv_led_off(led_blue);
        lv_obj_clear_state(sw_bled, LV_STATE_CHECKED);
    }

    ACCEL[0].value=((int16_t)ADXL345_ReadX());
    ACCEL[1].value=((int16_t)ADXL345_ReadY());
    ACCEL[2].value=((int16_t)ADXL345_ReadZ());

    if(JSON_Read(&temp))
    {
       JSON_Write(&temp,1);
       if(!strcmp(temp.name,"RLED"))LED[0]=temp;
       if(!strcmp(temp.name,"GLED"))LED[1]=temp;
       if(!strcmp(temp.name,"BLED"))LED[2]=temp;
       if(!strcmp(temp.name,"tab"))
       {
           menu=temp;
           JSON_Write(&menu,1);
       }
    }
    if(transmit_enable)
    {
        switch(menu.value)
        {
            case 0:
                JSON_Write(ADC,3);
                JSON_Write(LED,3);
                break;
            case 1:
                JSON_Write(ACCEL,3);
                break;
            case 2:
                delay_count++;
                if(delay_count>=10) //slow down
                {
                    JSON_Write(&temp,1);
                    JSON_Write(ADC,3);
                    JSON_Write(LED,3);
                    JSON_Write(ACCEL,3);
                    delay_count=0;
                }
                break;
        }
    }

}
