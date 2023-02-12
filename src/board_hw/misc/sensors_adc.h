/*
 * Author: J. Bajic, 2022.
 */

#ifndef BOARD_HW_SENSORS_ADC_H_
#define BOARD_HW_SENSORS_ADC_H_

#include <stdint.h>
#include <stdbool.h>

void ADCSensors_Init(void);
void ADCSensors_Read(void);
uint32_t ADCSensors_getPINDiodeRaw(void);
uint32_t ADCSensors_getTempExternalRaw(void);
uint32_t ADCSensors_getBatteryRaw(void);
uint32_t ADCSensors_getTempInternalRaw(void);
float ADCSensors_getPINDiodeV(void);
float ADCSensors_getTempExternalC(void);
float ADCSensors_getBatteryV(void);
float ADCSensors_getTempInternalC(void);

#endif /* BOARD_HW_SENSORS_ADC_H_ */
