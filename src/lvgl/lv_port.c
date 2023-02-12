/*
 * Author: J. Bajic, 2022.
 */
/*********************
 *      INCLUDES
 *********************/
#include "lv_port.h"
#include <stdbool.h>

#include "board_hw/display/display.h"
#include "board_hw/touch/TSC2006.h"
#include "board_hw/misc/rgb_led.h"
#include "board_hw/misc/nec_decoder.h"
#include "board_hw/misc/ir_tsop.h"
#include "board_hw/misc/buzzer.h"
#include "board_hw/sys/udma_sw.h"
#include "board_hw/tivaware_c_lib.h"


/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/
static void my_disp_flush(lv_disp_drv_t * disp_drv, const lv_area_t * area, lv_color_t * color_p);
static void my_touchpad_read(lv_indev_drv_t * indev_drv, lv_indev_data_t * data);
#if USE_IR_REMOTE_AS_CURSOR
    static void my_remote_cursor_read(lv_indev_drv_t * indev_drv, lv_indev_data_t * data);
#else
    static void my_remote_keypad_read(lv_indev_drv_t * indev_drv, lv_indev_data_t * data);
#endif
/**********************
 *  STATIC VARIABLES
 **********************/
lv_disp_drv_t act_disp_drv;
uint32_t transfer_num=0;
uint32_t transfer_size=0;
uint16_t *destBuff;
uint16_t *srcBuff;
uint32_t sys_tick_cnt=0;

lv_indev_t * indev_touchpad;
lv_indev_t * indev_remote;

#if USE_IR_REMOTE_AS_CURSOR
    #define LV_CURSOR_INC       20
    lv_obj_t *remote_cursor;
    uint8_t cursor_is_visible=0;
    lv_coord_t cursor_x_position=100;  //default x cursor position
    lv_coord_t cursor_y_position=100;  //default y cursor position
    extern const lv_img_dsc_t cursor;
#endif

extern uint8_t buzzer_audio_enable;


/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/
void SysTickIntHandler(void)
{
    sys_tick_cnt++;
    lv_tick_inc(1);
    if(sys_tick_cnt>=1000)
    {
        sys_tick_cnt=0;
    }
}

void uDMAIntHandler(void)
{
    uint32_t ui32Mode;

    // Check for the primary control structure to indicate complete.
    ui32Mode = MAP_uDMAChannelModeGet(UDMA_CHANNEL_SW);
    if(ui32Mode == UDMA_MODE_STOP)
    {
        if(transfer_num>0)
        {
            transfer_num--;
            destBuff+=MY_DISP_HOR_RES;
            srcBuff+=transfer_size;
            uDMA_Transfer(srcBuff, destBuff, transfer_size);
        }
        else
        {
            lv_disp_flush_ready(&act_disp_drv);
        }
    }
}


void LCDIntHandler(void)
{
#if DISPLAY_EN_INTERRUPT
    uint32_t ui32Status;

    // Get the current interrupt status and clear any active interrupts.
    ui32Status = MAP_LCDIntStatus(LCD0_BASE, true);
    MAP_LCDIntClear(LCD0_BASE, ui32Status);

    if(ui32Status & LCD_INT_EOF0)
    {
    }
    if(ui32Status & LCD_INT_EOF1)//in pingpong mode
    {
    }
    if(ui32Status & LCD_INT_UNDERFLOW)
    {
    }
#endif
}


