/*
 * Author: J. Bajic, 2022.
 */

#include "board_hw/mp3/MP3.h"
#include "board_hw/mp3/VS1053.h"
#include "board_hw/misc/rgb_led.h"
#include "board_hw/misc/buzzer.h"
#include "board_hw/tivaware_c_lib.h"
#include "fatfs/ff.h"
#include "gui/mp3_win.h"
#include "gui/main_win.h"
#include <stdio.h>

lv_obj_t *bar_playing_time, *txt_playing_time;
lv_obj_t *slider_volume, *txt_volume;
lv_timer_t *mp3_refresh_task;
lv_obj_t *txt_mp3;
lv_obj_t *selected_song;
lv_obj_t *spinner;
lv_obj_t * list_playlist;

FRESULT fr;
DIR dj;
FILINFO fno;
char song_path[300];
char song_folder[20]="music";

uint8_t play=0;
uint32_t playing_time=1;
int16_t mp3_vol=50;

extern uint8_t buzzer_audio_enable;
extern const lv_img_dsc_t music;

uint8_t playlist_populated=0;
uint8_t num_of_songs=0;
uint8_t max_num_of_songs=255;
uint8_t max_song_name_len=255;
lv_color_t prim_color;


static void find_prev(void)
{
    uint32_t index = lv_obj_get_index(selected_song);
    if(index > 0)
    {
        lv_obj_t *song_label=lv_obj_get_child(selected_song, 0);
        lv_label_set_long_mode(song_label, LV_LABEL_LONG_CLIP); //disable rolling

        lv_obj_clear_state(selected_song, LV_STATE_CHECKED);
        selected_song=lv_obj_get_child(list_playlist, index - 1);
        lv_obj_scroll_to_view(selected_song, LV_ANIM_ON);
        lv_obj_add_state(selected_song, LV_STATE_CHECKED);

        sprintf(song_path,"%s/%s",song_folder,(char*)lv_list_get_btn_text(list_playlist, selected_song));
        lv_label_set_text(txt_mp3, song_path);

        song_label=lv_obj_get_child(selected_song, 0);
        lv_label_set_long_mode(song_label, LV_LABEL_LONG_SCROLL_CIRCULAR); //enable rolling
    }
}
static void find_next(void)
{

    uint32_t index = lv_obj_get_index(selected_song);
    if(index < num_of_songs-1)
    {
        lv_obj_t *song_label=lv_obj_get_child(selected_song, 0);
        lv_label_set_long_mode(song_label, LV_LABEL_LONG_CLIP); //disable rolling

        lv_obj_clear_state(selected_song, LV_STATE_CHECKED);
        selected_song=lv_obj_get_child(list_playlist, index + 1);
        lv_obj_scroll_to_view(selected_song, LV_ANIM_ON);
        lv_obj_add_state(selected_song, LV_STATE_CHECKED);

        sprintf(song_path,"%s/%s",song_folder,(char*)lv_list_get_btn_text(list_playlist, selected_song));
        lv_label_set_text(txt_mp3, song_path);

        song_label=lv_obj_get_child(selected_song, 0);
        lv_label_set_long_mode(song_label, LV_LABEL_LONG_SCROLL_CIRCULAR); //enable rolling
    }
}

static void playlist_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *obj = lv_event_get_current_target(e);


    if(code == LV_EVENT_CLICKED)
    {
        if(buzzer_audio_enable)BUZZER_ClickSound();

        lv_obj_t *song_label=lv_obj_get_child(selected_song, 0);
        lv_label_set_long_mode(song_label, LV_LABEL_LONG_CLIP); //disable rolling

        lv_obj_clear_state(selected_song, LV_STATE_CHECKED);
        lv_obj_add_state(obj, LV_STATE_CHECKED);
        sprintf(song_path,"%s/%s",song_folder,(char*)lv_list_get_btn_text(list_playlist, obj));
        lv_label_set_text(txt_mp3, song_path);

        selected_song=obj;

        song_label=lv_obj_get_child(selected_song, 0);
        lv_label_set_long_mode(song_label, LV_LABEL_LONG_SCROLL_CIRCULAR); //enable rolling

    }
}
static void slider_volume_event_cb(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *obj = lv_event_get_current_target(e);

    if(code == LV_EVENT_VALUE_CHANGED)
    {
       char data_string[20]={};
       sprintf(data_string,"Volume %d%%", (int)lv_slider_get_value(obj));
       lv_label_set_text(txt_volume, data_string);
       mp3_vol=100-(uint8_t)lv_slider_get_value(obj);
       MP3_SetVolume(mp3_vol);
    }
    if(code == LV_EVENT_PRESSED)
    {
        if(buzzer_audio_enable)BUZZER_ClickSound();
    }
}

