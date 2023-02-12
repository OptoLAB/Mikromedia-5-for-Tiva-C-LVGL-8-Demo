/*
 * Author: J. Bajic, 2022.
 */

#include "board_hw/board_hw.h"
#include "fatfs/ff.h"
#include "gui/main_win.h"
#include "gui/sensors_win.h"
#include "gui/debug_win.h"
#include "gui/wifi_win.h"
#include "gui/mp3_win.h"
#include "gui/obj/clock_obj.h"
#include "gui/images/gears_anim.h"
#include <stdio.h>

lv_obj_t *main_win;
lv_obj_t *txt_date, *txt_time;
lv_obj_t *pwr_stat, *bat_stat, *sd_stat, *audio_stat, *wifi_stat, *theme_stat, *btn_txt_time, *btn_txt_date;;
lv_timer_t *main_refresh_task;
lv_obj_t  *my_calendar, *my_clock;
uint8_t buzzer_audio_enable=1;
//5%  25%   50%    75%
uint16_t bat_level[4]={3600, 3750, 3840, 3980}; //for testing purpose

uint8_t calendar_visible=0;
uint8_t clock_visible=0;
uint8_t current_theme=0;
//FATFS myFAT;
//char SDPath[4]={};
extern lv_font_t ni7seg_36;
extern const lv_img_dsc_t lvgl_logo;
extern const lv_img_dsc_t ti_logo;
extern const lv_img_dsc_t mikroe_logo;
extern uint8_t wifi_state;

//static void lv_create_calendar(lv_obj_t * par);
//static void lv_create_clock(lv_obj_t * par);


void close_win_main(void)
{
    lv_timer_del(main_refresh_task);
    //f_mount(0, SDPath, 1);
    lv_obj_del(main_win);
}

static void btn_sensors_event_cb(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    if(code == LV_EVENT_CLICKED)
    {
        if(buzzer_audio_enable)BUZZER_ClickSound();
        lv_create_win_sensors();
        close_win_main();
    }
}

static void btn_wifi_event_cb(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    if(code == LV_EVENT_CLICKED)
    {
        if(buzzer_audio_enable)BUZZER_ClickSound();
        lv_create_win_wifi();
        close_win_main();
    }
}
static void btn_mp3_event_cb(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    if(code == LV_EVENT_CLICKED)
    {
        if(buzzer_audio_enable)BUZZER_ClickSound();
        lv_create_win_mp3();
        close_win_main();
    }
}

static void btn_debug_event_cb(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    if(code == LV_EVENT_CLICKED)
    {
        if(buzzer_audio_enable)BUZZER_ClickSound();
        close_win_main();
        lv_create_win_debug();

    }
}
static void theme_event_cb(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    if(code == LV_EVENT_CLICKED)
    {
        current_theme^=0x01;
        if(buzzer_audio_enable)BUZZER_ClickSound();

        lv_disp_t * disp = lv_disp_get_default();
        lv_theme_t * th = lv_disp_get_theme(disp);
        lv_theme_default_init(disp, th->color_secondary, th->color_primary, current_theme, th->font_normal);
        close_win_main();
        lv_create_win_main();
    }
}
static void audio_event_cb(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    if(code == LV_EVENT_CLICKED)
    {
        buzzer_audio_enable^=0x01;
        if(buzzer_audio_enable)BUZZER_ClickSound();
    }
}

static void btn_txt_time_event_cb(lv_event_t *e)
{
    struct tm rtc_time;
    lv_clock_time_t clock_time;

    lv_event_code_t code = lv_event_get_code(e);

    if(code == LV_EVENT_VALUE_CHANGED)
    {
        SYSRTC_GetDateTime(&rtc_time);
        if(buzzer_audio_enable)BUZZER_ClickSound();
        if(!clock_visible)
        {
            if(calendar_visible)lv_obj_set_pos(my_calendar, 497,3+75);

            clock_time.hour=rtc_time.tm_hour;
            clock_time.min=rtc_time.tm_min;
            clock_time.sec=rtc_time.tm_sec;

            lv_clock_set_time(my_clock,&clock_time);

            lv_obj_clear_flag(my_clock, LV_OBJ_FLAG_HIDDEN);
            lv_clock_t * clock = (lv_clock_t *)my_clock;
            lv_group_focus_obj(clock->hour);

            clock_visible=1;
        }
        else
        {
            if(calendar_visible)lv_obj_set_pos(my_calendar, 497,3);

            clock_time=lv_clock_get_time(my_clock);

            rtc_time.tm_hour=(int)clock_time.hour;
            rtc_time.tm_min=(int)clock_time.min;
            rtc_time.tm_sec=(int)clock_time.sec;

            SYSRTC_SetDateTime(&rtc_time);

            lv_obj_add_flag(my_clock, LV_OBJ_FLAG_HIDDEN);
            clock_visible=0;
        }
    }
}

