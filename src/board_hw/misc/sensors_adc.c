/*
 * Author: J. Bajic, 2022.
 */

#include "board_hw/misc/sensors_adc.h"
#include "board_hw/tivaware_c_lib.h"

#define ADC_VREF            2.048f
#define ADC_RES             4096.0f
#define TEMP_SENSITIVITY    0.01f
#define TEMP_OFFSET         0.5f

uint32_t adc_data[4];

void ADCSensors_Init(void)
{
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOK);
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOP);

    MAP_GPIOPinTypeADC(GPIO_PORTP_BASE, GPIO_PIN_7);            // Configure the GPIO Pin Mux for PP7 for AIN22
    MAP_GPIOPinTypeADC(GPIO_PORTK_BASE, GPIO_PIN_2|GPIO_PIN_3);// Configure the GPIO Pin Mux for PK2 for AIN18 and PK3 for AIN19

    MAP_ADCSequenceConfigure(ADC0_BASE, 2, ADC_TRIGGER_PROCESSOR, 0);
    MAP_ADCSequenceStepConfigure(ADC0_BASE, 2, 0, ADC_CTL_CH22);                            //pin diode
    MAP_ADCSequenceStepConfigure(ADC0_BASE, 2, 1, ADC_CTL_CH18);                            //external temp sensor
    MAP_ADCSequenceStepConfigure(ADC0_BASE, 2, 2, ADC_CTL_CH19);                            //battery voltage
    MAP_ADCSequenceStepConfigure(ADC0_BASE, 2, 3, ADC_CTL_TS | ADC_CTL_IE | ADC_CTL_END);   //internal temp sensor
    MAP_ADCReferenceSet(ADC0_BASE, ADC_REF_EXT_3V);
    MAP_ADCSequenceEnable(ADC0_BASE, 2);
    MAP_ADCIntClear(ADC0_BASE, 2);
}

void ADCSensors_Read(void)
{
    MAP_ADCProcessorTrigger(ADC0_BASE, 2);
    while(!MAP_ADCIntStatus(ADC0_BASE, 2, false));
    MAP_ADCIntClear(ADC0_BASE, 2);
    MAP_ADCSequenceDataGet(ADC0_BASE, 2, adc_data);
}

uint32_t ADCSensors_getPINDiodeRaw(void)
{
    return adc_data[0];
}
uint32_t ADCSensors_getTempExternalRaw(void)
{
    return adc_data[1];
}

uint32_t ADCSensors_getBatteryRaw(void)
{
    return adc_data[2];
}

uint32_t ADCSensors_getTempInternalRaw(void)
{
    return adc_data[3];
}

float ADCSensors_getPINDiodeV(void)
{
    return ((float)ADCSensors_getPINDiodeRaw()*ADC_VREF/ADC_RES);
}

float ADCSensors_getTempExternalC(void)
{
    return ((float)ADCSensors_getTempExternalRaw()*ADC_VREF/ADC_RES-TEMP_OFFSET)/TEMP_SENSITIVITY;
}

float ADCSensors_getBatteryV(void)
{
    return ((float)ADCSensors_getBatteryRaw()*ADC_VREF*3/ADC_RES);;
}

float ADCSensors_getTempInternalC(void)
{
    return (147.5f-((float)ADCSensors_getTempInternalRaw()*ADC_VREF/ADC_RES)*75.0f);
}