static void btn_play_event_cb(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    if(code == LV_EVENT_RELEASED)
    {
        if(buzzer_audio_enable)BUZZER_ClickSound();
        play=1;
        MP3_Play(song_path);
        playing_time=MP3_GetPlayingTime();
    }
}

static void btn_next_event_cb(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    if(code == LV_EVENT_RELEASED)
    {
        if(buzzer_audio_enable)BUZZER_ClickSound();
        find_next();
        MP3_Close();
        MP3_Play(song_path);

    }
}
static void btn_prev_event_cb(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    if(code == LV_EVENT_RELEASED)
    {
        if(buzzer_audio_enable)BUZZER_ClickSound();
        find_prev();
        MP3_Close();
        MP3_Play(song_path);
        playing_time=MP3_GetPlayingTime();
    }
}
static void btn_pause_event_cb(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    if(code == LV_EVENT_RELEASED)
    {
        if(buzzer_audio_enable)BUZZER_ClickSound();
        play=0;
    }
}
static void btn_stop_event_cb(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    if(code == LV_EVENT_RELEASED)
    {
        if(buzzer_audio_enable)BUZZER_ClickSound();
        play=0;
        lv_bar_set_value(bar_playing_time, 0, LV_ANIM_OFF);
        lv_label_set_text(txt_playing_time, "0%");
        MP3_Close();

    }
}
static void close_win_mp3_cb(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *btn = lv_event_get_current_target(e);
    lv_obj_t *win = lv_obj_get_parent(lv_obj_get_parent(btn));

    if(code == LV_EVENT_RELEASED)
    {
        if(buzzer_audio_enable)BUZZER_ClickSound();
        MP3_Close();
        MP3_UnmountSD();
        lv_timer_del(mp3_refresh_task);
        lv_obj_del(win);
        lv_create_win_main();
    }
}

