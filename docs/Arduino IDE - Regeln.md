# Arduino IDE: Regeln für Ordner, Dateien und Bibliotheken

## 1. Sketch‑Grundregeln (Ordner & Hauptdatei)

- Ein **Sketch** ist immer ein **eigener Ordner**.
- Der **Ordnername** ist der **Sketch‑Name**.
- Im Ordner muss **exakt eine Haupt‑`.ino`‑Datei** liegen, die **denselben Namen** wie der Ordner hat:
  - Ordner: `mein_sketch`
  - Datei: `mein_sketch.ino`
- Diese Datei enthält mindestens `setup()` und `loop()`.

> Regel: **Ordnername == Haupt‑`.ino`‑Dateiname** (ohne Erweiterung betrachtet).

---

## 2. Erlaubte Zeichen für Sketch‑ und Dateinamen

Gilt für:
- Sketch‑Ordnername
- Alle Code‑Dateinamen (`.ino`, `.h`, `.cpp`, …)

**Erlaubte Startzeichen:**
- Buchstabe `A–Z` oder `a–z`
- Ziffer `0–9` (ab IDE 1.8.4)
- Unterstrich `_`

**Erlaubte Folgezeichen:**
- Buchstaben `A–Z`, `a–z`
- Ziffern `0–9`
- Unterstrich `_`
- Punkt `.`
- Bindestrich `-`

**Weitere Einschränkungen:**
- Maximale Länge: **63 Zeichen**
- Darf **nicht mit einem Punkt enden** (z. B. `test.` ist ungültig)
- Keine Leerzeichen
- Keine Sonderzeichen wie `ä, ö, ü, ß, @, #, $, %, &`, usw.
- Keine reservierten Namen (die IDE blockiert manche)

**Empfehlung für robuste Namen:**
- Nur ASCII, `_` und `-` verwenden  
  Beispiele: `Blink`, `sensor_test`, `motor-control`, `my_sketch_v2`

---

## 3. Dateierweiterungen

- Empfohlen: **`.ino`** (aktueller Standard)
- Veraltet, aber noch unterstützt: **`.pde`** (wird zukünftig entfernt)
- Weitere erlaubte Quelldateien in Sketches:
  - `.h`, `.hpp` (Header)
  - `.cpp`, `.c` (Implementierung)
  - weitere `.ino`‑Tabs (von der IDE erzeugt)

---

## 4. Spezielle Unterordner im Sketch

### `src` – eigener Code (mitkompiliert)

- Wird **rekursiv** durchsucht und mitkompiliert.
- Ideal für größere Projekte (Modularisierung).
- Typische Nutzung:
  - `mein_sketch.ino`: nur `setup()`, `loop()` und Aufrufe
  - `src/`: `.h` / `.cpp` / ggf. weitere `.ino` für Klassen, Treiber, Hilfsfunktionen

> Wichtig: Der Ordner muss exakt `src` heißen (kleingeschrieben), damit er auf allen Systemen (insb. Linux) korrekt erkannt wird.

### `data` – zusätzliche Dateien (nicht mitkompiliert)

- Für Ressourcen, die **nicht** Teil des kompilierten Codes sind:
  - Konfigurationsdateien (JSON, TXT)
  - Web‑Assets (HTML, CSS, JS) für ESP32/ESP8266
  - Binärdaten, Fonts, etc.
- Dateien, die du über **Sketch → Add File…** hinzufügst, landen hier.

### `extras` – vor allem bei Bibliotheken

- Wird hauptsächlich bei **Bibliotheken** verwendet (Beispiele, Docs, Tools).
- Bei normalen Sketches eher unüblich.

---

## 5. Saubere Projektstruktur (Beispiel)

### Minimales Beispiel

```text
mein_sketch/
  mein_sketch.ino
```

### Empfohlene Struktur für größere Projekte

```text
mein_sketch/
  mein_sketch.ino
  src/
    Sensor.cpp
    Sensor.h
    Motor.cpp
    Motor.h
    Utils.cpp
    Utils.h
  data/
    config.json
    index.html
    style.css
```

**Aufbau:**
- `mein_sketch.ino`  
  - Enthält `#include` der eigenen Module  
  - Implementiert `setup()` und `loop()`  
  - Ruft Funktionen aus `src/` auf
- `src/`  
  - Eigene Klassen, Treiber, Hilfsfunktionen  
  - Wird automatisch mitkompiliert
- `data/`  
  - Nicht‑kompilierte Ressourcen (z. B. für Web‑Server auf ESP)

---

## 6. Globale Bibliotheken: Speicherorte und Struktur

Arduino unterscheidet grob:

1. **Benutzer‑Bibliotheken** (im Sketchbook)
2. **IDE‑/Board‑Paket‑Bibliotheken** (im Installations‑/Hardware‑Verzeichnis)

Für die tägliche Arbeit sind primär die **Benutzer‑Bibliotheken** relevant.

### 6.1 Sketchbook‑Ordner (Basispfad)

