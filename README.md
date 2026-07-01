# LED-Board FSM

Boilerplate Code, um den [SparkFun LED 10x Output (Qwiic)](https://www.sparkfun.com/sparkfun-qwiic-led-stick-apa102c.html) und 1 x [SparkFun Button (Qwiic)](https://www.sparkfun.com/sparkfun-qwiic-button-red-led.html) anzusteuern, mit FSM lib.

## Aufgaben

### 1. Aufgabe

1. Clone dieses Repo

```
cd my-favourite-dir
git clone https://github.com/IT-A-23H-27H/fsm-esp32.git
```

4. Checke deinen Branch aus

```
cd fsm-esp32
git checkout my-name
```

5. Öffne das Projekt mit Visual Studio Code

```
code .
```

## 2. Aufgabe

Dieses Beispiel schaltet die Farben Rot Grün und Blau auf den mit 2 s Periodendauer durch. Bei Blau bleibt der Zyklus stehen bis erneut eine Taste gedrückt wurde. Ändere das Programm so ab, dass bei Tastendruck die Farbe weitergeschaltet wird, ohne die 2 s abzuwarten.

Tastendrücke können anhand folgendem Snippet abgefragt werden:

```cpp
if (button.hasBeenClicked())
{
    button.clearEventBits(); // Click event löschen
    Serial.println("Button pressed");
}
```

## 3. Aufgabe

Implementiere das Beispiel als State Machine mit `switch` statements.

## 4. Aufgabe

Modelliere eine State Machine für eine Garagentorsteuerung, welche sich wie folgt verhält:

- Zu beginn ist nicht bekannt, ob das Tor offen oder geschlossen oder in einem Zwischenzustand steht.
- Wird die Taste in unbekanntem Zustand gedrückt, so fährt das Tor in die geschlossene Position
- Wird die Taste im geschlossenen Zustand gedrückt, fährt das Tor auf
- Wird die Taste im offenen Zustand gedrückt, fährt das Tor zu
- Wird die Taste während der Bewegung gedrückt, stoppt das Tor
- Wird eine Taste im gestoppten Zustand gedrückt, fährt das Tor in die Gegenrichtung weiter
- «Offen» und «Geschlossen» wird durch sog. Endschalter erkannt.

Zur Umsetzung soll die FSM-Bibliothek unter `lib/fsm` verwendet werden. Unter `src/garage_door` findest du bereits ein angefangenes Skelett. Der Garagentor-Motor kann mit `src/motor_sim` simuliert werden.

Passe dein `main.cpp` anhand folgendem Snippet an um die FSM auszuführen:

```cpp
#include <Animation.h>
#include <Arduino.h>
#include <Fill.h>
#include <LedFrame.h>
#include <QwiicLedStick.h>
#include <Sparkfun_Qwiic_Button.h>
#include <config/board.h>
#include "garage_door/garage_door.h"
#include "motor_sim/motor_sim.h"

static LED leds = LED();
static QwiicButton button;
static MotorSim *motorSim = nullptr;
static fsm::FSM *garageDoor = nullptr;

Animation motorFillAnimation = {
    "Motor Fill",
    renderFill,
    (LED_COUNT + 1) * 100,
};

GarageDoorContext context;

static const unsigned long tick_ms = 500;
static unsigned long lastTick_ms = 0;

void setup(void)
{
    // put your setup code here, to run once:
    bool success = true;

    Serial.begin(115200);
    Wire.begin();

    ...

    motorSim = new MotorSim(leds, motorFillAnimation);

    context.button   = &button;
    context.motorSim = motorSim;
    garageDoor = garage_door_create(&context);

    lastTick_ms = millis();
}

void loop(void)
{
    // put your main code here, to run repeatedly:
    unsigned long now = millis();

    if (now - lastTick_ms < tick_ms)
    {
        return;
    }
    lastTick_ms = now;

    garageDoor->run();
}
```
