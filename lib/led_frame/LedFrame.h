#ifndef LIB_LED_FRAME_LED_FRAME_H
#define LIB_LED_FRAME_LED_FRAME_H

#include "../../include/config/board.h"
#include "LedColor.h"
#include <QwiicLedStick.h>
#include <stdint.h>

typedef struct sFrame
{
    LedColor pixels[LED_COUNT];
    uint16_t duration_ms;
} Frame;

void clearFrame(Frame *const frame, uint16_t duration_ms);
void fillFrame(Frame *const frame, LedColor color, uint16_t duration_ms);
void showFrame(const Frame *frame, LED *const leds);

#endif /* LIB_LED_FRAME_LED_FRAME_H */
