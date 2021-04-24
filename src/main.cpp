#include <Arduino.h>

#include <display.h>

Display display;

void setup()
{
  Serial.begin(115200);
  display.init();
}

void loop()
{
}
