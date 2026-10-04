- den einmaligen Richtungswechsel beim Drücken
# Zoetrope SysML-v2-Modell

## Zweck und Baseline

Dieses Dokument führt in sechs verständlichen Diagrammen vom Systemüberblick bis
zu seinen Zuständen. Grundlage ist der Sketch `../project_10_zoetrope.ino`:
Der Motor läuft, solange der Ein/Aus-Taster gedrückt ist. Der Richtungstaster
ändert die Drehrichtung einmal pro Tastendruck; erneutes Drücken ist erst nach
dem Loslassen möglich. Das Potentiometer stellt die Drehzahl ein.

## Lernpfad: sechs Diagramme

Jedes Diagramm beantwortet eine Frage und baut auf dem vorherigen auf. Die
Diagramme sind bewusst vereinfacht und zeigen jeweils nur die Informationen,
die für den aktuellen Lernschritt wichtig sind.

### 1. Systemkontext: Was liegt innerhalb der Systemgrenze?

```mermaid


flowchart LR
  operator[Bedienperson]
  supply[USB 5 V und Motorversorgung 9 V]
  effect[Visuelle Animation]

  subgraph system[Zoetrope-System]
    buttons[Taster Ein/Aus und Richtung]
    potentiometer[Potentiometer]
    controller[Arduino Uno]
    driver[L293D H-Brücke]
    motor[DC-Motor]
    disk[Zoetrope-Scheibe mit Bildstreifen]
    buttons --> controller
    potentiometer --> controller
    controller -->|D2, D3, D9| driver
    driver --> motor --> disk
  end

  operator --> buttons
  operator --> potentiometer
  supply --> driver
  disk --> effect



```

### 2. Anforderungen: Woran erkennen wir Erfolg?

```mermaid
flowchart LR
  need[Bedienbare Drehbewegung]
  need --> enable[Motorfreigabe folgt dem Ein/Aus-Pegel]
  need --> direction[Drehrichtung ändert sich einmal pro Tastendruck]
  need --> speed[Potentiometerwert wird auf PWM skaliert]
  need --> driver[Motor wird über die H-Brücke angesteuert]
  need --> off[PWM ist bei LOW gleich null]

  enable --> testEnable[Test: HIGH und LOW an D5 prüfen]
  direction --> testDirection[Test: einmal drücken, einmal umschalten]
  speed --> testSpeed[Test: 0, 512, 1023 ergeben 0, 128, 255]
  driver --> testDriver[Inspektion: Motor liegt an der H-Brücke]
  off --> testOff[Messung: PWM bei LOW ist null]
```

Jede Anforderung ist mit einer passenden Prüfung verbunden.

### 3. Use Cases: Was tut die Bedienperson mit dem System?

```mermaid

flowchart LR
  operator((Bedienperson))
  enable([Motorfreigabe setzen])
  speed([Drehzahl einstellen])
  direction([Drehrichtung wechseln])

  operator --> enable
  operator --> speed
  operator --> direction


```

Beim Ein/Aus-Taster ist entscheidend, ob er gerade gedrückt ist. Beim
Richtungstaster löst jeder neue Tastendruck genau einen Wechsel aus. Gedrückt
halten oder Loslassen ändert die Richtung nicht erneut.

### 4. Funktionaler Ablauf: Wie entsteht ein Motorbefehl?

```mermaid
flowchart TD
  read[Ein/Aus, Richtung und A0 einlesen]
  edge{Wurde der Richtungstaster gerade gedrückt?}
  changeDirection[Richtung umschalten]
  keep[Richtung beibehalten]
  pins[D2 und D3 passend zur Richtung setzen]
  scale[PWM = analogRead A0 / 4]
  enabled{Ein/Aus-Pegel ist HIGH?}
  write[ PWM auf D9 ausgeben]
  stop[PWM auf D9 auf null setzen]

  read --> edge
  edge -->|Ja| changeDirection --> pins
  edge -->|Nein| keep --> pins
  pins --> scale --> enabled
  enabled -->|Ja| write
  enabled -->|Nein| stop
```

### 5. Struktur: Welche Teile setzen den Ablauf um?

```mermaid
flowchart LR
  subgraph system[Zoetrope-System]
    inputs[Taster und Potentiometer]
    controller[Arduino Uno\nD2, D3, D4, D5, A0, D9]
    bridge[L293D H-Brücke]
    motor[DC-Motor]
    assembly[Scheibe und Bildstreifen]
    inputs --> controller
    controller -->|Richtung und PWM| bridge
    bridge -->|Motorleistung| motor
    motor --> assembly
  end
```

### 6. Zustände: Was bleibt zwischen den Schleifendurchläufen erhalten?

Die beiden Teile zeigen getrennte Zustände. Der Motor kann zum Beispiel
ausgeschaltet und zugleich auf Vorwärtsrichtung eingestellt sein.

```mermaid
stateDiagram-v2
  state "Motorfreigabe" as Enable {
    [*] --> MotorAus
    MotorAus --> MotorEin : Ein/Aus-Pegel HIGH
    MotorEin --> MotorAus : Ein/Aus-Pegel LOW
  }
  state "Drehrichtung" as Direction {
    [*] --> Vorwaerts
    Vorwaerts --> Rueckwaerts : Taste gedrückt, zuvor losgelassen
    Rueckwaerts --> Vorwaerts : Taste gedrückt, zuvor losgelassen
  }
```

## Modell lesen

## Wie die Diagramme zusammenhängen

Der **Systemkontext** zeigt Systemgrenze und Bedienperson. Die **Anforderungen**
beschreiben, woran ein korrektes Ergebnis erkennbar ist. Die **Use Cases**
zeigen die Bedienhandlungen. Der **Ablauf** erklärt, wie der Arduino daraus
Steuersignale bildet. Die **Struktur** ordnet die Aufgaben den Bauteilen zu.
Die **Zustände** zeigen, welche Einstellungen über mehrere Programmdurchläufe
erhalten bleiben.

Die Pinbelegung folgt dem Sketch: D2 und D3 steuern die H-Brücke, D9 gibt das
PWM-Signal aus, D4 und D5 lesen die Taster und A0 liest das Potentiometer.

## Diagramme in VS Code ansehen

Öffne diese README und wähle **Markdown: Open Preview** aus der Befehlspalette
(Tastenkürzel `Cmd+Shift+V`). Die Diagramme erscheinen in der Vorschau direkt
unter ihrer jeweiligen Erklärung.

## Abgrenzung der Quellen

Die Dokumentation folgt dem aktuellen Sketch: Der Ein/Aus-Taster steuert den
Motor über seinen aktuellen Pegel. Die separate PlatformIO-SRS nennt zusätzlich
eine Stroboskop-LED und Synchronisation. Diese Funktionen sind im Sketch nicht
implementiert und deshalb nicht Teil dieser Beschreibung.