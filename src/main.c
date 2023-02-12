#include "board_hw/board_hw.h"
#include "lvgl/lvgl.h"
#include "lvgl/lv_port.h"
#include "gui/main_win.h"

void my_log_cb(lv_log_level_t level, const char * buf)
{
  SERIAL_Write((uint8_t*)buf, (uint32_t)strlen(buf));
}

int main(void)
{
    BOARD_HW_Init();
    lv_init();
    lv_port_init();

    lv_log_register_print_cb((lv_log_print_g_cb_t)my_log_cb);

    lv_create_win_main();

    while(1)
    {
        lv_timer_handler();
        delayMS(5);
    }

}
