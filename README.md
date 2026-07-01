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

Dieses Beispiel schaltet die Farben Rot Grün und Blau auf den mit 2s Periodendauer durch. Bei Blau bleibt der Zyklus stehen bis erneut eine Taste gedrückt wurde. Ändern Sie das Programm so ab, dass bei Tastendruck die Farbe weitergeschaltet wird, ohne die 2s abzuwarten.

## 3. Aufgabe

Implementiere das Beispiel als State Machine.

## 4. Aufgabe

Modellieren Sie einen Zustandsautomaten für eine Garagentorsteuerung, welche sich wie folgt verhält:
- Zu beginn ist nicht bekannt, ob das Tor offen oder geschlossen oder in einem Zwischenzustand steht.
- Wird die Taste in unbekanntem Zustand gedrückt, so fährt das Tor in die geschlossene Position
- Wird die Taste im geschlossenen Zustand gedrückt, fährt das Tor auf
- Wird die Taste im offenen Zustand gedrückt, fährt das Tor zu
- Wird die Taste während der Bewegung gedrückt, stoppt das Tor
- Wird eine Taste im gestoppten Zustand gedrückt, fährt das Tor in die Gegenrichtung weiter
- «Offen» und «Geschlossen» wird durch sog. Endschalter erkannt.
