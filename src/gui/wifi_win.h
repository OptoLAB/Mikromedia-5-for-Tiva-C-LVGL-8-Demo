/*
 * Author: J. Bajic, 2022.
 */

#ifndef GUI_WIFI_WIN_H_
#define GUI_WIFI_WIN_H_

#define WIFI_DISCONNECTED   0
#define WIFI_CONFIG         1
#define WIFI_START          2
#define WIFI_CONNECT        3
#define WIFI_CONNECTED      4
#define WIFI_GET_DATA       5
#define WIFI_DISCONNECT     6

#include "lvgl/lvgl.h"

void lv_create_win_wifi(void);
void lv_update_win_wifi(void);


#endif /* GUI_WIFI_WIN_H_ */
