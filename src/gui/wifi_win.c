/*
 * Author: J. Bajic, 2022.
 */

#include "board_hw/wifi/wifi_weather_demo.h"
#include "board_hw/misc/buzzer.h"
#include "board_hw/misc/rgb_led.h"
#include "gui/wifi_win.h"
#include "gui/main_win.h"
#include "gui/obj/pswd_obj.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

lv_obj_t *win;
lv_timer_t *wifi_refresh_task;
lv_obj_t *txt_status, *txt_weather, *txt_mbox_connect;
lv_obj_t *weather_img;
lv_obj_t *mbox_connect, *wifi_pswd;

char ap_ssid[20]="MyAP";
char ap_pswd[20]="12345678";

char city[20]="N/A";
char temperature[6]="0";
char weather[20]="N/A";
char icon[5]="01d";
char weather_text[55]={};

uint8_t wifi_state=WIFI_DISCONNECTED;

extern const lv_img_dsc_t d01;
extern const lv_img_dsc_t d02;
extern const lv_img_dsc_t d03;
extern const lv_img_dsc_t d04;
extern const lv_img_dsc_t d09;
extern const lv_img_dsc_t d10;
extern const lv_img_dsc_t d11;
extern const lv_img_dsc_t d13;
extern const lv_img_dsc_t d50;
extern const lv_img_dsc_t n01;
extern const lv_img_dsc_t n02;
extern const lv_img_dsc_t n10;

extern uint8_t buzzer_audio_enable;

static void lv_create_pswd(lv_obj_t * par);
static void lv_create_connect_mbox(lv_obj_t * par);

static void btn_debug_event_cb(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    if(code == LV_EVENT_RELEASED)
    {
        if(buzzer_audio_enable)BUZZER_ClickSound();
        if(wifi_state==WIFI_DISCONNECTED)
        {
            WIFI_Exec((_i8*)ap_ssid, (_i8*)ap_pswd);
        }
        else
        {
            lv_label_set_text(txt_status, "Status: Disconnect from AP first");
        }

    }
}
static void wifi_pswd_event_cb(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_current_target(e);
    if(code == LV_EVENT_CANCEL)
    {
        //nothing to do
    }
    if(code == LV_EVENT_READY)
    {
       lv_pswd_get_name(obj, ap_ssid);
       lv_pswd_get_passkey(obj, ap_pswd);
    }
}
static void connect_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_current_target(e);

    if(code == LV_EVENT_VALUE_CHANGED)
    {

        char *txt=(char *)lv_msgbox_get_active_btn_text(obj);
        if(!strcmp(txt, "Connect"))
        {
            if(buzzer_audio_enable)BUZZER_ClickSound();
            if(wifi_state==WIFI_DISCONNECTED)
            {
                wifi_state=WIFI_CONFIG;
                lv_label_set_text(txt_mbox_connect, "Status: Configuring...");
            }
            else
            {
                lv_label_set_text(txt_mbox_connect, "Already connected");
            }
        }
        if(!strcmp(txt, "Cancel"))
        {
            if(buzzer_audio_enable)BUZZER_ClickSound();
            lv_msgbox_close(mbox_connect);
        }
    }
}

static void  btn_connect_event_cb(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    if(code == LV_EVENT_RELEASED)
    {
        if(buzzer_audio_enable)BUZZER_ClickSound();
        lv_obj_t * cont = lv_win_get_content(win);
        lv_create_connect_mbox(cont);
        lv_group_focus_obj(lv_msgbox_get_btns(mbox_connect));
        lv_group_focus_freeze(lv_group_get_default(), true);
    }
}
static void  btn_disconnect_event_cb(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    if(code == LV_EVENT_RELEASED)
    {
        if(buzzer_audio_enable)BUZZER_ClickSound();
        if(wifi_state==WIFI_CONNECTED)
        {
            wifi_state=WIFI_DISCONNECT;
        }
    }
}
static void btn_ap_event_cb(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    if(code == LV_EVENT_RELEASED)
    {
        if(buzzer_audio_enable)BUZZER_ClickSound();
        lv_obj_t * cont = lv_win_get_content(win);
        lv_create_pswd(cont);
        lv_group_focus_obj(lv_pswd_get_kb(wifi_pswd));
        lv_group_focus_freeze(lv_group_get_default(), true);
    }
}

