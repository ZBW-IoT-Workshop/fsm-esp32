#include <Bgr.h>
#include <LedColor.h>
#include <array.h>

static const LedColor sequence[] = {
    LED_BLUE,
    LED_GREEN,
    LED_RED,
};

void renderBgr(Frame *frame, uint32_t animationFrame)
{
    LedColor color = sequence[animationFrame % ARRAY_LENGTH(sequence)];

    fillFrame(frame, color, 2000);
}
