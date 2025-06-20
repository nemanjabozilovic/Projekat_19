#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>

#define TFT_CS   22
#define TFT_DC   21

Adafruit_ILI9341 display(TFT_CS, TFT_DC);

void setup() {
  display.begin();
  display.fillScreen(ILI9341_WHITE);
  display.setCursor(20, 20);
  display.setTextColor(ILI9341_BLUE);
  display.setTextSize(2);
  display.println("Hello world");
}

void loop() {}
