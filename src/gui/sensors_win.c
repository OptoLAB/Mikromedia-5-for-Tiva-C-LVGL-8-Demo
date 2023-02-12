/*
 * Author: J. Bajic, 2022.
 */

#include "board_hw/misc/buzzer.h"
#include "board_hw/misc/sensors_adc.h"
#include "board_hw/accel/ADXL345.h"
#include "board_hw/touch/TSC2006.h"
#include "gui/sensors_win.h"
#include "gui/main_win.h"
#include <stdio.h>

#define CANVAS_WIDTH        300
#define CANVAS_HEIGHT       200
#define CANVAS_X_OFFSET     0
#define CANVAS_Y_OFFSET     -30

lv_obj_t * canvas, *canvas_cw, *canvas_arc, *canvas_btn_clear;
lv_color_t canvas_bg, canvas_fg, canvas_pen_color;
lv_area_t canvas_area;
uint8_t canvas_pen_size=5;
lv_obj_t *tabview_sensors;
lv_obj_t *txt_touch_data, *txt_bat_volts, *txt_pin;
lv_obj_t *txt_ext_temp, *txt_int_temp;
lv_obj_t *txt_ax, *txt_ay, *txt_az;
lv_obj_t * meter_temp, *meter_pin;
lv_timer_t *sensors_refresh_task;
lv_obj_t * chart_accel, *accel_cont_radio;

lv_chart_series_t * ser_x, *ser_y, *ser_z;
lv_meter_indicator_t *temp_ext, *temp_int, *pin_diode;
static lv_style_t style_radio;
static lv_style_t style_radio_chk;
int32_t radio_id=0;

extern uint8_t buzzer_audio_enable;
extern lv_font_t ni7seg_36;

