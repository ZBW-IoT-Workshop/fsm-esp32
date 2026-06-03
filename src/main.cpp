#include <Animation.h>
#include <Arduino.h>
#include <Bgr.h>
#include <Complex.h>
#include <KnightRider.h>
#include <LedColor.h>
#include <LedFrame.h>
#include <QwiicLedStick.h>
#include <Rainbow.h>
#include <config/board.h>

static LED leds = LED();

static unsigned int currentAnimationIndex = 0;
static unsigned long currentAnimationStartMs = 0;
static unsigned long currentFrameStartMs = 0;
static unsigned long animationFrameCounter = 0;

static Frame currentFrame;

static const Animation animations[] = {
    {"B-G-R sequence", renderBgr, 6000},
    {"Knight Rider", renderKnightRider, 8000},
    {"Complex animation", renderComplexAnimation, 6000},
    {"Complex + LED0 R-G-B-Off", renderComplexAnimationWithLed0RgbOff, 8000},
    {"Complex + LED0 Rainbow", renderComplexAnimationWithLed0Rainbow, 8000},
    {"Static Rainbow", renderStaticRainbow, 5000},
    {"Running Rainbow", renderRunningRainbow, 10000},
};

static const unsigned int animationCount = sizeof(animations) / sizeof(animations[0]);

void setup(void)
{
    // put your setup code here, to run once:
    bool success = true;

    Serial.begin(115200);
    Wire.begin();

    Serial.print("Initializing LEDs...");
    success = success && leds.begin();
    leds.LEDOff();
    leds.setLEDBrightness(1);
    Serial.println(" done");

    if (!success)
    {
        Serial.println("Initialization failed at some point. Halting...");
        while (1)
        {
        }
    }
    else
    {
        Serial.println("Starting");
    }

    currentAnimationStartMs = millis();
    currentFrameStartMs = millis();

    animations[currentAnimationIndex].render(&currentFrame, animationFrameCounter);
    showFrame(&currentFrame, &leds);
}

void loop(void)
{
    // put your main code here, to run repeatedly:
    unsigned long now = millis();

    Animation currentAnimation = animations[currentAnimationIndex];

    if (now - currentAnimationStartMs >= currentAnimation.duration_ms)
    {
        currentAnimationIndex++;

        if (currentAnimationIndex >= animationCount)
        {
            currentAnimationIndex = 0;
        }

        currentAnimationStartMs = now;
        currentFrameStartMs = now;
        animationFrameCounter = 0;

        Serial.print("Switching to animation: ");
        Serial.println(animations[currentAnimationIndex].name);

        animations[currentAnimationIndex].render(&currentFrame, animationFrameCounter);
        showFrame(&currentFrame, &leds);
        return;
    }

    if (now - currentFrameStartMs >= currentFrame.duration_ms)
    {
        currentFrameStartMs = now;
        animationFrameCounter++;

        animations[currentAnimationIndex].render(&currentFrame, animationFrameCounter);
        showFrame(&currentFrame, &leds);
    }
}
