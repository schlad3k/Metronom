# Metronom

# Einführung

Bei diesem Projekt wollte ich ein Metronom mit meinem ESP32 programmieren. Zum Programmieren habe ich die Arduino IDE benutzt.

# Projektbeschreibung

Mein Metronom soll durch drei Knöpfe gesteuert werden. Ein Knopf erhöht die Geschwindigkeit, einer senkt sie und ein Knopf verändert den Ton. Dieser Ton wird auf einem Lautsprecher ausgegeben.

# Theorie

Für den Aufbau habe ich drei normale Knöpfe an GPIO-Pins angeschlossen und die Eingaben mit einer Anhäufung an if-Abfragen verwaltet. Für den Ton habe ich die ToneESP32.h und die Notes.h Library von Arduino verwendet.

# Arbeitsschritte

Als erstes habe ich die drei Knöpfe an den Mikrocontroller angeschlossen. Danach habe ich mir einen Lautsprecher gekauft und ihn an einen Pin und Ground angeschlossen. Hier habe ich meinen Schaltplan in Wokwi gezeichnet.
![grafik](https://github.com/schlad3k/Metronom/assets/131366006/f7c69a76-698e-4953-8c2e-a573f6d8c635)

Jetzt musste ich nur noch den Code programmieren. Für die Töne musste ich eine Tondauer und eine Pause berechnen, je nachdem wie schnell es im Moment ist. Diese Schläge pro Minute habe ich je nach dem welcher Knopf gedrückt wird angepasst. Die Töne sind alle C Noten in einem Array. Wenn der Notenbutton gedrückt wird, wird der Index des Arrays erhöht. Wenn ich bei der letzten Stelle im Array bin, wird zuerst nichts abgespielt und danach wieder von vorne begonnen. 

```cpp
#include <Notes.h> 
#include <ToneESP32.h>
#define OUT 32
#define PacePlus 4
#define PaceMinus 22
#define differentTone 14
void setup() {
  pinMode(OUT, OUTPUT);
  pinMode(PacePlus, INPUT);
  pinMode(PaceMinus, INPUT);
  pinMode(differentTone, INPUT);
  Serial.begin(9600);
}
int sps = 100;
int dauer = (60000 / sps) * 0.25;
int pause2 = (60000 / sps) * 0.75;
int tonindex = 0;

void loop() {
  Serial.println(digitalRead(differentTone));
  int notes[] = {
    NOTE_C1, NOTE_C2, NOTE_C3, NOTE_C4, NOTE_C5, NOTE_C6, NOTE_C7, NOTE_C8
  };
  if(digitalRead(PacePlus) == HIGH) {
    sps += 10;
    dauer = 60000 / sps / 4;
    pause2 = dauer * 3;
    Serial.println("Geschwindigkeit wird erhöht");
  }
  if(digitalRead(PaceMinus) == HIGH) {
    sps -= 10;
    dauer = 60000 / sps / 4;
    pause2 = dauer * 3;
    Serial.println("Geschwindigkeit wird gesenkt");
  }
  if(digitalRead(differentTone) == HIGH) {
    tonindex += 1;
  }
  if(tonindex == sizeof(notes)/sizeof(notes[0])) {
    tonindex = 0;
  }
  tone(OUT, notes[tonindex+2], sps);
  delay(pause2);
}
```

# Zusammenfassung

Dieses Projekt hat insgesamt ca 4 Stunden an Zeitaufwand benötigt und funktioniert perfekt als Metronom. Für den Fall, dass ich andere Frequenzen haben will, kann ich die Erhöhung pro Klick auf 2 oder 4 anpassen. Für eine klarere Angabe von der Geschwindigkeit, könnte ich die SPS auf einem Display ausgeben.

# Quellen

[https://esp32io.com/tutorials/esp32-button-toggle-led](https://esp32io.com/tutorials/esp32-button-toggle-led)

[https://www.mikrocontroller.net/topic/543430](https://www.mikrocontroller.net/topic/543430)