static void populate_playlist(void)
{
    // scan and search for MP3 files - copy files names to playlist items

    lv_obj_t * new_song;
    if(!num_of_songs)
    {
        lv_label_set_text(txt_mp3, "Searching for files...");
        spinner = lv_spinner_create(lv_obj_get_parent(list_playlist), 1000, 60);
        lv_obj_set_size(spinner, 70, 70);
        lv_obj_align(spinner, LV_ALIGN_CENTER, -310+288, -170);
        fr = f_findfirst(&dj, &fno, "music", "*.mp3");
    }

    else
        fr = f_findnext(&dj, &fno);

    if(fr == FR_OK && fno.fname[0] && num_of_songs<max_num_of_songs)
    {
        unsigned char song_len=strlen(fno.fname);
        if(song_len<max_song_name_len)
        {
            new_song = lv_list_add_btn(list_playlist, NULL, fno.fname);
            lv_group_remove_obj(new_song);
            lv_obj_t *song_label=lv_obj_get_child(new_song, 0);

            static lv_style_t style_item_pr;
            lv_style_init(&style_item_pr);
            lv_style_set_bg_color(&style_item_pr, prim_color);
            lv_style_set_bg_opa(&style_item_pr, LV_OPA_70);
            lv_style_set_pad_ver(&style_item_pr, 3);
            static lv_style_t style_item_rel;
            lv_style_init(&style_item_rel);
            lv_style_set_bg_color(&style_item_rel, lv_color_white());
            lv_style_set_bg_opa(&style_item_rel, LV_OPA_70);
            lv_style_set_pad_ver(&style_item_rel, 3);

            lv_obj_add_style(new_song, &style_item_rel, LV_STATE_DEFAULT);
            lv_obj_add_style(new_song, &style_item_pr, LV_STATE_CHECKED);
            lv_obj_add_style(new_song, &style_item_pr, LV_STATE_PRESSED);

            lv_label_set_long_mode(song_label, LV_LABEL_LONG_CLIP); //disable rolling
            lv_obj_set_style_anim_speed(song_label, 20, LV_PART_MAIN);
            lv_obj_add_event_cb(new_song, playlist_event_handler, LV_EVENT_ALL, NULL);

            if(!num_of_songs)
            {
                sprintf(song_path,"%s/%s",song_folder,(char*)lv_list_get_btn_text(list_playlist, new_song));
                selected_song=new_song;
                lv_obj_add_state(new_song, LV_STATE_CHECKED);
                lv_label_set_long_mode(song_label, LV_LABEL_LONG_SCROLL_CIRCULAR); //enable rolling

            }
            num_of_songs++;

        }
    }
    else
    {
        char data_string[30]={};
        sprintf(data_string,"Done! Found %d files.",(uint16_t)num_of_songs);
        lv_label_set_text(txt_mp3, data_string);
        lv_obj_del(spinner);
        playlist_populated=1;
        f_closedir(&dj);
    }
}
static void lv_create_playlist(lv_obj_t * par)
{
    /*Create a list*/
    list_playlist = lv_list_create(par);
    lv_obj_set_size(list_playlist, 340, 310);
    lv_obj_set_pos(list_playlist, 420, 80);
    lv_gridnav_add(list_playlist, LV_GRIDNAV_CTRL_ROLLOVER);
    lv_group_add_obj(lv_group_get_default(), list_playlist);

    static lv_style_t style_list;
    lv_style_init(&style_list);
    lv_style_set_text_font(&style_list, &lv_font_montserrat_18);
    lv_style_set_pad_all(&style_list, 0);
    lv_style_set_bg_opa(&style_list, LV_OPA_30);
    lv_obj_add_style(list_playlist, &style_list, LV_STATE_DEFAULT);

    lv_obj_t * txt_playlist = lv_label_create(par);
    lv_label_set_text(txt_playlist, "Playlist:");
    lv_obj_align_to(txt_playlist, list_playlist, LV_ALIGN_OUT_TOP_LEFT, 10, -5);
}

