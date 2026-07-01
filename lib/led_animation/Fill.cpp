#include <Fill.h>
#include <LedColor.h>
#include <LedFrame.h>
#include "../../include/config/board.h"

static const LedColor COLOR_FILLED   = LED_OFF;
static const LedColor COLOR_UNFILLED = LED_RED;
static const uint16_t FRAME_DURATION_MS = 100;

void renderFill(Frame *frame, uint32_t animationFrame)
{
    uint32_t filledCount = animationFrame % (LED_COUNT + 1);

    clearFrame(frame, FRAME_DURATION_MS);

    for (uint32_t i = 0; i < filledCount; i++)
    {
        frame->pixels[i] = COLOR_FILLED;
    }

    for (uint32_t i = filledCount; i < LED_COUNT; i++)
    {
        frame->pixels[i] = COLOR_UNFILLED;
    }
}

const Animation motorFillAnimation = {
    "Motor Fill",
    renderFill,
    (LED_COUNT + 1) * FRAME_DURATION_MS,
};
