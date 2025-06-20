#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>

#define TFT_CS   22
#define TFT_DC   21
#define BUTTON_PIN 15

Adafruit_ILI9341 display(TFT_CS, TFT_DC);
String nmeaSentence = "";
bool sentenceReady = false;

// Funkcija za parsiranje DMM u decimalne stepene
double dmmToDecimal(String dmm, char dir) {
  int dotIndex = dmm.indexOf('.');
  if (dotIndex < 0) return 0.0;
  int degLen = (dotIndex > 2) ? 3 : 2;
  double deg = dmm.substring(0, degLen).toInt();
  double min = dmm.substring(degLen).toFloat();
  double dec = deg + (min / 60.0);
  if (dir == 'S' || dir == 'W') dec = -dec;
  return dec;
}

// Funkcija za parsiranje NMEA RMC rečenice
bool parseRMC(String sentence, String &latDMM, char &latDir, String &lonDMM, char &lonDir) {
  int idx = 0;
  int lastIdx = 0;
  int field = 0;
  String fields[13];
  while ((idx = sentence.indexOf(',', lastIdx)) != -1) {
    fields[field++] = sentence.substring(lastIdx, idx);
    lastIdx = idx + 1;
    if (field >= 13) break;
  }
  // Poslednje polje
  if (field < 13 && lastIdx < sentence.length())
    fields[field++] = sentence.substring(lastIdx);
  if (fields[0].endsWith("RMC") && field >= 7) {
    latDMM = fields[3];
    latDir = fields[4][0];
    lonDMM = fields[5];
    lonDir = fields[6][0];
    return true;
  }
  return false;
}

void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  Serial.begin(115200);
  display.begin();
  display.fillScreen(ILI9341_WHITE);
  display.setCursor(20, 20);
  display.setTextColor(ILI9341_BLUE);
  display.setTextSize(2);
  display.println("Unesi NMEA RMC rečenicu:");
}

void loop() {
  // Čitanje sa Serial-a
  while (Serial.available()) {
    char c = Serial.read();
    if (c == '\n' || c == '\r') {
      if (nmeaSentence.length() > 0) {
        sentenceReady = true;
        Serial.print("Uneta recenica: ");
        Serial.println(nmeaSentence);
      }
    } else {
      nmeaSentence += c;
    }
  }

  // Kada je taster pritisnut i rečenica spremna
  if (sentenceReady && digitalRead(BUTTON_PIN) == LOW) {
    String latDMM, lonDMM;
    char latDir, lonDir;
    if (parseRMC(nmeaSentence, latDMM, latDir, lonDMM, lonDir)) {
      double latDec = dmmToDecimal(latDMM, latDir);
      double lonDec = dmmToDecimal(lonDMM, lonDir);
      display.fillScreen(ILI9341_WHITE);
      display.setCursor(10, 20);
      display.setTextColor(ILI9341_BLUE);
      display.setTextSize(2);
      display.println("DMM: ");
      display.print("Lat: "); display.println(latDMM + String(latDir));
      display.print("Lon: "); display.println(lonDMM + String(lonDir));
      display.println("");
      display.println("Decimal:");
      display.print("Lat: "); display.println(latDec, 6);
      display.print("Lon: "); display.println(lonDec, 6);
    } else {
      display.fillScreen(ILI9341_WHITE);
      display.setCursor(10, 20);
      display.setTextColor(ILI9341_RED);
      display.setTextSize(2);
      display.println("Greška u rečenici!");
    }
    nmeaSentence = "";
    sentenceReady = false;
    delay(1000);
  }
}