static void tab_btns_event_cb(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *tabview = lv_event_get_current_target(e);

    if(code == LV_EVENT_VALUE_CHANGED)
    {
        if(buzzer_audio_enable)BUZZER_ClickSound();

        uint16_t act_tv=lv_tabview_get_tab_act(tabview);
        lv_group_add_obj(lv_group_get_default(), accel_cont_radio);
        lv_group_add_obj(lv_group_get_default(), canvas_btn_clear);
        if(act_tv==0)
        {
            lv_group_remove_obj(accel_cont_radio);
            lv_group_remove_obj(canvas_btn_clear);
        }
        if(act_tv==1)
            lv_group_remove_obj(canvas_btn_clear);
        if(act_tv==2)
            lv_group_remove_obj(accel_cont_radio);
    }
}
static void close_win_sensors_cb(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *btn = lv_event_get_current_target(e);
    lv_obj_t *win = lv_obj_get_parent(lv_obj_get_parent(btn));

    if(code == LV_EVENT_RELEASED)
    {
        if(buzzer_audio_enable)BUZZER_ClickSound();
        lv_timer_del(sensors_refresh_task);
        lv_obj_del(win);
        lv_create_win_main();

    }
}
static void btn_clear_canvas_event_cb(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    if(code == LV_EVENT_RELEASED)
    {
        if(buzzer_audio_enable)BUZZER_ClickSound();
        lv_canvas_fill_bg(canvas, canvas_bg, LV_OPA_COVER);
    }
}
static void pen_event_handler(lv_event_t *e)
{
    if(buzzer_audio_enable)BUZZER_ClickSound();
}
static void radio_event_handler(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * act_cb = lv_event_get_target(e);
    lv_obj_t * cont = lv_obj_get_parent(act_cb);
    lv_obj_t * old_cb = lv_obj_get_child(cont, radio_id);

    if(code == LV_EVENT_CLICKED)
    {
        if(buzzer_audio_enable)BUZZER_ClickSound();

        lv_obj_clear_state(old_cb, LV_STATE_CHECKED);
        lv_obj_add_state(act_cb, LV_STATE_CHECKED);     /*Uncheck the current radio button*/
        radio_id = lv_obj_get_index(act_cb);
        switch(radio_id)
        {
            case 0:
                lv_style_set_bg_color(&style_radio_chk, lv_palette_main(LV_PALETTE_RED));
                lv_style_set_border_color(&style_radio_chk, lv_palette_main(LV_PALETTE_RED));
                lv_chart_hide_series(chart_accel, ser_x, false);
                lv_chart_hide_series(chart_accel, ser_y, true);
                lv_chart_hide_series(chart_accel, ser_z, true);
                break;
            case 1:
                lv_style_set_bg_color(&style_radio_chk, lv_palette_main(LV_PALETTE_GREEN));
                lv_style_set_border_color(&style_radio_chk, lv_palette_main(LV_PALETTE_GREEN));
                lv_chart_hide_series(chart_accel, ser_x, true);
                lv_chart_hide_series(chart_accel, ser_y, false);
                lv_chart_hide_series(chart_accel, ser_z, true);
                break;
            case 2:
                lv_style_set_bg_color(&style_radio_chk, lv_palette_main(LV_PALETTE_BLUE));
                lv_style_set_border_color(&style_radio_chk, lv_palette_main(LV_PALETTE_BLUE));
                lv_chart_hide_series(chart_accel, ser_x, true);
                lv_chart_hide_series(chart_accel, ser_y, true);
                lv_chart_hide_series(chart_accel, ser_z, false);
                break;
            case 3:
                lv_style_set_bg_color(&style_radio_chk, lv_color_black());
                lv_style_set_border_color(&style_radio_chk, lv_color_black());
                lv_chart_hide_series(chart_accel, ser_x, false);
                lv_chart_hide_series(chart_accel, ser_y, false);
                lv_chart_hide_series(chart_accel, ser_z, false);
                break;
        }
    }
}
static void lv_create_meter_pin(lv_obj_t * par)
{
    static lv_style_t style_meter;
    lv_style_init(&style_meter);
    lv_style_set_text_font(&style_meter, &lv_font_montserrat_18);

    meter_pin = lv_meter_create(par);
    lv_obj_set_style_pad_left(meter_pin,5,LV_PART_MAIN);
    lv_obj_set_style_pad_right(meter_pin,5,LV_PART_MAIN);
    lv_obj_set_style_pad_top(meter_pin,5,LV_PART_MAIN);
    lv_obj_set_style_pad_bottom(meter_pin,5,LV_PART_MAIN);
    lv_obj_set_size(meter_pin, 220, 220);
    lv_obj_set_pos(meter_pin,455,30);

    lv_obj_add_style(meter_pin, &style_meter, LV_PART_MAIN);

    lv_meter_scale_t *scale = lv_meter_add_scale(meter_pin);
    lv_meter_set_scale_ticks(meter_pin, scale, 41, 2, 10, lv_color_black());
    lv_meter_set_scale_major_ticks(meter_pin, scale, 8, 4, 15, lv_color_black(), 15);

    pin_diode = lv_meter_add_arc(meter_pin, scale, 3, lv_palette_main(LV_PALETTE_BLUE), 0);
    lv_meter_set_indicator_start_value(meter_pin, pin_diode, 0);
    lv_meter_set_indicator_end_value(meter_pin, pin_diode, 20);

    pin_diode = lv_meter_add_scale_lines(meter_pin, scale, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_BLUE), false, 0);
    lv_meter_set_indicator_start_value(meter_pin, pin_diode, 0);
    lv_meter_set_indicator_end_value(meter_pin, pin_diode, 20);

    pin_diode = lv_meter_add_arc(meter_pin, scale, 3, lv_palette_main(LV_PALETTE_RED), 0);
    lv_meter_set_indicator_start_value(meter_pin, pin_diode, 80);
    lv_meter_set_indicator_end_value(meter_pin, pin_diode, 100);

    pin_diode = lv_meter_add_scale_lines(meter_pin, scale, lv_palette_main(LV_PALETTE_RED), lv_palette_main(LV_PALETTE_RED), false, 0);
    lv_meter_set_indicator_start_value(meter_pin, pin_diode, 80);
    lv_meter_set_indicator_end_value(meter_pin, pin_diode, 100);

    pin_diode = lv_meter_add_needle_line(meter_pin, scale, 4, lv_palette_main(LV_PALETTE_GREY), -10);

    static lv_style_t ni7seg_style;
    lv_style_init(&ni7seg_style);
    lv_style_set_text_font(&ni7seg_style, &ni7seg_36);
    lv_style_set_text_color(&ni7seg_style,lv_palette_main(LV_PALETTE_BLUE));
    lv_style_set_text_align(&ni7seg_style, LV_TEXT_ALIGN_CENTER);

    txt_pin = lv_label_create(par);
    lv_label_set_text(txt_pin, "");
    lv_obj_add_style(txt_pin, &ni7seg_style, LV_STATE_DEFAULT);
    lv_obj_align_to(txt_pin, meter_pin, LV_ALIGN_CENTER, -25, 80);

    lv_obj_t *title = lv_label_create(par);
    lv_label_set_text(title, "Light level [%]");
    lv_obj_align_to(title, meter_pin, LV_ALIGN_OUT_TOP_MID, 0, -15);
}

