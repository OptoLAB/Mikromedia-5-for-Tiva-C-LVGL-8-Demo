/*
 * Author: J. Bajic, 2022.
 */
#include "board_hw/misc/buzzer.h"
#include "gui/obj/pswd_obj.h"
#include <string.h>

extern uint8_t buzzer_audio_enable;

const lv_obj_class_t lv_pswd_class = {
    .width_def = LV_SIZE_CONTENT,
    .height_def = LV_SIZE_CONTENT,
    .instance_size = sizeof(lv_pswd_t),
    .base_class = &lv_obj_class
};

static void kb_event_cb(lv_event_t *e)
{

    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * kb = lv_event_get_current_target(e);
    lv_obj_t *cont = lv_obj_get_parent(kb);
    lv_obj_t *obj = lv_obj_get_parent(cont);
    lv_pswd_t *pswd = (lv_pswd_t *)obj;

    if(code == LV_EVENT_CLICKED)
    {
        if(buzzer_audio_enable)BUZZER_ClickSound();
    }
    if(code == LV_EVENT_CANCEL)
    {

    }
    if(code == LV_EVENT_CANCEL)
    {
        if(buzzer_audio_enable)BUZZER_ClickSound();
        lv_event_send(obj, LV_EVENT_CANCEL, NULL);
        lv_obj_del(obj);
    }
    if(code == LV_EVENT_READY)
    {
        if(lv_keyboard_get_textarea(kb)==pswd->ta_name)
        {
            lv_keyboard_set_textarea(pswd->kb, pswd->ta_pass);
            lv_obj_clear_state(pswd->ta_name, LV_STATE_FOCUSED);
            lv_obj_add_state(pswd->ta_pass, LV_STATE_FOCUSED);
        }
        else
        {
            if(buzzer_audio_enable)BUZZER_ClickSound();
            strcpy(pswd->name,(char*)lv_textarea_get_text(pswd->ta_name));
            strcpy(pswd->pass,(char*)lv_textarea_get_text(pswd->ta_pass));

            lv_event_send(obj, LV_EVENT_READY, NULL);
            lv_obj_del(obj);
        }
    }

}
static void ta_event_cb(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *ta = lv_event_get_current_target(e);
    lv_obj_t *cont=lv_obj_get_parent(ta);
    lv_pswd_t* pswd = (lv_pswd_t *)lv_obj_get_parent(cont);

    if(code == LV_EVENT_CLICKED)
    {
        if(buzzer_audio_enable)BUZZER_ClickSound();
        if(pswd->kb != NULL)
        {
            lv_obj_clear_state(lv_keyboard_get_textarea(pswd->kb), LV_STATE_FOCUSED);
            lv_keyboard_set_textarea(pswd->kb, ta);
            lv_obj_add_state(ta, LV_STATE_FOCUSED);
        }
    }

}

lv_obj_t * lv_pswd_get_kb(lv_obj_t * obj)
{
    lv_pswd_t * pswd = (lv_pswd_t *)obj;
    return pswd->kb;
}

lv_obj_t *lv_pswd_create(lv_obj_t *parent)
{
    lv_obj_t * obj = lv_obj_class_create_obj(&lv_pswd_class, parent);
    lv_obj_class_init_obj(obj);

    lv_pswd_t * pswd = (lv_pswd_t *)obj;

    static lv_style_t style_cont_pswd;
    lv_style_init(&style_cont_pswd);
    lv_style_set_pad_all(&style_cont_pswd, 5);

    pswd->cont=lv_obj_create(obj);
    lv_obj_set_width(pswd->cont, 480);
    lv_obj_set_height(pswd->cont, 260);
    lv_obj_add_style(pswd->cont, &style_cont_pswd, LV_STATE_DEFAULT);

    pswd->name[0]=0;
    pswd->pass[0]=0;

    /* Create the ssid box */
    pswd->ta_name= lv_textarea_create(pswd->cont);
    lv_textarea_set_text(pswd->ta_name, "");
    lv_textarea_set_password_mode(pswd->ta_name, false);
    lv_textarea_set_one_line(pswd->ta_name, true);
    lv_obj_set_width(pswd->ta_name, 190);
    lv_obj_set_pos(pswd->ta_name, 5+10, 25);
    lv_obj_add_event_cb(pswd->ta_name, ta_event_cb, LV_EVENT_ALL, NULL);
    /* Create a label and position it above the text box */
    pswd->label_name = lv_label_create(pswd->cont);
    lv_label_set_text(pswd->label_name, "Name:");
    lv_obj_align_to(pswd->label_name, pswd->ta_name, LV_ALIGN_OUT_TOP_LEFT, 0, 0);

    /* Create the password box */
    pswd->ta_pass = lv_textarea_create(pswd->cont);
    lv_textarea_set_text(pswd->ta_pass, "");
    lv_textarea_set_password_mode(pswd->ta_pass, true);
    lv_textarea_set_one_line(pswd->ta_pass, true);
    lv_obj_set_width(pswd->ta_pass, 190);
    lv_obj_set_pos(pswd->ta_pass, 205+40, 25);
    lv_obj_add_event_cb(pswd->ta_pass, ta_event_cb, LV_EVENT_ALL, NULL);

    /* Create a label and position it above the text box */
    pswd->label_pass = lv_label_create(pswd->cont);
    lv_label_set_text(pswd->label_pass, "Password:");
    lv_obj_align_to(pswd->label_pass, pswd->ta_pass, LV_ALIGN_OUT_TOP_LEFT, 0, 0);

    /* Create a keyboard and make it fill the width of the above text areas */
    pswd->kb = lv_keyboard_create(pswd->cont);
    lv_obj_set_pos(pswd->kb, 0, 0);
    lv_obj_add_event_cb(pswd->kb, kb_event_cb, LV_EVENT_ALL, NULL);
    lv_obj_set_size(pswd->kb,  390+60, 160);
    lv_keyboard_set_textarea(pswd->kb, pswd->ta_name);
    lv_obj_add_state(pswd->ta_name, LV_STATE_FOCUSED);

    return obj;

}

void lv_pswd_get_name(lv_obj_t * obj, char *name)
{
    lv_pswd_t * pswd = (lv_pswd_t *)obj;

    if(pswd->name[0]!=0)
    {
        strcpy(name,pswd->name);
    }
}
void lv_pswd_get_passkey(lv_obj_t * obj, char *passkey)
{
    lv_pswd_t * pswd = (lv_pswd_t *)obj;

    if(pswd->pass[0]!=0)
    {
        strcpy(passkey,pswd->pass);
    }
}
