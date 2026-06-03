#ifndef LIB_LED_ANIMATION_ANIMATION_H
#define LIB_LED_ANIMATION_ANIMATION_H

#include <LedFrame.h>
#include <stdint.h>

typedef void (*RenderFunction)(Frame *frame, uint32_t animationFrame);

typedef struct Animation_s
{
    const char *name;
    RenderFunction render;
    uint32_t duration_ms;
} Animation;

#endif /* LIB_LED_ANIMATION_ANIMATION_H */
