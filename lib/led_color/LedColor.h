#ifndef LIB_LED_COLOR_LED_COLOR_H
#define LIB_LED_COLOR_LED_COLOR_H

#include <stdbool.h>
#include <stdint.h>

typedef struct LedColor_s
{
    uint8_t r;
    uint8_t g;
    uint8_t b;
} LedColor;

#define LED_OFF ((LedColor){0, 0, 0})
#define LED_RED ((LedColor){255, 0, 0})
#define LED_ORANGE ((LedColor){255, 165, 0})
#define LED_YELLOW ((LedColor){255, 255, 0})
#define LED_GREENYELLOW ((LedColor){173, 255, 47})
#define LED_GREEN ((LedColor){0, 128, 0})
#define LED_AQUAMARINE ((LedColor){127, 255, 212})
#define LED_AQUA ((LedColor){0, 255, 255})
#define LED_DODGERBLUE ((LedColor){30, 144, 255})
#define LED_BLUE ((LedColor){0, 0, 255})
#define LED_PURPLE ((LedColor){128, 0, 128})

bool colorsEqual(LedColor a, LedColor b);
const char *colorToString(LedColor color);

#endif /* LIB_LED_COLOR_LED_COLOR_H */
