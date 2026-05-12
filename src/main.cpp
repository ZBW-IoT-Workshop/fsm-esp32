#include <Arduino.h>
#include <QwiicLedStick.h>

#define LED_COUNT (10)
#define MAX_FRAME_COUNT (20)
#define ANIMATION_SWITCH_THRESHOLD (20)
#define DEFAULT_FRAME_DURATION_MS (250)

#define LED_OFF {0, 0, 0}
#define LED_RED {255, 0, 0}
#define LED_ORANGE {255, 165, 0}
#define LED_YELLOW {255, 255, 0}
#define LED_GREENYELLOW {173, 255, 47}
#define LED_GREEN {0, 128, 0}
#define LED_AQUAMARINE {127, 255, 212}
#define LED_AQUA {0, 255, 255}
#define LED_DODGERBLUE {30, 144, 255}
#define LED_BLUE {0, 0, 255}
#define LED_PURPLE {128, 0, 128}

typedef struct LedColor_s
{
    unsigned int r;
    unsigned int g;
    unsigned int b;
} LedColor;

typedef struct Frame_s
{
    LedColor pixels[LED_COUNT];
    unsigned int duration_ms;
} Frame;

typedef void (*RenderFunction)(Frame *frame, unsigned long animationFrame);

typedef struct Animation_s
{
    const char *name;
    RenderFunction render;
    unsigned long duration_ms;
} Animation;

static const LedColor ledRainbow[LED_COUNT] = {
    LED_RED,        LED_ORANGE, LED_YELLOW,     LED_GREENYELLOW, LED_GREEN,
    LED_AQUAMARINE, LED_AQUA,   LED_DODGERBLUE, LED_BLUE,        LED_PURPLE,
};

static const LedColor rgbOffCycle[4] = {
    LED_RED,
    LED_GREEN,
    LED_BLUE,
    LED_OFF,
};

static LED leds = LED();

static unsigned int currentAnimationIndex = 0;
static unsigned long currentAnimationStartMs = 0;
static unsigned long currentFrameStartMs = 0;
static unsigned long animationFrameCounter = 0;

static Frame currentFrame;

static bool colorsEqual(LedColor a, LedColor b);
static const char *colorToString(LedColor color);
static void printFrameInfo(const Frame *const frame);

static void clearFrame(Frame *frame, unsigned int duration_ms);
static void fillFrame(Frame *frame, LedColor color, unsigned int duration_ms);
static void showFrame(const Frame *frame);

static void renderBgr(Frame *frame, unsigned long animationFrame);
static void renderKnightRider(Frame *frame, unsigned long animationFrame);
static void renderComplexAnimation(Frame *frame, unsigned long animationFrame);
static void renderComplexAnimationWithLed0RgbOff(Frame *frame, unsigned long animationFrame);
static void renderComplexAnimationWithLed0Rainbow(Frame *frame, unsigned long animationFrame);
static void renderStaticRainbow(Frame *frame, unsigned long animationFrame);
static void renderRunningRainbow(Frame *frame, unsigned long animationFrame);

static const Frame complexAnimation[] = {
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

static const unsigned int complexAnimationFrameCount = sizeof(complexAnimation) / sizeof(complexAnimation[0]);

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
    showFrame(&currentFrame);
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
        showFrame(&currentFrame);
        return;
    }

    if (now - currentFrameStartMs >= currentFrame.duration_ms)
    {
        currentFrameStartMs = now;
        animationFrameCounter++;

        animations[currentAnimationIndex].render(&currentFrame, animationFrameCounter);
        showFrame(&currentFrame);
    }
}

static void clearFrame(Frame *frame, unsigned int duration_ms)
{
    for (unsigned int i = 0; i < LED_COUNT; i++)
    {
        frame->pixels[i] = {0, 0, 0};
    }

    frame->duration_ms = duration_ms;
}

static void fillFrame(Frame *frame, LedColor color, unsigned int duration_ms)
{
    for (unsigned int i = 0; i < LED_COUNT; i++)
    {
        frame->pixels[i] = color;
    }

    frame->duration_ms = duration_ms;
}

static void showFrame(const Frame *frame)
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

    leds.setLEDColor(red, green, blue, LED_COUNT);
    printFrameInfo(frame);
}

static void renderBgr(Frame *frame, unsigned long animationFrame)
{
    static const LedColor sequence[] = {
        LED_BLUE,
        LED_GREEN,
        LED_RED,
    };

    LedColor color = sequence[animationFrame % 3];

    fillFrame(frame, color, 500);
}

static void renderKnightRider(Frame *frame, unsigned long animationFrame)
{
    clearFrame(frame, 100);

    unsigned int position = animationFrame % ((LED_COUNT * 2) - 2);

    if (position >= LED_COUNT)
    {
        position = ((LED_COUNT * 2) - 2) - position;
    }

    frame->pixels[position] = {255, 0, 0};
}

static void renderComplexAnimation(Frame *frame, unsigned long animationFrame)
{
    unsigned int frameIndex = animationFrame % complexAnimationFrameCount;

    *frame = complexAnimation[frameIndex];
}

static void renderComplexAnimationWithLed0RgbOff(Frame *frame, unsigned long animationFrame)
{
    renderComplexAnimation(frame, animationFrame);

    frame->pixels[0] = rgbOffCycle[(animationFrame / 5) % 4];
}

static void renderComplexAnimationWithLed0Rainbow(Frame *frame, unsigned long animationFrame)
{
    renderComplexAnimation(frame, animationFrame);

    frame->pixels[0] = ledRainbow[(animationFrame / 5) % LED_COUNT];
}

static void renderStaticRainbow(Frame *frame, unsigned long animationFrame)
{
    for (unsigned int i = 0; i < LED_COUNT; i++)
    {
        frame->pixels[i] = ledRainbow[i];
    }

    frame->duration_ms = 500;
}

static void renderRunningRainbow(Frame *frame, unsigned long animationFrame)
{
    for (unsigned int i = 0; i < LED_COUNT; i++)
    {
        frame->pixels[i] = ledRainbow[(i + animationFrame) % LED_COUNT];
    }

    frame->duration_ms = 150;
}

static bool colorsEqual(LedColor a, LedColor b)
{
    return (a.r == b.r) && (a.g == b.g) && (a.b == b.b);
}

static const char *colorToString(LedColor color)
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