static void lv_create_meter_temp(lv_obj_t * par)
{

    static lv_style_t style_meter;
    lv_style_init(&style_meter);
    lv_style_set_text_font(&style_meter, &lv_font_montserrat_18);

    meter_temp = lv_meter_create(par);
    lv_obj_set_style_pad_left(meter_temp,5,LV_PART_MAIN);
    lv_obj_set_style_pad_right(meter_temp,5,LV_PART_MAIN);
    lv_obj_set_style_pad_top(meter_temp,5,LV_PART_MAIN);
    lv_obj_set_style_pad_bottom(meter_temp,5,LV_PART_MAIN);
    lv_obj_remove_style(meter_temp, NULL, LV_PART_INDICATOR);
    lv_obj_add_style(meter_temp, &style_meter, LV_STATE_DEFAULT);
    lv_obj_set_pos(meter_temp,65,30);
    lv_obj_set_size(meter_temp, 220, 220);

    lv_meter_scale_t * scale = lv_meter_add_scale(meter_temp);

    lv_meter_set_scale_ticks(meter_temp, scale, 7, 4, 15, lv_palette_main(LV_PALETTE_GREY));
    lv_meter_set_scale_major_ticks(meter_temp, scale, 1, 2, 20, lv_color_hex3(0xeee), 15);
    lv_meter_set_scale_range(meter_temp, scale, 20, 50, 270, 135);

    temp_int = lv_meter_add_arc(meter_temp, scale, 10, lv_palette_main(LV_PALETTE_RED), -10);
    temp_ext = lv_meter_add_arc(meter_temp, scale, 10, lv_palette_main(LV_PALETTE_GREEN), 0);

    static lv_style_t ext_temp_style;
    lv_style_init(&ext_temp_style);
    lv_style_set_text_color(&ext_temp_style,lv_palette_main(LV_PALETTE_GREEN));

    txt_ext_temp = lv_label_create(par);
    lv_obj_add_style(txt_ext_temp, &ext_temp_style, LV_STATE_DEFAULT);
    lv_obj_set_pos(txt_ext_temp, 60, 265);
    lv_label_set_text(txt_ext_temp, "");

    static lv_style_t int_temp_style;
    lv_style_init(&int_temp_style);
    lv_style_set_text_color(&int_temp_style,lv_palette_main(LV_PALETTE_RED));

    txt_int_temp = lv_label_create(par);
    lv_obj_add_style(txt_int_temp, &int_temp_style, LV_STATE_DEFAULT);
    lv_obj_set_pos(txt_int_temp, 60, 295);
    lv_label_set_text(txt_int_temp, "");

    lv_obj_t *title = lv_label_create(par);
    lv_label_set_text(title, "Temperature ['C]");
    lv_obj_align_to(title, meter_temp, LV_ALIGN_OUT_TOP_MID, 0, -15);
}

