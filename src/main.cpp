#include <Arduino.h>

#include <display.h>

#include <Fonts/FreeSansBold24pt7b.h>

Display display;

void setup()
{
  Serial.begin(115200);

  Serial.println("initializing EPD...");
  display.init();

  Serial.println("Printing...");
  display.setRotation(ROTATE_270);
  display.setFont(&FreeSansBold24pt7b);
  display.fillScreen(COLOR_WHITE);
  display.setTextColor(COLOR_BLACK);
  display.setCursor(30, 60);
  display.print("Teste");

  display.display();

  display.sleep();
}

void loop()
{
}
