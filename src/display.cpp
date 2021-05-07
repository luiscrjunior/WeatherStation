#include <display.h>
#include <SPI.h>

void Display::init(void)
{
  if (epd.Init() != 0)
  {
    Serial.println("[WeatherStation] Error initializing EPD.");
    return;
  }
}

void Display::display(void)
{
  epd.DisplayFrame(black_buffer, red_buffer);
}

void Display::sleep(void)
{
  epd.Sleep();
}