static void btn_refresh_event_cb(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    if(code == LV_EVENT_RELEASED)
    {
        if(buzzer_audio_enable)BUZZER_ClickSound();
        if(wifi_state==WIFI_CONNECTED)
        {
            lv_label_set_text(txt_status, "Status: Acquiring data...");
            wifi_state=WIFI_GET_DATA;
        }
        else
        {
            lv_label_set_text(txt_status, "Status: Connect to AP first");
        }
    }
}

static void close_win_wifi_cb(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);

    if(code == LV_EVENT_RELEASED)
    {
        if(buzzer_audio_enable)BUZZER_ClickSound();
        lv_timer_del(wifi_refresh_task);
        lv_obj_del(win);
        lv_create_win_main();
    }
}

static void updateWeatherIcon(char *icon)
{
    if(strcmp(icon,"01d")==0)lv_img_set_src(weather_img, &d01);
    else if(strcmp(icon,"01n")==0)lv_img_set_src(weather_img, &n01);
    else if(strcmp(icon,"02d")==0)lv_img_set_src(weather_img, &d02);
    else if(strcmp(icon,"02n")==0)lv_img_set_src(weather_img, &n02);
    else if(strcmp(icon,"10d")==0)lv_img_set_src(weather_img, &d10);
    else if(strcmp(icon,"10n")==0)lv_img_set_src(weather_img, &n10);
    else if((strcmp(icon,"03d")==0) || (strcmp(icon,"03n")==0))lv_img_set_src(weather_img, &d03);
    else if((strcmp(icon,"04d")==0) || (strcmp(icon,"04n")==0))lv_img_set_src(weather_img, &d04);
    else if((strcmp(icon,"09d")==0) || (strcmp(icon,"09n")==0))lv_img_set_src(weather_img, &d09);
    else if((strcmp(icon,"11d")==0) || (strcmp(icon,"11n")==0))lv_img_set_src(weather_img, &d11);
    else if((strcmp(icon,"13d")==0) || (strcmp(icon,"13n")==0))lv_img_set_src(weather_img, &d13);
    else if((strcmp(icon,"50d")==0) || (strcmp(icon,"50n")==0))lv_img_set_src(weather_img, &d50);
    else lv_img_set_src(weather_img, &d01);;
}

static void lv_create_pswd(lv_obj_t * par)
{
    wifi_pswd=lv_pswd_create(par);
    lv_obj_align(wifi_pswd, LV_ALIGN_CENTER, -140, -30);
    lv_obj_add_event_cb(wifi_pswd, wifi_pswd_event_cb, LV_EVENT_ALL,  NULL);
}
static void lv_create_connect_mbox(lv_obj_t * par)
{
    static const char * btns[] ={"Connect", "Cancel", ""};

    mbox_connect = lv_msgbox_create(par, "Connect to AP", "Status: Disconnected", btns, false);
    txt_mbox_connect=lv_msgbox_get_text(mbox_connect);
    lv_obj_t *btns_mbox_connect=lv_msgbox_get_btns(mbox_connect);
    lv_obj_set_size(btns_mbox_connect, 300,50);
    lv_obj_set_width(mbox_connect, 350);
    lv_obj_add_event_cb(mbox_connect, connect_event_handler, LV_EVENT_ALL, NULL);
    lv_obj_align(mbox_connect, LV_ALIGN_CENTER, -140, 20);
}

