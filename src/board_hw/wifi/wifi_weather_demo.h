/*
 * wf.h
 *
 *  Created on: Dec 5, 2020
 *      Author: Jovan
 */

#ifndef WIFI_WF_H
#define WIFI_WF_H

#include "simplelink//include//simplelink.h"

_i32 WIFI_Exec(_i8 *ssid_name, _i8* passkey);

_i32 WIFI_establishConnectionWithAP(_i8 *ssid_name, _i8* passkey);
_i32 WIFI_disconnectFromAP(void);
_i32 WIFI_configureToDefaultState(void);
_i32 WIFI_initializeAppVariables(void);

_i32 WIFI_createConnection();
_i32 WIFI_getHostIP();
_i32 WIFI_getData(void);
_i32 WIFI_getWeather(void);
void WIFI_extractWeatherData(const char *city, const char *temperature, const char *weather, const char *icon);

void CLI_displayBanner(void);
_i32 CLI_displayData(void);

#endif /* WIFI_WF_H_ */
