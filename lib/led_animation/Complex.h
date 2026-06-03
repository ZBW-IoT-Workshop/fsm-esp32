#ifndef LIB_LED_ANIMATION_COMPLEX_H
#define LIB_LED_ANIMATION_COMPLEX_H

#include <LedFrame.h>
#include <stdint.h>

void renderComplexAnimation(Frame *frame, uint32_t animationFrame);
void renderComplexAnimationWithLed0RgbOff(Frame *frame, uint32_t animationFrame);
void renderComplexAnimationWithLed0Rainbow(Frame *frame, uint32_t animationFrame);

#endif /* LIB_LED_ANIMATION_COMPLEX_H */