static void radiobutton_create(lv_obj_t * parent, const char * txt)
{
    lv_obj_t * obj = lv_checkbox_create(parent);
    lv_group_remove_obj(obj);
    lv_checkbox_set_text(obj, txt);
    lv_obj_add_event_cb(obj, radio_event_handler, LV_EVENT_ALL, NULL);
    lv_obj_add_style(obj, &style_radio, LV_PART_INDICATOR);
    lv_obj_add_style(obj, &style_radio_chk, LV_PART_INDICATOR | LV_STATE_CHECKED);
    lv_obj_set_style_text_color(obj, lv_palette_main(LV_PALETTE_GREY), LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(obj, lv_color_black(), LV_STATE_CHECKED);
}
static void lv_create_chart(lv_obj_t * par)
{
    chart_accel = lv_chart_create(par);

    lv_chart_set_type(chart_accel, LV_CHART_TYPE_LINE);
    lv_chart_set_range(chart_accel, LV_CHART_AXIS_PRIMARY_Y, -500, 500);
    lv_chart_set_div_line_count(chart_accel, 5, 10);
    lv_chart_set_point_count(chart_accel,25);
    lv_chart_set_update_mode(chart_accel, LV_CHART_UPDATE_MODE_SHIFT);

    lv_obj_set_pos(chart_accel, 0, 40);
    lv_obj_set_size(chart_accel, 500, 250);

    lv_obj_set_style_size(chart_accel, 0, LV_PART_INDICATOR);//Do not display points on the data
    lv_obj_set_style_line_width(chart_accel, 3, LV_PART_ITEMS);   //set line width
    lv_obj_set_style_line_opa(chart_accel, LV_OPA_70, LV_PART_ITEMS);   //set line width
    lv_obj_set_style_line_width(chart_accel, 1, LV_PART_MAIN);
    lv_obj_set_style_pad_left(chart_accel,0,LV_PART_MAIN);
    lv_obj_set_style_pad_right(chart_accel,0,LV_PART_MAIN);
    lv_obj_set_style_pad_top(chart_accel,0,LV_PART_MAIN);
    lv_obj_set_style_pad_bottom(chart_accel,0,LV_PART_MAIN);

    ser_x = lv_chart_add_series(chart_accel, lv_palette_main(LV_PALETTE_RED),LV_CHART_AXIS_PRIMARY_Y);
    ser_y = lv_chart_add_series(chart_accel, lv_palette_main(LV_PALETTE_GREEN),LV_CHART_AXIS_PRIMARY_Y);
    ser_z = lv_chart_add_series(chart_accel, lv_palette_main(LV_PALETTE_BLUE),LV_CHART_AXIS_PRIMARY_Y);

    lv_chart_set_all_value(chart_accel, ser_x, 0);
    lv_chart_set_all_value(chart_accel, ser_y, 0);
    lv_chart_set_all_value(chart_accel, ser_z, 0);

    lv_chart_hide_series(chart_accel, ser_x, false);
    lv_chart_hide_series(chart_accel, ser_y, true);
    lv_chart_hide_series(chart_accel, ser_z, true);

    txt_ax = lv_label_create(par);
    lv_obj_set_pos(txt_ax, 470, 300);
    lv_label_set_text(txt_ax, "");

    txt_ay = lv_label_create(par);
    lv_obj_set_pos(txt_ay, 570, 300);
    lv_label_set_text(txt_ay, "");

    txt_az = lv_label_create(par);
    lv_obj_set_pos(txt_az, 670, 300);
    lv_label_set_text(txt_az, "");

    lv_obj_t *title_chart = lv_label_create(par);
    lv_label_set_text(title_chart, "Accelerometer ADXL345");
    lv_obj_align_to(title_chart, chart_accel, LV_ALIGN_OUT_TOP_LEFT, 0, -10);

    //radio buttons
    lv_style_init(&style_radio);
    lv_style_set_radius(&style_radio, LV_RADIUS_CIRCLE);
    lv_style_set_border_color(&style_radio, lv_palette_main(LV_PALETTE_GREY));

    lv_style_init(&style_radio_chk);
    lv_style_set_bg_img_src(&style_radio_chk, NULL);
    lv_style_set_text_color(&style_radio_chk, lv_color_black());
    //lv_style_set_border_color(&style_radio, lv_palette_main(LV_PALETTE_RED));
    lv_style_set_bg_color(&style_radio_chk, lv_palette_main(LV_PALETTE_RED));

    accel_cont_radio = lv_obj_create(par);
    lv_gridnav_add(accel_cont_radio, LV_GRIDNAV_CTRL_ROLLOVER);
    lv_group_add_obj(lv_group_get_default(), accel_cont_radio);
    lv_obj_set_flex_flow(accel_cont_radio, LV_FLEX_FLOW_COLUMN);
    lv_obj_clear_flag(accel_cont_radio, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
    lv_group_remove_obj(accel_cont_radio);

    lv_obj_set_pos(accel_cont_radio, 520, 40);
    lv_obj_set_size(accel_cont_radio, 170, 190);
   // lv_obj_add_event_cb(cont_radio, radio_event_handler, LV_EVENT_ALL, NULL);

    lv_obj_t *title_radio = lv_label_create(par);
    lv_label_set_text(title_radio, "Active axis:");
    lv_obj_align_to(title_radio, accel_cont_radio, LV_ALIGN_OUT_TOP_LEFT, 0, -10);

    radiobutton_create(accel_cont_radio, "x accel");
    radiobutton_create(accel_cont_radio, "y accel");
    radiobutton_create(accel_cont_radio, "z accel");
    radiobutton_create(accel_cont_radio, "all");

    /*Make the first checkbox checked*/
    lv_obj_add_state(lv_obj_get_child(accel_cont_radio, radio_id), LV_STATE_CHECKED);
    lv_style_set_border_color(&style_radio_chk, lv_palette_main(LV_PALETTE_RED));
}

void lv_create_canvas(lv_obj_t * par)
{
    static lv_color_t cbuf[LV_CANVAS_BUF_SIZE_INDEXED_1BIT(CANVAS_WIDTH, CANVAS_HEIGHT)];
    canvas = lv_canvas_create(par);
    lv_canvas_set_buffer(canvas, cbuf, CANVAS_WIDTH, CANVAS_HEIGHT, LV_IMG_CF_INDEXED_1BIT);
    lv_obj_align(canvas, LV_ALIGN_CENTER, CANVAS_X_OFFSET, CANVAS_Y_OFFSET);

    lv_canvas_set_palette(canvas, 0, lv_color_black());
    lv_canvas_set_palette(canvas, 1, lv_color_white());

    canvas_bg.full=0;
    canvas_fg.full=1;
    canvas_pen_color=lv_color_black();

    //lv_canvas_fill_bg(canvas, canvas_bg, LV_OPA_COVER);

    static lv_style_t style_knob;
    lv_style_init(&style_knob);
    lv_style_set_pad_all(&style_knob, 15);
    lv_style_set_radius(&style_knob, LV_RADIUS_CIRCLE);

    canvas_cw = lv_colorwheel_create(par, true);
    lv_obj_set_size(canvas_cw, 150, 150);
    lv_obj_set_style_arc_width(canvas_cw, 15, LV_PART_MAIN);
    lv_obj_add_style(canvas_cw, &style_knob, LV_PART_KNOB);
    lv_obj_align(canvas_cw, LV_ALIGN_LEFT_MID, 30, -30);

    lv_obj_add_event_cb(canvas_cw, pen_event_handler, LV_EVENT_PRESSED, NULL);

    canvas_arc = lv_arc_create(par);
    lv_obj_set_size(canvas_arc, 150, 150);
    lv_arc_set_rotation(canvas_arc, 0);
    lv_arc_set_bg_angles(canvas_arc, 0, 360);
    lv_arc_set_value(canvas_arc, 10);
    lv_obj_set_style_arc_width(canvas_arc, 15, LV_PART_MAIN);
    lv_obj_set_style_arc_width(canvas_arc, 15, LV_PART_INDICATOR);
    lv_obj_add_style(canvas_arc, &style_knob, LV_PART_KNOB);
    lv_obj_align(canvas_arc, LV_ALIGN_RIGHT_MID, -30, -30);

    lv_obj_add_event_cb(canvas_arc, pen_event_handler, LV_EVENT_PRESSED, NULL);

    lv_obj_t *title = lv_label_create(par);
    lv_label_set_text(title, "Drawing area (Canvas)");
    lv_obj_align_to(title, canvas, LV_ALIGN_OUT_TOP_MID, 0, -10);

    lv_obj_t *title_cw = lv_label_create(par);
    lv_label_set_text(title_cw, "Pen color");
    lv_obj_align_to(title_cw, canvas_cw, LV_ALIGN_OUT_TOP_MID, 0, -20);

    lv_obj_t *title_arc = lv_label_create(par);
    lv_label_set_text(title_arc, "Pen size");
    lv_obj_align_to(title_arc, canvas_arc, LV_ALIGN_OUT_TOP_MID, 0, -20);

    canvas_btn_clear = lv_btn_create(par);
    lv_obj_align_to(canvas_btn_clear, canvas, LV_ALIGN_OUT_BOTTOM_MID, -40, 5);
    lv_obj_set_size(canvas_btn_clear, 120, 40);
    lv_obj_add_event_cb(canvas_btn_clear, btn_clear_canvas_event_cb, LV_EVENT_ALL, NULL);

    lv_obj_t * label_btn_clear = lv_label_create(canvas_btn_clear);
    lv_label_set_text(label_btn_clear, "clear");
    lv_obj_align(label_btn_clear, LV_ALIGN_CENTER, 0, 0);

    lv_obj_clear_flag(canvas_btn_clear, LV_OBJ_FLAG_SCROLL_ON_FOCUS);

    lv_group_remove_obj(canvas_btn_clear);

    canvas_area.x1= 400-(CANVAS_WIDTH>>1)+CANVAS_X_OFFSET;
    canvas_area.x2= canvas_area.x1+CANVAS_WIDTH;
    canvas_area.y1= 240-(CANVAS_HEIGHT>>1)+CANVAS_Y_OFFSET;
    canvas_area.y2= canvas_area.y1+CANVAS_HEIGHT;
}

void lv_create_win_sensors(void)
{
    /*Create a window*/
    lv_obj_t * win = lv_win_create(lv_scr_act(), 50);
    lv_win_add_title(win, "Sensors");
    lv_obj_t * cont = lv_win_get_content(win);

    /*Add control button to the header*/
    lv_obj_t * close_btn = lv_win_add_btn(win, LV_SYMBOL_CLOSE, 45);
    lv_obj_add_event_cb(close_btn, close_win_sensors_cb, LV_EVENT_ALL, NULL);
    lv_obj_set_style_bg_color(close_btn, lv_palette_main(LV_PALETTE_RED), LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(close_btn, lv_palette_darken(LV_PALETTE_RED, 4), LV_STATE_PRESSED);

    static lv_style_t style_cont;
    lv_style_init(&style_cont);
    lv_style_set_pad_all(&style_cont, 0);
    lv_obj_add_style(cont, &style_cont, LV_STATE_DEFAULT);

    tabview_sensors = lv_tabview_create(cont, LV_DIR_BOTTOM, 50);
    lv_obj_t *tab_adc = lv_tabview_add_tab(tabview_sensors, "ADC");
    lv_obj_t *tab_accel = lv_tabview_add_tab(tabview_sensors, "Accel");
    lv_obj_t *tab_touch = lv_tabview_add_tab(tabview_sensors, "Touch");
    lv_obj_add_event_cb(tabview_sensors, tab_btns_event_cb, LV_EVENT_ALL, NULL);

    txt_bat_volts = lv_label_create(tab_adc);
    lv_obj_set_pos(txt_bat_volts, 420, 295);
    lv_label_set_text(txt_bat_volts, "");

    lv_create_meter_pin(tab_adc);
    lv_create_meter_temp(tab_adc);
    lv_create_chart(tab_accel);

    txt_touch_data = lv_label_create(tab_touch);
    lv_obj_align(txt_touch_data, LV_ALIGN_BOTTOM_LEFT, 0, 0);
    lv_label_set_text(txt_touch_data, "");

    lv_create_canvas(tab_touch);

    sensors_refresh_task=lv_timer_create((lv_timer_cb_t) lv_update_win_sensors, 50, NULL);
}

void lv_update_win_sensors(void)
{
    char data_string[60];
    int16_t ax,ay,az, pin;
    float bat, te, ti;

    switch(lv_tabview_get_tab_act(tabview_sensors))
    {
        case 0:
            ADCSensors_Read();
            pin=ADCSensors_getPINDiodeRaw()/41;
            bat=ADCSensors_getBatteryV();
            te=ADCSensors_getTempExternalC();
            ti=ADCSensors_getTempInternalC();

            lv_meter_set_indicator_value(meter_pin, pin_diode, pin);
            lv_meter_set_indicator_end_value(meter_temp, temp_int, (int16_t)ti);
            lv_meter_set_indicator_end_value(meter_temp, temp_ext, (int16_t)te);

            sprintf(data_string,"Ext. temp: %d 'C",(int)te);
            lv_label_set_text(txt_ext_temp, data_string);
            sprintf(data_string,"CPU temp: %d 'C",(int)ti);
            lv_label_set_text(txt_int_temp, data_string);

            sprintf(data_string,"%d",(int)pin);
            lv_label_set_text(txt_pin, data_string);
            sprintf(data_string,"battery voltage: %d mV",(int)(bat*1000));
            lv_label_set_text(txt_bat_volts, data_string);

            break;
        case 1:
            ax=0;
            ay=0;
            az=0;

            if((radio_id==0)||(radio_id==3))
                ax=(int16_t)ADXL345_ReadX();
            if((radio_id==1)||(radio_id==3))
                ay=(int16_t)ADXL345_ReadY();
            if((radio_id==2)||(radio_id==3))
                az=(int16_t)ADXL345_ReadZ();
            switch(radio_id)
            {
                case 0:
                    ax=(int16_t)ADXL345_ReadX();
                    lv_chart_set_next_value(chart_accel, ser_x, (lv_coord_t)ax);
                    break;
                case 1:
                    ay=(int16_t)ADXL345_ReadY();
                    lv_chart_set_next_value(chart_accel, ser_y, (lv_coord_t)ay);
                    break;
                case 2:
                    az=(int16_t)ADXL345_ReadZ();
                    lv_chart_set_next_value(chart_accel, ser_z, (lv_coord_t)az);
                    break;
                case 3:
                    ADXL345_ReadXYZ((uint16_t*)&ax, (uint16_t*)&ay, (uint16_t*)&az);
                    lv_chart_set_next_value(chart_accel, ser_x, (lv_coord_t)ax);
                    lv_chart_set_next_value(chart_accel, ser_y, (lv_coord_t)ay);
                    lv_chart_set_next_value(chart_accel, ser_z, (lv_coord_t)az);
                    break;
            }

            sprintf(data_string,"ax: %d",ax);
            lv_label_set_text(txt_ax, data_string);
            sprintf(data_string,"ay: %d",ay);
            lv_label_set_text(txt_ay, data_string);
            sprintf(data_string,"az: %d",az);
            lv_label_set_text(txt_az, data_string);
            break;
        case 2:
            TSC2006_readXYCalibrated((uint16_t *)&ax, (uint16_t *)&ay);

            lv_disp_t * disp = lv_disp_get_default();
            lv_disp_rot_t rot=lv_disp_get_rotation(disp);

            switch(rot)
            {
                case LV_DISP_ROT_NONE:
                    break;
                case LV_DISP_ROT_90:
                    az=ax; //az used as temp var
                    ax=(int16_t)lv_disp_get_hor_res(disp)-ay;
                    ay=az;
                    break;
                case LV_DISP_ROT_180:
                    ax=(int16_t)lv_disp_get_hor_res(disp)-ax;
                    ay=(int16_t)lv_disp_get_ver_res(disp)-ay;
                    break;
                case LV_DISP_ROT_270:
                    az=ax; //az used as temp var
                    ax=ay;
                    ay=(int16_t)lv_disp_get_ver_res(disp)-az;
                    break;
            }

            sprintf(data_string,"RAW: x: %d y: %d  CAL.: x: %d y: %d",TSC2006_readX(),TSC2006_readY(), ax, ay);
            lv_label_set_text(txt_touch_data, data_string);

            canvas_pen_size=lv_arc_get_value(canvas_arc)/5;
            if(canvas_pen_color.full!=lv_colorwheel_get_rgb(canvas_cw).full)
            {
                canvas_pen_color=lv_colorwheel_get_rgb(canvas_cw);
                lv_canvas_set_palette(canvas, 1, canvas_pen_color);
                lv_obj_invalidate(canvas);
            }

            if(ax>=canvas_area.x1&&ax<canvas_area.x2)
            {
                if(ay>=canvas_area.y1&&ay<canvas_area.y2)
                {
                    lv_obj_clear_flag(lv_tabview_get_content(tabview_sensors), LV_OBJ_FLAG_SCROLLABLE);

                    uint32_t x;
                    uint32_t y;

                    for(y = (ay-canvas_area.y1-canvas_pen_size/2); y <(ay-canvas_area.y1+canvas_pen_size/2); y++)
                    {

                        for(x = (ax-canvas_area.x1-canvas_pen_size/2); x < (ax-canvas_area.x1+canvas_pen_size/2); x++)
                        {
                            lv_canvas_set_px_color(canvas, x, y, canvas_fg);
                        }
                    }
                }
            }
            else
            {
                lv_obj_add_flag(lv_tabview_get_content(tabview_sensors), LV_OBJ_FLAG_SCROLLABLE);
            }


            break;
    }
}

