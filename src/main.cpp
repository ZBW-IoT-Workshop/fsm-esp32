#include <Arduino.h>
#include <QwiicLedStick.h>

static LED leds = LED();

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
}

void loop(void)
{
    // put your main code here, to run repeatedly:
    leds.setLEDColor(255, 0, 0);
    delay(500);
    leds.setLEDColor(0, 255, 0);
    delay(500);
    leds.setLEDColor(0, 0, 255);
    delay(500);
}
