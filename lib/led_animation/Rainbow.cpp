#include <Rainbow.h>

void renderStaticRainbow(Frame *frame, uint32_t animationFrame)
{
    for (unsigned int i = 0; i < LED_COUNT; i++)
    {
        frame->pixels[i] = ledRainbow[i];
    }

    frame->duration_ms = 500;
}

void renderRunningRainbow(Frame *frame, uint32_t animationFrame)
{
    for (unsigned int i = 0; i < LED_COUNT; i++)
    {
        frame->pixels[i] = ledRainbow[(i + animationFrame) % LED_COUNT];
    }

    frame->duration_ms = 150;
}