static void btn_txt_date_event_cb(lv_event_t *e)
{
    struct tm rtc_time;
    lv_calendar_date_t date;


    lv_event_code_t code = lv_event_get_code(e);
    if(code == LV_EVENT_VALUE_CHANGED)
    {
        SYSRTC_GetDateTime(&rtc_time);

        if(!calendar_visible)
        {
            lv_calendar_set_today_date(my_calendar, rtc_time.tm_year-100+2000, rtc_time.tm_mon, rtc_time.tm_mday);
            lv_calendar_set_showed_date(my_calendar, rtc_time.tm_year-100+2000, rtc_time.tm_mon);

            lv_obj_clear_flag(my_calendar, LV_OBJ_FLAG_HIDDEN);
            if(clock_visible)lv_obj_set_pos(my_calendar, 497,3+75);

            lv_group_focus_obj(lv_calendar_get_btnmatrix(my_calendar));
            calendar_visible=1;
        }
        else
        {
            if(buzzer_audio_enable)BUZZER_ClickSound();

            date=*lv_calendar_get_today_date(my_calendar);

            rtc_time.tm_year=date.year-2000+100;
            rtc_time.tm_mon=date.month;
            rtc_time.tm_mday=date.day;

            SYSRTC_SetDateTime(&rtc_time);

            lv_obj_add_flag(my_calendar, LV_OBJ_FLAG_HIDDEN);
            calendar_visible=0;
        }
    }
}
static void calendar_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_current_target(e);

    if(code == LV_EVENT_CLICKED)
    {
        if(buzzer_audio_enable)BUZZER_ClickSound();
        lv_calendar_date_t date;
        if(lv_calendar_get_pressed_date(obj, &date))
        {
            lv_calendar_set_today_date(my_calendar, date.year, date.month, date.day);
        }
    }
}
static void calendar_arrow_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    if(code == LV_EVENT_VALUE_CHANGED)
    {
        if(buzzer_audio_enable)BUZZER_ClickSound();
    }
}