void lv_port_init(void)
{
    static lv_disp_draw_buf_t  lv_disp_buf;      //Define buffer

#if(BUFFER_RAM==RAM_INT)
    #if(BUFFERING_MODE==SINGLE_BUF)
        static lv_color_t lv_buffer_1[INT_BUF_SIZE]; //First buffer
        lv_disp_draw_buf_init(&lv_disp_buf, lv_buffer_1, NULL, INT_BUF_SIZE); //Initialize the display buffer
    #else
        static lv_color_t lv_buffer_1[INT_BUF_SIZE]; //First buffer
        static lv_color_t lv_buffer_2[INT_BUF_SIZE]; //Second buffer
        lv_disp_draw_buf_init(&lv_disp_buf, lv_buffer_1, lv_buffer_2, INT_BUF_SIZE); //Initialize the display buffer
    #endif
#else
    #if(BUFFERING_MODE==SINGLE_BUF)
        lv_disp_draw_buf_init(&lv_disp_buf, (void*)EXT_BUF1_ADR, NULL, EXT_BUF_SIZE); //Initialize the display buffer
    #else
        lv_disp_draw_buf_init(&lv_disp_buf, (void*)EXT_BUF1_ADR, (void*)EXT_BUF2_ADR, EXT_BUF_SIZE); //Initialize the display buffer
    #endif
#endif
	
    // Initialized in main

   // static lv_disp_drv_t disp_drv;                    //Descriptor of a display driver
    lv_disp_drv_init(&act_disp_drv);                    //Basic initialization
    act_disp_drv.hor_res = MY_DISP_HOR_RES;             //Set horizontal resolution of the display
    act_disp_drv.ver_res = MY_DISP_VER_RES;             //Set vertical resolution of the display
    act_disp_drv.flush_cb = my_disp_flush;              //Used to copy the buffer's content to the display
    act_disp_drv.draw_buf = &lv_disp_buf;               //Set a display buffer
    act_disp_drv.full_refresh=false;                    //copy entire buffer
    act_disp_drv.direct_mode=false;                     //direct copy
#if MY_DISP_ROTATION
    act_disp_drv.sw_rotate=1;
    act_disp_drv.rotated=MY_DISP_ROTATION;
#endif
    lv_disp_drv_register(&act_disp_drv);                //Finally register the driver

    static lv_indev_drv_t indev_drv_tp;             //Descriptor of input device
    lv_indev_drv_init(&indev_drv_tp);               //Basic initialization
    indev_drv_tp.type = LV_INDEV_TYPE_POINTER;      //Touchpad
    indev_drv_tp.read_cb = my_touchpad_read;        //Callback fuction used for reading touchpad
    indev_touchpad=lv_indev_drv_register(&indev_drv_tp); //Finally register the driver

#if USE_IR_REMOTE_AS_CURSOR
    static lv_indev_drv_t indev_drv_ir;
    lv_indev_drv_init(&indev_drv_ir);
    indev_drv_ir.type = LV_INDEV_TYPE_POINTER;
    indev_drv_ir.read_cb = my_remote_cursor_read;
    indev_remote = lv_indev_drv_register(&indev_drv_ir);        //Register a ir remote input device

    remote_cursor = lv_img_create(lv_disp_get_scr_act(NULL));   //Set cursor. For simplicity set a + symbol now.
    lv_img_set_src(remote_cursor, &cursor);
    lv_obj_set_style_img_recolor_opa(remote_cursor, LV_OPA_COVER, 0);
    lv_obj_set_style_img_recolor(remote_cursor, lv_palette_main(LV_PALETTE_RED), 0);
    lv_indev_set_cursor(indev_remote, remote_cursor);
    lv_obj_add_flag(remote_cursor, LV_OBJ_FLAG_HIDDEN);
    cursor_is_visible=0;
#else
    lv_group_t *g = lv_group_create();
    lv_group_set_default(g);
    static lv_indev_drv_t indev_drv_ir;
    lv_indev_drv_init(&indev_drv_ir);
    indev_drv_ir.type = LV_INDEV_TYPE_KEYPAD;
    indev_drv_ir.read_cb = my_remote_keypad_read;
    indev_remote = lv_indev_drv_register(&indev_drv_ir);        //Register a ir remote input device
    lv_indev_set_group(indev_remote, g);
#endif
}
/**********************
 *   STATIC FUNCTIONS
 **********************/
static void my_disp_flush(lv_disp_drv_t * disp_drv, const lv_area_t * area, lv_color_t * color_p)
{
    uint16_t *sdram_addr=(uint16_t*)DISPLAY_getFrameBufferAddress();

    transfer_size=lv_area_get_width(area);
    transfer_num=lv_area_get_height(area);
    destBuff=&sdram_addr[area->y1 * MY_DISP_HOR_RES + area->x1];
    srcBuff=(uint16_t*)color_p;

#if(FLUSH_MODE==FLUSH_SIMPLE)
    uint32_t i,j;
    for(i = 0; i <transfer_num; i++)
    {
        for(j = 0; j <transfer_size; j++)
        {
            #if USE_EPI
                EPIWorkaroundHWordWrite(destBuff+j, *srcBuff);
            #else
                destBuff[j]= *srcBuff;
            #endif
            //destBuff++;
            srcBuff++;
        }
        //srcBuff+=size_of_transfer;
        destBuff+=MY_DISP_HOR_RES;
    }
    lv_disp_flush_ready(&act_disp_drv);
#elif(FLUSH_MODE==FLUSH_MEMCPY)
    uint32_t i;
    for(i = 0; i <transfer_num; i++)
    {
        lv_memcpy(destBuff, srcBuff, transfer_size * sizeof(lv_color_t));
        srcBuff += transfer_size;
        destBuff+=MY_DISP_HOR_RES;
    }
    lv_disp_flush_ready(&act_disp_drv);
#elif(FLUSH_MODE==FLUSH_DMA)
    if(transfer_num)
    {
        uDMA_Transfer(srcBuff, destBuff, transfer_size);
        transfer_num-=1;
    }
#else
    if(lv_disp_flush_is_last(&act_disp_drv)==true)
    {
    }

    lv_disp_flush_ready(&act_disp_drv);
#endif

}