void lv_create_win_wifi(void)
{
    /*Create a window*/
    win = lv_win_create(lv_scr_act(), 50);
    lv_win_add_title(win, "Wifi Weather Demo");
    lv_obj_t * cont = lv_win_get_content(win);

    /*Add control button to the header*/
    lv_obj_t * close_btn = lv_win_add_btn(win, LV_SYMBOL_CLOSE,45);
    lv_obj_add_event_cb(close_btn, close_win_wifi_cb, LV_EVENT_ALL, NULL);
    lv_obj_set_style_bg_color(close_btn, lv_palette_main(LV_PALETTE_RED), LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(close_btn, lv_palette_darken(LV_PALETTE_RED, 4), LV_STATE_PRESSED);

    txt_status = lv_label_create(cont);
    lv_obj_align(txt_status, LV_ALIGN_TOP_LEFT, 10, 0);
    if(wifi_state==WIFI_DISCONNECTED)
        lv_label_set_text(txt_status, "Status: Disconnected");
    else
    {
        sprintf(weather_text,"Status: Connected to %s", ap_ssid);
        lv_label_set_text(txt_status, weather_text);
    }

    static lv_style_t style_weather;
    lv_style_init(&style_weather);
    lv_style_set_radius(&style_weather, 10);
    lv_style_set_bg_opa(&style_weather, LV_OPA_COVER);
    lv_style_set_bg_opa(&style_weather, LV_OPA_10);
    lv_style_set_bg_color(&style_weather, lv_palette_main(LV_PALETTE_YELLOW));
    lv_style_set_border_opa(&style_weather, LV_OPA_40);
    lv_style_set_border_color(&style_weather, lv_palette_main(LV_PALETTE_GREY));
    lv_style_set_border_width(&style_weather, 2);
    lv_style_set_pad_all(&style_weather, 5);

    lv_obj_t *weather_info = lv_obj_create(cont);
    lv_obj_align(weather_info, LV_ALIGN_TOP_LEFT, 10, 60);
    lv_obj_add_style(weather_info, &style_weather, LV_STATE_DEFAULT);
    lv_obj_set_width(weather_info, 300);
    lv_obj_set_height(weather_info, 135);

    txt_weather = lv_label_create(weather_info);
    lv_obj_align(txt_weather, LV_ALIGN_TOP_LEFT, 20, 25);
    lv_label_set_text(txt_weather, "none");

    weather_img = lv_img_create(weather_info);
    lv_obj_align(weather_img, LV_ALIGN_TOP_LEFT, 180, 0);
    lv_img_set_src(weather_img, &d01);
    updateWeatherIcon(icon);
    int temp=atoi(temperature);
    sprintf(weather_text,"%s\n%d 'C\n%s", city,temp,weather);
    lv_label_set_text(txt_weather, weather_text);

    lv_obj_t * btn_debug = lv_btn_create(cont);
    lv_obj_align(btn_debug, LV_ALIGN_CENTER, 300, 150);
    lv_obj_set_size(btn_debug, 140, 80);
    lv_obj_add_event_cb(btn_debug, btn_debug_event_cb, LV_EVENT_ALL, NULL);
    lv_obj_t * label_btn_debug = lv_label_create(btn_debug);
    lv_label_set_text(label_btn_debug, "Debug");
    lv_obj_center(label_btn_debug);

    lv_obj_t * btn_ap = lv_btn_create(cont);
    lv_obj_align(btn_ap, LV_ALIGN_CENTER, -300, 150);
    lv_obj_set_size(btn_ap, 140, 80);
    lv_obj_add_event_cb(btn_ap, btn_ap_event_cb, LV_EVENT_ALL, NULL);
    lv_obj_t * label_btn_ap = lv_label_create(btn_ap);
    lv_label_set_text(label_btn_ap, "Setup AP");
    lv_obj_center(label_btn_ap);

    lv_obj_t * btn_connect = lv_btn_create(cont);
    lv_obj_align(btn_connect, LV_ALIGN_CENTER, -140, 150);
    lv_obj_set_size(btn_connect, 140, 80);
    lv_obj_add_event_cb(btn_connect, btn_connect_event_cb, LV_EVENT_ALL, NULL);
    lv_obj_t * label_btn_connect = lv_label_create(btn_connect);
    lv_label_set_text(label_btn_connect, "Connect");
    lv_obj_center(label_btn_connect);

    lv_obj_t * btn_disconnect = lv_btn_create(cont);
    lv_obj_align(btn_disconnect, LV_ALIGN_CENTER, 20, 150);
    lv_obj_set_size(btn_disconnect, 140, 80);
    lv_obj_add_event_cb(btn_disconnect, btn_disconnect_event_cb, LV_EVENT_ALL, NULL);
    lv_obj_t * label_btn_disconnect = lv_label_create(btn_disconnect);
    lv_label_set_text(label_btn_disconnect, "Disconnect");
    lv_obj_center(label_btn_disconnect);

    //debug btn
    lv_obj_t * btn_refresh = lv_btn_create(cont);
    lv_obj_align(btn_refresh, LV_ALIGN_CENTER, 300, -150);
    lv_obj_set_size(btn_refresh, 140, 80);
    lv_obj_add_event_cb(btn_refresh, btn_refresh_event_cb, LV_EVENT_ALL, NULL);

    lv_obj_t *img_btn_refresh = lv_img_create(btn_refresh);
    lv_img_set_src(img_btn_refresh, LV_SYMBOL_REFRESH);
    lv_obj_align(img_btn_refresh, LV_ALIGN_CENTER, 0, -15);

    lv_obj_t * label_btn_refresh = lv_label_create(btn_refresh);
    lv_label_set_text(label_btn_refresh, "Refresh");
    lv_obj_align(label_btn_refresh, LV_ALIGN_CENTER, 0, 15);

    wifi_refresh_task=lv_timer_create((lv_timer_cb_t) lv_update_win_wifi, 100, NULL);

    WIFI_initializeAppVariables();
}

void lv_update_win_wifi(void)
{
    _i32 retVal = -1;

    switch(wifi_state)
    {
        case WIFI_DISCONNECTED://Disconnected
            //standby
            break;
        case WIFI_CONFIG: //Initializing
            retVal = WIFI_configureToDefaultState();
            if(retVal < 0)
            {
                lv_label_set_text(txt_mbox_connect, "Status: Failed at Config");
                wifi_state=WIFI_DISCONNECTED;
            }
            else
            {
                wifi_state=WIFI_START;
                lv_label_set_text(txt_mbox_connect, "Status: Starting...");
            }
            break;
        case WIFI_START://Starting device
            retVal = sl_Start(0, 0, 0);
            if ((retVal < 0) || (ROLE_STA != retVal) )
            {
                lv_label_set_text(txt_mbox_connect, "Status: Failed at Start");
                wifi_state=WIFI_DISCONNECTED;
            }
            else
            {
                wifi_state=WIFI_CONNECT;
                lv_label_set_text(txt_mbox_connect, "Status: Connecting...");
            }
            break;
        case WIFI_CONNECT://Connecting
            retVal = WIFI_establishConnectionWithAP((_i8*)ap_ssid, (_i8*)ap_pswd);
            if (retVal < 0)
            {
                lv_label_set_text(txt_mbox_connect, "Status: Failed at Connect");
                wifi_state=WIFI_DISCONNECTED;
            }
            else
            {
                wifi_state=WIFI_CONNECTED;
                lv_msgbox_close(mbox_connect);
                sprintf(weather_text,"Status: Connected to %s", ap_ssid);
                lv_label_set_text(txt_status, weather_text);
            }
            break;
        case WIFI_CONNECTED: //Connected
            //standby
            break;
        case WIFI_GET_DATA://Getting data
            retVal = WIFI_getWeather();
            if(retVal < 0)
            {
                wifi_state=WIFI_CONNECTED;
                lv_label_set_text(txt_status, "Status: Failed at Data Get");
            }
            else
            {
                WIFI_extractWeatherData(city,temperature,weather,icon);
                int temp=atoi(temperature);
                sprintf(weather_text,"%s\n%d 'C\n%s", city,temp,weather);
                lv_label_set_text(txt_weather, weather_text);
                updateWeatherIcon(icon);
                wifi_state=WIFI_CONNECTED;
                sprintf(weather_text,"Status: Connected to %s", ap_ssid);
                lv_label_set_text(txt_status, weather_text);
            }

            break;
        case WIFI_DISCONNECT://Disconnecting
            retVal = WIFI_disconnectFromAP();
            if (retVal < 0)
            {
                lv_label_set_text(txt_status, "Status: Failed at Disconnect");
                wifi_state=WIFI_DISCONNECTED;
            }
            else
            {
                wifi_state=WIFI_DISCONNECTED;
                sl_Stop(0xFF);
                lv_label_set_text(txt_status, "Status: Disconnected");
            }
            break;

    }
}


