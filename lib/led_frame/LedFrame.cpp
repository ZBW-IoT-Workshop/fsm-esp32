#include "LedFrame.h"
#include <Arduino.h>
#include <stddef.h>

static void printFrameInfo(const Frame *const frame);

void clearFrame(Frame *const frame, const uint16_t duration_ms)
{
    fillFrame(frame, LED_OFF, duration_ms);
}

void fillFrame(Frame *const frame, const LedColor color, const uint16_t duration_ms)
{
    for (size_t i = 0; i < LED_COUNT; ++i)
    {
        frame->pixels[i] = color;
    }

    frame->duration_ms = duration_ms;
}

void showFrame(const Frame *frame, LED *const leds)
{
    uint8_t red[LED_COUNT];
    uint8_t green[LED_COUNT];
    uint8_t blue[LED_COUNT];

    for (unsigned int i = 0; i < LED_COUNT; i++)
    {
        red[i] = (unsigned int)frame->pixels[i].r;
        green[i] = (unsigned int)frame->pixels[i].g;
        blue[i] = (unsigned int)frame->pixels[i].b;
    }

    leds->setLEDColor(red, green, blue, LED_COUNT);
    printFrameInfo(frame);
}

static void printFrameInfo(const Frame *const frame)
{
    Serial.print("[");

    for (size_t i = 0; i < LED_COUNT; i++)
    {
        const char *name = colorToString(frame->pixels[i]);

        Serial.print(name);

        if (i < LED_COUNT - 1)
        {
            Serial.print(", ");
        }
    }

    Serial.print("] ");
    Serial.print(frame->duration_ms);
    Serial.println(" ms");
}
