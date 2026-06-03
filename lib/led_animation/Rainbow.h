#ifndef LIB_LED_ANIMATION_RAINBOW_H
#define LIB_LED_ANIMATION_RAINBOW_H

#include <LedFrame.h>
#include <stdint.h>

const LedColor ledRainbow[] = {
    LED_RED,        LED_ORANGE, LED_YELLOW,     LED_GREENYELLOW, LED_GREEN,
    LED_AQUAMARINE, LED_AQUA,   LED_DODGERBLUE, LED_BLUE,        LED_PURPLE,
};

void renderStaticRainbow(Frame *frame, uint32_t animationFrame);
void renderRunningRainbow(Frame *frame, uint32_t animationFrame);

#endif /* LIB_LED_ANIMATION_RAINBOW_H */