static void lv_create_calendar(lv_obj_t * par)
{
    struct tm rtc_time;

    my_calendar = lv_calendar_create(par);
    lv_obj_set_size(my_calendar, 300, 250);
    if(clock_visible)
        lv_obj_set_pos(my_calendar, 497,3+75);
    else
        lv_obj_set_pos(my_calendar, 497,3);

    lv_obj_t* my_calendar_arrow=lv_calendar_header_arrow_create(my_calendar);

    if(!calendar_visible)
    {
        lv_obj_add_flag(my_calendar, LV_OBJ_FLAG_HIDDEN);
        lv_obj_clear_state(btn_txt_date, LV_STATE_CHECKED);
    }
    else
    {
        SYSRTC_GetDateTime(&rtc_time);

        lv_calendar_set_today_date(my_calendar, rtc_time.tm_year-100+2000, rtc_time.tm_mon, rtc_time.tm_mday);
        lv_calendar_set_showed_date(my_calendar, rtc_time.tm_year-100+2000, rtc_time.tm_mon);

        lv_obj_clear_flag(my_calendar, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_state(btn_txt_date, LV_STATE_CHECKED);
    }

    lv_obj_add_event_cb(my_calendar, calendar_event_handler, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(my_calendar_arrow, calendar_arrow_event_handler, LV_EVENT_ALL, NULL);
}

static void lv_create_clock(lv_obj_t * par)
{
    lv_clock_time_t clock_time;
    struct tm rtc_time;

    my_clock =lv_clock_create(par);
    lv_obj_set_pos(my_clock, 537, 3);

    if(!clock_visible)
    {
        lv_obj_add_flag(my_clock, LV_OBJ_FLAG_HIDDEN);
        lv_obj_clear_state(btn_txt_time, LV_STATE_CHECKED);
    }
    else
    {
        SYSRTC_GetDateTime(&rtc_time);
        clock_time.hour=rtc_time.tm_hour;
        clock_time.min=rtc_time.tm_min;
        clock_time.sec=rtc_time.tm_sec;
        lv_clock_set_time(my_clock,&clock_time);

        lv_obj_clear_flag(my_clock, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_state(btn_txt_time, LV_STATE_CHECKED);
    }
}

void lv_create_win_main(void)
{
    /*Create a window*/
    lv_disp_t * disp = lv_disp_get_default();
    lv_theme_t * th = lv_disp_get_theme(disp);
    lv_color_t prim_color=th->color_primary;

    main_win = lv_win_create(lv_scr_act(), 40);
    lv_obj_t *title=lv_win_add_title(main_win, "mikromedia 5 for Tiva C Series");
    lv_obj_t *header=lv_win_get_header(main_win);
    lv_obj_t *cont=lv_win_get_content(main_win);

    lv_group_add_obj(lv_group_get_default(), main_win);
    static lv_style_t style_title;
    lv_style_init(&style_title);
    lv_style_set_text_color(&style_title, prim_color);
    lv_style_set_text_font(&style_title, &lv_font_montserrat_26);
    lv_obj_add_style(title, &style_title, LV_STATE_DEFAULT);

    static lv_style_t cont_style;
    lv_style_init(&cont_style);
    lv_style_set_pad_all(&cont_style, 0);
    if(current_theme)
        lv_style_set_bg_color(&cont_style, lv_palette_main(LV_PALETTE_GREY));
    else
        lv_style_set_bg_color(&cont_style, lv_palette_lighten(LV_PALETTE_GREY,4));

    lv_obj_add_style(cont, &cont_style, LV_STATE_DEFAULT);

    pwr_stat = lv_img_create(header);
    lv_img_set_src(pwr_stat, LV_SYMBOL_CHARGE);
    lv_obj_align(pwr_stat, LV_ALIGN_LEFT_MID, 0, 0);

    bat_stat = lv_img_create(header);
    lv_img_set_src(bat_stat, LV_SYMBOL_BATTERY_EMPTY);

    sd_stat = lv_img_create(header);
    lv_img_set_src(sd_stat, LV_SYMBOL_SD_CARD);

    static lv_style_t style_pr;
    lv_style_init(&style_pr);
    lv_style_set_text_color(&style_pr, prim_color);
    lv_style_set_text_opa(&style_pr, LV_OPA_30);

    static lv_style_t style_fc;
    lv_style_init(&style_fc);
    lv_style_set_radius(&style_fc, 3);
    lv_style_set_border_width(&style_fc, 2);
    lv_style_set_border_color(&style_fc, prim_color);
    lv_style_set_border_opa(&style_fc, LV_OPA_50);
    lv_style_set_text_align(&style_fc, LV_TEXT_ALIGN_CENTER);

    theme_stat = lv_img_create(header);
    lv_group_add_obj(lv_group_get_default(), theme_stat);
    lv_obj_add_style(theme_stat, &style_pr, LV_STATE_PRESSED);
    lv_obj_add_style(theme_stat, &style_fc, LV_STATE_FOCUSED);
    lv_img_set_src(theme_stat, LV_SYMBOL_TINT);
    lv_obj_add_flag(theme_stat, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_clear_flag(theme_stat, LV_OBJ_FLAG_CLICK_FOCUSABLE);
    lv_obj_add_flag(theme_stat, LV_OBJ_FLAG_CHECKABLE);
    lv_obj_add_event_cb(theme_stat, theme_event_cb, LV_EVENT_ALL, NULL);

    audio_stat = lv_img_create(header);
    lv_group_add_obj(lv_group_get_default(), audio_stat);
    lv_obj_add_style(audio_stat, &style_pr, LV_STATE_PRESSED);
    lv_obj_add_style(audio_stat, &style_fc, LV_STATE_FOCUSED);
    lv_img_set_src(audio_stat, LV_SYMBOL_VOLUME_MAX);
    lv_obj_add_flag(audio_stat, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_clear_flag(audio_stat, LV_OBJ_FLAG_CLICK_FOCUSABLE);
    lv_obj_add_flag(audio_stat, LV_OBJ_FLAG_CHECKABLE);
    lv_obj_add_event_cb(audio_stat, audio_event_cb, LV_EVENT_ALL, NULL);

    wifi_stat = lv_img_create(header);
    lv_img_set_src(wifi_stat, LV_SYMBOL_WIFI);
    lv_obj_add_flag(wifi_stat, LV_OBJ_FLAG_HIDDEN);

    static lv_style_t click_txt_style_pr;
    lv_style_init(&click_txt_style_pr);
    lv_style_set_radius(&click_txt_style_pr, 0);
    lv_style_set_bg_color(&click_txt_style_pr, prim_color);
    lv_style_set_bg_grad_color(&click_txt_style_pr, prim_color);
    lv_style_set_bg_opa(&click_txt_style_pr, LV_OPA_30);

    static lv_style_t click_txt_style_rel;
    lv_style_init(&click_txt_style_rel);
    lv_style_set_radius(&click_txt_style_rel, 0);
    lv_style_set_bg_opa(&click_txt_style_rel, LV_OPA_0);

    btn_txt_time= lv_btn_create(header);
    lv_obj_remove_style_all(btn_txt_time);                          /*Remove the style coming from the theme*/
    lv_obj_add_style(btn_txt_time, &click_txt_style_rel, 0);
    lv_obj_add_style(btn_txt_time, &click_txt_style_pr, LV_STATE_CHECKED);
    lv_obj_add_style(btn_txt_time, &style_fc, LV_STATE_FOCUSED);
    lv_obj_set_size(btn_txt_time, 65, 30);
    lv_obj_add_flag(btn_txt_time, LV_OBJ_FLAG_CHECKABLE);
    lv_obj_clear_flag(btn_txt_time, LV_OBJ_FLAG_CLICK_FOCUSABLE);
    lv_obj_add_event_cb(btn_txt_time, btn_txt_time_event_cb, LV_EVENT_ALL, NULL);

    txt_time = lv_label_create(btn_txt_time);
    lv_obj_center(txt_time);
    lv_label_set_text(txt_time, "00:00");
    lv_obj_align(txt_time, LV_ALIGN_CENTER, 0, 0);

    btn_txt_date= lv_btn_create(header);
    lv_obj_remove_style_all(btn_txt_date);                          /*Remove the style coming from the theme*/
    lv_obj_add_style(btn_txt_date, &click_txt_style_rel, 0);
    lv_obj_add_style(btn_txt_date, &click_txt_style_pr, LV_STATE_CHECKED);
    lv_obj_add_style(btn_txt_date, &style_fc, LV_STATE_FOCUSED);
    lv_obj_set_size(btn_txt_date, 100, 30);
    lv_obj_add_flag(btn_txt_date, LV_OBJ_FLAG_CHECKABLE);
    lv_obj_clear_flag(btn_txt_date, LV_OBJ_FLAG_CLICK_FOCUSABLE);
    lv_obj_add_event_cb(btn_txt_date, btn_txt_date_event_cb, LV_EVENT_ALL, NULL);

    txt_date = lv_label_create(btn_txt_date);
    lv_obj_center(txt_date);
    lv_label_set_text(txt_date, "00/00/00");
    lv_obj_align(txt_date, LV_ALIGN_CENTER, 0, 0);

    //sensors btn
    lv_obj_t * btn_sensors = lv_btn_create(cont);
    lv_obj_align(btn_sensors, LV_ALIGN_CENTER, -270, -120);
    lv_obj_set_size(btn_sensors, 140, 80);
    lv_obj_add_event_cb(btn_sensors, btn_sensors_event_cb, LV_EVENT_ALL, NULL);

    lv_obj_t *img_btn_sensors = lv_img_create(btn_sensors);
    lv_img_set_src(img_btn_sensors, LV_SYMBOL_EYE_OPEN);
    lv_obj_align(img_btn_sensors, LV_ALIGN_CENTER, 0, -15);

    lv_obj_t * label_btn_sensors = lv_label_create(btn_sensors);
    lv_label_set_text(label_btn_sensors, "Sensors");
    lv_obj_align(label_btn_sensors, LV_ALIGN_CENTER, 0, 15);

    //wifi btn
    lv_obj_t * btn_wifi = lv_btn_create(cont);
    lv_obj_align(btn_wifi, LV_ALIGN_CENTER, -90, -120);
    lv_obj_set_size(btn_wifi, 140, 80);
    lv_obj_add_event_cb(btn_wifi, btn_wifi_event_cb, LV_EVENT_ALL, NULL);

    lv_obj_t *img_btn_wifi = lv_img_create(btn_wifi);
    lv_img_set_src(img_btn_wifi, LV_SYMBOL_WIFI);
    lv_obj_align(img_btn_wifi, LV_ALIGN_CENTER, 0, -15);

    lv_obj_t * label_btn_wifi = lv_label_create(btn_wifi);
    lv_label_set_text(label_btn_wifi, "WiFi");
    lv_obj_align(label_btn_wifi, LV_ALIGN_CENTER, 0, 15);

    //mp3 btn
    lv_obj_t * btn_mp3 = lv_btn_create(cont);
    lv_obj_align(btn_mp3, LV_ALIGN_CENTER, 90, -120);
    lv_obj_set_size(btn_mp3, 140, 80);
    lv_obj_add_event_cb(btn_mp3, btn_mp3_event_cb, LV_EVENT_ALL, NULL);
    //lv_group_remove_obj(btn_mp3);

    lv_obj_t *img_btn_mp3 = lv_img_create(btn_mp3);
    lv_img_set_src(img_btn_mp3, LV_SYMBOL_AUDIO);
    lv_obj_align(img_btn_mp3, LV_ALIGN_CENTER, 0, -15);

    lv_obj_t * label_btn_mp3 = lv_label_create(btn_mp3);
    lv_label_set_text(label_btn_mp3, "MP3");
    lv_obj_align(label_btn_mp3, LV_ALIGN_CENTER, 0, 15);


    //debug btn
    lv_obj_t * btn_debug = lv_btn_create(cont);
    lv_obj_align(btn_debug, LV_ALIGN_CENTER, 270, -120);
    lv_obj_set_size(btn_debug, 140, 80);
    lv_obj_add_event_cb(btn_debug, btn_debug_event_cb, LV_EVENT_ALL, NULL);

    lv_obj_t *img_btn_debug = lv_img_create(btn_debug);
    lv_img_set_src(img_btn_debug, LV_SYMBOL_USB);
    lv_obj_align(img_btn_debug, LV_ALIGN_CENTER, 0, -15);

    lv_obj_t * label_btn_debug = lv_label_create(btn_debug);
    lv_label_set_text(label_btn_debug, "Debug");
    lv_obj_align(label_btn_debug, LV_ALIGN_CENTER, 0, 15);

    main_refresh_task=lv_timer_create((lv_timer_cb_t) lv_update_win_main, 50, NULL);

    lv_obj_t *img_mikroe = lv_img_create(cont);
    lv_obj_align(img_mikroe, LV_ALIGN_CENTER, -250, 150);
    lv_img_set_src(img_mikroe, &mikroe_logo);

    lv_obj_t *img_lvgl = lv_img_create(cont);
    lv_obj_align(img_lvgl, LV_ALIGN_CENTER, -5, 150);
    lv_img_set_src(img_lvgl, &lvgl_logo);

    lv_obj_t *img_ti = lv_img_create(cont);
    lv_obj_align(img_ti, LV_ALIGN_CENTER, 235, 150);
    lv_img_set_src(img_ti, &ti_logo);

    lv_obj_t *gears_anim=lv_create_gears_anim(cont);
    lv_obj_align(gears_anim, LV_ALIGN_CENTER, 0, 20);

    lv_create_clock(cont);
    lv_create_calendar(cont);
}

void lv_update_win_main(void)
{
    char data_string[30];

    uint16_t bat_volts=0;

    switch(PWR_GetStatus(&bat_volts))
    {
        case PWR_DC:
            lv_obj_clear_flag(pwr_stat, LV_OBJ_FLAG_HIDDEN);
            lv_obj_add_flag(bat_stat, LV_OBJ_FLAG_HIDDEN);
            lv_img_set_src(pwr_stat, LV_SYMBOL_POWER);
            break;
        case PWR_USB:
            lv_obj_clear_flag(pwr_stat, LV_OBJ_FLAG_HIDDEN);
            lv_obj_add_flag(bat_stat, LV_OBJ_FLAG_HIDDEN);
            lv_img_set_src(pwr_stat, LV_SYMBOL_USB);
            break;
        case PWR_BAT:
            lv_obj_clear_flag(pwr_stat, LV_OBJ_FLAG_HIDDEN);
            lv_obj_clear_flag(bat_stat, LV_OBJ_FLAG_HIDDEN);
            if(bat_volts<bat_level[0])lv_img_set_src(bat_stat, LV_SYMBOL_BATTERY_EMPTY);
            else if(bat_volts<bat_level[1])lv_img_set_src(bat_stat, LV_SYMBOL_BATTERY_1);
            else if(bat_volts<bat_level[2])lv_img_set_src(bat_stat, LV_SYMBOL_BATTERY_2);
            else if(bat_volts<bat_level[3])lv_img_set_src(bat_stat, LV_SYMBOL_BATTERY_3);
            else lv_img_set_src(bat_stat, LV_SYMBOL_BATTERY_FULL);
            break;
        case PWR_BAT_CHRG:
            lv_obj_clear_flag(pwr_stat, LV_OBJ_FLAG_HIDDEN);
            lv_obj_clear_flag(bat_stat, LV_OBJ_FLAG_HIDDEN);
            lv_img_set_src(pwr_stat, LV_SYMBOL_CHARGE);

            if(bat_volts<(bat_level[0]+250))lv_img_set_src(bat_stat, LV_SYMBOL_BATTERY_EMPTY);
            else if(bat_volts<(bat_level[1]+250))lv_img_set_src(bat_stat, LV_SYMBOL_BATTERY_1);
            else if(bat_volts<(bat_level[2]+250))lv_img_set_src(bat_stat, LV_SYMBOL_BATTERY_2);
            else if(bat_volts<(bat_level[3]+250))lv_img_set_src(bat_stat, LV_SYMBOL_BATTERY_3);
            else lv_img_set_src(bat_stat, LV_SYMBOL_BATTERY_FULL);
            break;
        case PWR_BAT_FLT:
            lv_obj_clear_flag(pwr_stat, LV_OBJ_FLAG_HIDDEN);
            lv_obj_add_flag(bat_stat, LV_OBJ_FLAG_HIDDEN);
            lv_img_set_src(pwr_stat, LV_SYMBOL_WARNING);
            break;
    }

    if(SD_isPresent())lv_obj_clear_flag(sd_stat, LV_OBJ_FLAG_HIDDEN);
    else lv_obj_add_flag(sd_stat, LV_OBJ_FLAG_HIDDEN);

    if(buzzer_audio_enable) lv_img_set_src(audio_stat, LV_SYMBOL_VOLUME_MAX);
    else lv_img_set_src(audio_stat, LV_SYMBOL_MUTE);

    if(!wifi_state)lv_obj_add_flag(wifi_stat, LV_OBJ_FLAG_HIDDEN);
    else lv_obj_clear_flag(wifi_stat, LV_OBJ_FLAG_HIDDEN);

    struct tm rtc_time;
    if(!SYSRTC_GetDateTime(&rtc_time))
    {
        sprintf(data_string,"%02d:%02d",rtc_time.tm_hour,rtc_time.tm_min);
        lv_label_set_text(txt_time, data_string);
        sprintf(data_string,"%02d/%02d/%02d",rtc_time.tm_mday,rtc_time.tm_mon,rtc_time.tm_year%100);
        lv_label_set_text(txt_date, data_string);
    }
}
