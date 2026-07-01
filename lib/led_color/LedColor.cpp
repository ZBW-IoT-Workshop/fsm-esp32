#include "LedColor.h"

bool colorsEqual(LedColor a, LedColor b)
{
    return (a.r == b.r) && (a.g == b.g) && (a.b == b.b);
}

const char *colorToString(LedColor color)
{
    if (colorsEqual(color, LED_OFF))
        return "Off";
    if (colorsEqual(color, LED_RED))
        return "Red";
    if (colorsEqual(color, LED_ORANGE))
        return "Orange";
    if (colorsEqual(color, LED_YELLOW))
        return "Yellow";
    if (colorsEqual(color, LED_GREENYELLOW))
        return "GreenYellow";
    if (colorsEqual(color, LED_GREEN))
        return "Green";
    if (colorsEqual(color, LED_AQUAMARINE))
        return "Aquamarine";
    if (colorsEqual(color, LED_AQUA))
        return "Aqua";
    if (colorsEqual(color, LED_DODGERBLUE))
        return "DodgerBlue";
    if (colorsEqual(color, LED_BLUE))
        return "Blue";
    if (colorsEqual(color, LED_PURPLE))
        return "Purple";

    return "Custom";
}
