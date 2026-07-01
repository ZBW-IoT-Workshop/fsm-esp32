#include <Animation.h>
#include <Arduino.h>
#include <Bgr.h>
#include <LedColor.h>
#include <LedFrame.h>
#include <QwiicLedStick.h>
#include <Sparkfun_Qwiic_Button.h>
#include <config/board.h>

static LED leds = LED();
static QwiicButton button = QwiicButton();

static Frame frame;

static const Animation animation = {"B-G-R sequence", renderBgr, 6000};

static void button_wait_for_press(QwiicButton *const button);

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

    Serial.println("Initializing Button...");
    success = success && button.begin();
    button.LEDconfig(1, 0, 0);
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
}

void loop(void)
{
    // put your main code here, to run repeatedly:
    animation.render(&frame, 0);
    showFrame(&frame, &leds);
    delay(frame.duration_ms);

    animation.render(&frame, 1);
    showFrame(&frame, &leds);
    delay(frame.duration_ms);

    animation.render(&frame, 2);
    showFrame(&frame, &leds);
    delay(frame.duration_ms);

    button_wait_for_press(&button);
}

static void button_wait_for_press(QwiicButton *const button)
{
    button->clearEventBits();

    while (!button->hasBeenClicked())
    {
        delay(20);
    }

    button->clearEventBits();
    Serial.println("Button pressed");
}