void lv_create_win_mp3(void)
{
    lv_disp_t * disp = lv_disp_get_default();
    lv_theme_t * th = lv_disp_get_theme(disp);
    prim_color=th->color_primary;
    /*Create a window*/
    lv_obj_t * win = lv_win_create(lv_scr_act(), 50);
    lv_win_add_title(win, "MP3 player");
    lv_obj_t * cont = lv_win_get_content(win);

    /*Add control button to the header*/
    lv_obj_t * close_btn = lv_win_add_btn(win, LV_SYMBOL_CLOSE, 45);
    lv_obj_add_event_cb(close_btn, close_win_mp3_cb, LV_EVENT_ALL, NULL);
    lv_obj_set_style_bg_color(close_btn, lv_palette_main(LV_PALETTE_RED), LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(close_btn, lv_palette_darken(LV_PALETTE_RED, 4), LV_STATE_PRESSED);

    txt_mp3 = lv_label_create(cont);
    lv_obj_align(txt_mp3, LV_ALIGN_TOP_LEFT, 40, 10);
    lv_label_set_text(txt_mp3, "Press button to play");

    lv_obj_t * btn_prev = lv_btn_create(cont);
    lv_obj_align(btn_prev, LV_ALIGN_CENTER, -310, -100);
    lv_obj_set_size(btn_prev, 60, 50);
    lv_obj_add_event_cb(btn_prev, btn_prev_event_cb, LV_EVENT_ALL, NULL);
    lv_obj_t *img = lv_img_create(btn_prev);
    lv_img_set_src(img, LV_SYMBOL_PREV);

    lv_obj_t * btn_play = lv_btn_create(cont);
    lv_obj_align(btn_play, LV_ALIGN_CENTER, -310+72, -100);
    lv_obj_set_size(btn_play, 60, 50);
    lv_obj_add_event_cb(btn_play, btn_play_event_cb, LV_EVENT_ALL, NULL);
    img = lv_img_create(btn_play);
    lv_img_set_src(img, LV_SYMBOL_PLAY);

    lv_obj_t * btn_pause = lv_btn_create(cont);
    lv_obj_align(btn_pause, LV_ALIGN_CENTER, -310+144, -100);
    lv_obj_set_size(btn_pause, 60, 50);
    lv_obj_add_event_cb(btn_pause, btn_pause_event_cb, LV_EVENT_ALL, NULL);
    img = lv_img_create(btn_pause);
    lv_img_set_src(img, LV_SYMBOL_PAUSE);

    lv_obj_t * btn_stop = lv_btn_create(cont);
    lv_obj_align(btn_stop, LV_ALIGN_CENTER, -310+216, -100);
    lv_obj_set_size(btn_stop, 60, 50);
    lv_obj_add_event_cb(btn_stop, btn_stop_event_cb, LV_EVENT_ALL, NULL);
    img = lv_img_create(btn_stop);
    lv_img_set_src(img, LV_SYMBOL_STOP);

    lv_obj_t * btn_next = lv_btn_create(cont);
    lv_obj_align(btn_next, LV_ALIGN_CENTER, -310+288, -100);
    lv_obj_set_size(btn_next, 60, 50);
    lv_obj_add_event_cb(btn_next, btn_next_event_cb, LV_EVENT_ALL, NULL);
    img = lv_img_create(btn_next);
    lv_img_set_src(img, LV_SYMBOL_NEXT);

    lv_obj_t * slider_volume = lv_slider_create(cont);
    lv_obj_set_pos(slider_volume, 40, 195);
    lv_obj_set_width(slider_volume, 340);
    lv_slider_set_value(slider_volume,50,LV_ANIM_OFF);
    lv_obj_add_event_cb(slider_volume, slider_volume_event_cb, LV_EVENT_ALL, NULL);
    txt_volume = lv_label_create(cont);
    lv_label_set_text(txt_volume, "Volume 50%");
    lv_obj_align_to(txt_volume, slider_volume, LV_ALIGN_OUT_BOTTOM_MID, 0, 5);

    txt_playing_time = lv_label_create(cont);
    lv_label_set_text(txt_playing_time, "0%");
    bar_playing_time = lv_bar_create(cont);
    lv_obj_set_size(bar_playing_time, 340, 30);
    lv_obj_set_pos(bar_playing_time,40,305);

    lv_obj_align_to(txt_playing_time, bar_playing_time, LV_ALIGN_OUT_BOTTOM_MID, 0, 5);

    lv_obj_t *img_music = lv_img_create(cont);
    lv_obj_set_pos(img_music, 495, 140);
    lv_img_set_src(img_music, &music);
    lv_obj_set_style_img_recolor_opa(img_music, LV_OPA_COVER, 0);
    lv_obj_set_style_img_recolor(img_music, prim_color, 0);

    lv_create_playlist(cont);

    mp3_refresh_task=lv_timer_create((lv_timer_cb_t) lv_update_win_mp3, 10, NULL);
    num_of_songs=0;
    playlist_populated=0;
    MP3_MountSD();
    MP3_SetVolume(mp3_vol);
    play=0;

}

void lv_update_win_mp3(void)
{
    char data_string[20]={};

    if(!playlist_populated)
        populate_playlist();

    if(play)
    {
        MP3_Play(song_path);
        float mp3_prog=(((float)MP3_GetPlayingPosition()/playing_time)*100);
        sprintf(data_string,"%d%%",(uint16_t)mp3_prog);
        lv_bar_set_value(bar_playing_time, (uint16_t)mp3_prog, LV_ANIM_OFF);
        lv_label_set_text(txt_playing_time, data_string);
        if(MP3_GetState()==FINISHED)
        {
            find_next();
        }
    }
}

