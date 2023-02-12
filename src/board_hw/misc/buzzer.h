/*
 * buzzer.h
 *
 *  Created on: Jan 16, 2023
 *      Author: Jovan
 */

#ifndef BOARD_HW_MISC_BUZZER_H_
#define BOARD_HW_MISC_BUZZER_H_

#include <stdint.h>
#include <stdbool.h>

#define TONE_C  523 //C5
#define TONE_Cs 554
#define TONE_D  587
#define TONE_DS 622
#define TONE_E  659
#define TONE_F  698
#define TONE_Fs 740
#define TONE_G  784
#define TONE_Gs 831
#define TONE_A  880
#define TONE_As 932
#define TONE_B  988
#define TONE_C_ 1046

void BUZZER_Init(void);
void BUZZER_Start(void);
void BUZZER_Stop(void);
void BUZZER_SetVolume(uint8_t vol);
void BUZZER_SetFreq(uint32_t freq);
void BUZZER_ClickSound(void);

#endif /* BOARD_HW_MISC_BUZZER_H_ */