Der **Sketchbook‑Ordner** ist in der IDE unter  
**Datei → Einstellungen** (Windows/Linux) bzw. **Arduino IDE → Einstellungen** (macOS) als **„Sketchbook location“** einsehbar und änderbar.

**Standardpfade:**

- **Windows:**
  - `C:\Users\<Benutzername>\Documents\Arduino`
- **macOS:**
  - `/Users/<Benutzername>/Documents/Arduino`
- **Linux:**
  - `/home/<Benutzername>/Arduino`

### 6.2 Bibliotheken‑Ordner (global für den Benutzer)

Innerhalb des Sketchbook‑Ordners gibt es den Unterordner:

- `<Sketchbook>/libraries`

Dort landen:

- Über **Sketch → Bibliothek einbinden → .ZIP‑Bibliothek hinzufügen…** installierte Bibliotheken
- Manuell kopierte Bibliotheken (als kompletter Bibliotheks‑Ordner)
- Bibliotheken, die über den **Bibliotheks‑Manager** installiert wurden (neuere IDEs legen sie ebenfalls hier ab)

**Vollständige Pfade für Bibliotheken:**

- **Windows:**
  - `C:\Users\<Benutzername>\Documents\Arduino\libraries`
- **macOS:**
  - `/Users/<Benutzername>/Documents/Arduino\libraries`
- **Linux:**
  - `/home/<Benutzername>/Arduino/libraries`

> Wichtig: Der Ordner muss exakt `libraries` heißen und direkt im Sketchbook liegen, sonst findet die IDE die Bibliotheken nicht.

### 6.3 Bibliotheks‑Ordnerstruktur (korrekte Installation)

Eine Bibliothek muss als **eigener Unterordner** in `libraries` liegen:

```text
<Sketchbook>/libraries/
  Adafruit_GFX/
    Adafruit_GFX.h
    Adafruit_GFX.cpp
    library.properties
    examples/
  MyOwnLibrary/
    MyOwnLibrary.h
    MyOwnLibrary.cpp
    library.properties
```

**Falsch:**
- Bibliothek direkt in `libraries` ablegen (ohne eigenen Ordner)
- Mehrere Ebenen verschachteln, sodass `library.properties` nicht direkt im Bibliotheks‑Ordner liegt

Die IDE durchsucht nur die **erste Ebene** unter `libraries`.

### 6.4 IDE‑ und Board‑Paket‑Bibliotheken (systemweit / pro Plattform)

Diese Ordner sind meist **nicht** manuell zu bearbeiten, aber zur Info:

- **Windows (IDE 1.x / 2.x, normale Installation):**
  - `C:\Users\<Benutzername>\AppData\Local\Arduino15\packages\<vendor>\hardware\<arch>\<version>\libraries`
- **macOS:**
  - `~/Library/Arduino15/packages/<vendor>/hardware/<arch>/<version>/libraries`
- **Linux:**
  - `~/.arduino15/packages/<vendor>/hardware/<arch>/<version>/libraries`

Dort liegen z. B.:
- Core‑Bibliotheken der Plattform (z. B. `SPI`, `Wire` für AVR/ESP32)
- Mit dem Board‑Paket mitgelieferte Bibliotheken

---

## 7. Praktische Tipps & häufige Fallstricke

- **Keine Leerzeichen oder Umlaute** in Sketch‑/Bibliotheks‑Ordnernamen verwenden.
- **Nicht mit Punkt enden** lassen (`F.O.O.` führt zu Fehlern in der IDE).
- Bei manueller Installation von Bibliotheken:
  - Immer den **kompletten Bibliotheks‑Ordner** (mit `library.properties`) nach `<Sketchbook>/libraries/` kopieren.
  - IDE danach neu starten, falls die Bibliothek nicht sofort erscheint.
- Wenn du den Sketchbook‑Pfad änderst:
  - Wird auch der Bibliothekspfad (`<neuer Sketchbook>/libraries`) entsprechend verschoben.
- Für große Projekte:
  - Haupt‑`.ino` schlank halten
  - Logik in `src/` auslagern
  - Bibliotheken für wiederverwendbare Teile schreiben und in `libraries/` ablegen

---

## 8. Schnellreferenz: Pfade im Überblick

**Sketchbook (Standard):**

- Windows: `C:\Users\<User>\Documents\Arduino`
- macOS: `/Users/<User>/Documents/Arduino`
- Linux: `/home/<User>/Arduino`

**Benutzer‑Bibliotheken:**

- Windows: `C:\Users\<User>\Documents\Arduino\libraries`
- macOS: `/Users/<User>/Documents/Arduino\libraries`
- Linux: `/home/<User>/Arduino/libraries`

**IDE‑Konfiguration / Board‑Pakete (zur Info):**

- Windows: `C:\Users\<User>\AppData\Local\Arduino15\`
- macOS: `~/Library/Arduino15/`
- Linux: `~/.arduino15/`