static void my_touchpad_read(lv_indev_drv_t * indev_drv, lv_indev_data_t * data)
{
    static uint8_t touchpad_db_fl=0; //debouncing flag
    static uint16_t last_x = 0, last_y = 0;

    if(TSC2006_isPressed())
    {
        if(touchpad_db_fl)
        {
            TSC2006_readXYCalibrated(&last_x, &last_y);
            data->state = LV_INDEV_STATE_PR;
#if USE_IR_REMOTE_AS_CURSOR
            if(cursor_is_visible)
            {
                cursor_is_visible=0;
                lv_obj_add_flag(remote_cursor, LV_OBJ_FLAG_HIDDEN);
            }
#endif
        }
        else
        {
            touchpad_db_fl=1;
        }
    }
    else
    {
        touchpad_db_fl=0;
        data->state = LV_INDEV_STATE_REL;
    }

    //Set the last pressed coordinates
    data->point.x = (lv_coord_t)last_x;
    data->point.y = (lv_coord_t)last_y;
}
#if USE_IR_REMOTE_AS_CURSOR
static void my_remote_cursor_read(lv_indev_drv_t * indev_drv, lv_indev_data_t * data)
{
    /*Get the current x and y coordinates*/
    if(NEC_GetStatus())
    {
        if(!cursor_is_visible)
        {
            cursor_is_visible=1;
            lv_obj_clear_flag(remote_cursor, LV_OBJ_FLAG_HIDDEN);
        }
        switch(NEC_GetCommand())
        {
            case IR_BTN_UP:
                if(buzzer_audio_enable)BUZZER_ClickSound();
                if(cursor_y_position>0) cursor_y_position-=LV_CURSOR_INC;
                else cursor_y_position=MY_DISP_VER_RES-LV_CURSOR_INC;
                break;
            case IR_BTN_DOWN:
                if(buzzer_audio_enable)BUZZER_ClickSound();
                if(cursor_y_position<(MY_DISP_VER_RES-LV_CURSOR_INC)) cursor_y_position+=LV_CURSOR_INC;
                else cursor_y_position=0;
                break;
            case IR_BTN_LEFT:
                if(buzzer_audio_enable)BUZZER_ClickSound();
                if(cursor_x_position>0) cursor_x_position-=LV_CURSOR_INC;
                else cursor_x_position=MY_DISP_HOR_RES-LV_CURSOR_INC;
                break;
            case IR_BTN_RIGHT:
                if(buzzer_audio_enable)BUZZER_ClickSound();
                if(cursor_x_position<(MY_DISP_HOR_RES-LV_CURSOR_INC)) cursor_x_position+=LV_CURSOR_INC;
                else cursor_x_position=0;
                break;
            case IR_BTN_OK:
                data->state = LV_INDEV_STATE_PR;
                break;
            default:
                data->state = LV_INDEV_STATE_REL;
                break;
        }
        NEC_ClearStatus();
    }
    data->point.x=cursor_x_position;
    data->point.y=cursor_y_position;
}
#else
static void my_remote_keypad_read(lv_indev_drv_t * indev_drv, lv_indev_data_t * data)
{
    static uint32_t last_key = 0;

    if(NEC_GetStatus())
    {
        data->state = LV_INDEV_STATE_PRESSED;
        switch(NEC_GetCommand())
        {
            case IR_BTN_HASH:
                if(buzzer_audio_enable)BUZZER_ClickSound();
                last_key = LV_KEY_NEXT;
                break;
            case IR_BTN_STAR:
                if(buzzer_audio_enable)BUZZER_ClickSound();
                last_key = LV_KEY_PREV;
                break;
            case IR_BTN_UP:
                if(buzzer_audio_enable)BUZZER_ClickSound();
                last_key = LV_KEY_UP;
                break;
            case IR_BTN_DOWN:
                if(buzzer_audio_enable)BUZZER_ClickSound();
                last_key = LV_KEY_DOWN;
                break;
            case IR_BTN_LEFT:
                if(buzzer_audio_enable)BUZZER_ClickSound();
                last_key = LV_KEY_LEFT;
                break;
            case IR_BTN_RIGHT:
                if(buzzer_audio_enable)BUZZER_ClickSound();
                last_key = LV_KEY_RIGHT;
                break;
            case IR_BTN_OK:
                last_key = LV_KEY_ENTER;
                break;
            default:
                //none
                break;
        }
        NEC_ClearStatus();
    }
    else
    {
        last_key=0;
        data->state = LV_INDEV_STATE_RELEASED;
    }
    data->key = last_key;
}
#endif
