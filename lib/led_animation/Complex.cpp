#include <Complex.h>
#include <LedColor.h>
#include <Rainbow.h>
#include <array.h>

const LedColor rgbOffCycle[] = {
    LED_RED,
    LED_GREEN,
    LED_BLUE,
    LED_OFF,
};

const Frame complexAnimation[] = {
    {{LED_OFF, LED_RED, LED_OFF, LED_OFF, LED_OFF, LED_OFF, LED_OFF, LED_OFF, LED_OFF, LED_RED},
     DEFAULT_FRAME_DURATION_MS},
    {{LED_OFF, LED_OFF, LED_GREEN, LED_OFF, LED_OFF, LED_OFF, LED_OFF, LED_OFF, LED_GREEN, LED_OFF},
     DEFAULT_FRAME_DURATION_MS},
    {{LED_OFF, LED_OFF, LED_OFF, LED_BLUE, LED_OFF, LED_OFF, LED_OFF, LED_BLUE, LED_OFF, LED_OFF},
     DEFAULT_FRAME_DURATION_MS},
    {{LED_OFF, LED_OFF, LED_OFF, LED_OFF, LED_RED, LED_OFF, LED_RED, LED_OFF, LED_OFF, LED_OFF},
     DEFAULT_FRAME_DURATION_MS},
    {{LED_OFF, LED_OFF, LED_OFF, LED_OFF, LED_OFF, LED_GREEN, LED_OFF, LED_OFF, LED_OFF, LED_OFF},
     DEFAULT_FRAME_DURATION_MS},
    {{LED_BLUE, LED_BLUE, LED_BLUE, LED_BLUE, LED_BLUE, LED_BLUE, LED_BLUE, LED_BLUE, LED_BLUE, LED_BLUE},
     DEFAULT_FRAME_DURATION_MS},
    {{LED_OFF, LED_OFF, LED_OFF, LED_OFF, LED_OFF, LED_RED, LED_OFF, LED_OFF, LED_OFF, LED_OFF},
     DEFAULT_FRAME_DURATION_MS},
    {{LED_OFF, LED_OFF, LED_OFF, LED_OFF, LED_GREEN, LED_OFF, LED_GREEN, LED_OFF, LED_OFF, LED_OFF},
     DEFAULT_FRAME_DURATION_MS},
    {{LED_OFF, LED_OFF, LED_OFF, LED_BLUE, LED_OFF, LED_OFF, LED_OFF, LED_BLUE, LED_OFF, LED_OFF},
     DEFAULT_FRAME_DURATION_MS},
    {{LED_OFF, LED_OFF, LED_RED, LED_OFF, LED_OFF, LED_OFF, LED_OFF, LED_OFF, LED_RED, LED_OFF},
     DEFAULT_FRAME_DURATION_MS},
    {{LED_OFF, LED_GREEN, LED_OFF, LED_OFF, LED_OFF, LED_OFF, LED_OFF, LED_OFF, LED_OFF, LED_GREEN},
     DEFAULT_FRAME_DURATION_MS},
    {{LED_OFF, LED_OFF, LED_OFF, LED_OFF, LED_OFF, LED_OFF, LED_OFF, LED_OFF, LED_OFF, LED_OFF},
     DEFAULT_FRAME_DURATION_MS},
};

void renderComplexAnimation(Frame *frame, uint32_t animationFrame)
{
    unsigned int frameIndex = animationFrame % ARRAY_LENGTH(complexAnimation);

    *frame = complexAnimation[frameIndex];
}

void renderComplexAnimationWithLed0RgbOff(Frame *frame, uint32_t animationFrame)
{
    renderComplexAnimation(frame, animationFrame);

    frame->pixels[0] = rgbOffCycle[(animationFrame / 5) % ARRAY_LENGTH(rgbOffCycle)];
}

void renderComplexAnimationWithLed0Rainbow(Frame *frame, uint32_t animationFrame)
{
    renderComplexAnimation(frame, animationFrame);

    frame->pixels[0] = ledRainbow[(animationFrame / 5) % ARRAY_LENGTH(ledRainbow)];
}
