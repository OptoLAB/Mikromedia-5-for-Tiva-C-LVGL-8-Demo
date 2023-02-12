#ifndef NEC_TIMERIC_H
#define NEC_TIMERIC_H

#include <stdint.h>

// IR REMOTE LAYOUT
//      -----------------------------
//      |                           |
//      |   1       2       3       |
//      |                           |
//      |   4       5       6       |
//      |                           |
//      |   7       8       9       |
//      |                           |
//      |   *       0       #       |
//      |                           |
//      |           up              |
//      |                           |
//      |   left    ok      right   |
//      |                           |
//      |           down            |
//      |                           |
//      -----------------------------

#define IR_BTN_1        0xBA
#define IR_BTN_2        0xB9
#define IR_BTN_3        0xB8
#define IR_BTN_4        0xBB
#define IR_BTN_5        0xBF
#define IR_BTN_6        0xBC
#define IR_BTN_7        0xF8
#define IR_BTN_8        0xEA
#define IR_BTN_9        0XF6
#define IR_BTN_0        0XE6
#define IR_BTN_STAR     0xE9
#define IR_BTN_HASH     0xF2
#define IR_BTN_UP       0xE7
#define IR_BTN_DOWN     0xAD
#define IR_BTN_LEFT     0xF7
#define IR_BTN_RIGHT    0XA5
#define IR_BTN_OK       0XE3

uint32_t NEC_GetTimer(void);
void NEC_ResetTimer(void);
void NEC_TickInc(uint8_t inc);
uint8_t NEC_Capture(uint32_t time);
void NEC_Decode(void);
uint8_t NEC_GetCommand(void);
uint8_t NEC_GetAddress(void);
uint8_t NEC_GetStatus(void);
void NEC_ClearStatus(void);

#endif /* NEC_TIMERIC_H */
